#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RoarEffect.h"


RoarEffect::RoarEffect() 
{
}

RoarEffect::~RoarEffect() 
{
}

void RoarEffect::Start()
{
	RoarEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);

	ResetLiveTime();
}

void RoarEffect::SetRoarEffect(RoarType _Type, float4 Pos)
{
	std::string_view RoarString;

	switch (_Type)
	{
	case RoarType::Black:
		RoarString = "RoarEffect1.png";
		break;
	case RoarType::White:
		RoarString = "RoarEffect2.png";
		break;
	default:
		break;
	}

	RoarEffectRenderer->SetScaleToTexture(RoarString);
	RoarEffectRenderer->GetTransform()->SetLocalPosition({ Pos.x, Pos.y, -70});
	RoarEffectRenderer->ColorOptionValue.MulColor.a = 0.8f;
}

void RoarEffect::Update(float _Delta)
{
	float4 CurrentScale = RoarEffectRenderer->GetTransform()->GetLocalScale();
	float ScaleValue = 9000 * _Delta;

	CurrentScale.x += ScaleValue;
	CurrentScale.y += ScaleValue;

	RoarEffectRenderer->GetTransform()->SetLocalScale(CurrentScale);

	if (GetLiveTime() >= 1.0f)
	{
		if (RoarEffectRenderer != nullptr)
		{
			RoarEffectRenderer->Death();
			RoarEffectRenderer = nullptr;
			Death();
		}
	}
}