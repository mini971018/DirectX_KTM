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
	RoarEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Effect);

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
	RoarEffectRenderer->GetTransform()->SetLocalPosition({ Pos.x, Pos.y, -400});
}

void RoarEffect::Update(float _Delta)
{
	float4 CurrentScale = RoarEffectRenderer->GetTransform()->GetLocalScale();
	float ScaleValue = 30.0f * _Delta;

	CurrentScale.x += ScaleValue;
	CurrentScale.y += ScaleValue;

	RoarEffectRenderer->GetTransform()->SetLocalScale(CurrentScale);

	if (GetLiveTime() >= 1.0f)
	{
		RoarEffectRenderer->Death();
		Death();
	}
}