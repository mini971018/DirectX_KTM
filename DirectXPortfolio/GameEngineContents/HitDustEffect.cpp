#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "HitDustEffect.h"

HitDustEffect::HitDustEffect() 
{
}

HitDustEffect::~HitDustEffect() 
{
}

void HitDustEffect::Start()
{
	DustEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BBPB_Effect);
	DustEffectRenderer->CreateAnimation({ .AnimationName = "HitDust", .SpriteName = "100.HitDust", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	DustEffectRenderer->ChangeAnimation("HitDust");
}

void HitDustEffect::Update(float _Delta)
{
	Dir += (float4::Down * 1000.0f * _Delta);

	GetTransform()->AddWorldPosition(Dir * _Delta);

	if (true == DustEffectRenderer->IsAnimationEnd())
	{
		if (DustEffectRenderer != nullptr)
		{
			DustEffectRenderer->Death();
			DustEffectRenderer = nullptr;
			Death();
		}
	}
}

void HitDustEffect::SetHitDust(float4 _Dir)
{
	Dir = _Dir.NormalizeReturn();
	
	float RandomForce = GameEngineRandom::MainRandom.RandomFloat(800.0f, 1200.0f);
	float RandomScale = GameEngineRandom::MainRandom.RandomFloat(0.3f, 1.0f);
	int RandomColor = GameEngineRandom::MainRandom.RandomInt(0, 2);
	
	switch (RandomColor)
	{
	case 0:
		DustEffectRenderer->ColorOptionValue.PlusColor = DustColor1;
		DustEffectRenderer->ColorOptionValue.MulColor = DustColor1;
		break;
	case 1:
		DustEffectRenderer->ColorOptionValue.PlusColor = DustColor2;
		DustEffectRenderer->ColorOptionValue.MulColor = DustColor2;
		break;
	case 2 :
		DustEffectRenderer->ColorOptionValue.PlusColor = DustColor3;
		DustEffectRenderer->ColorOptionValue.MulColor = DustColor3;
		break;
	default:
		break;
	}

	DustEffectRenderer->ColorOptionValue.MulColor.a = 1.0f;

	GetTransform()->SetLocalScale({ RandomScale, RandomScale, 1 });
	Dir = Dir * RandomForce;
}