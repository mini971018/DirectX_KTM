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
	float4 Value = float4(100, 100);

	RoarEffectRenderer->GetTransform()->AddLocalScale(Value);

	if (GetLiveTime() >= 1.0f)
	{
		RoarEffectRenderer->Death();
		Death();
	}
}