#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "HollowKnightDashEffect.h"

HollowKnightDashEffect::HollowKnightDashEffect() 
{
}

HollowKnightDashEffect::~HollowKnightDashEffect() 
{
}

void HollowKnightDashEffect::Start()
{
	DashEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	DashEffectRenderer->CreateAnimation({ .AnimationName = "DashEffect", .SpriteName = "57.DashEffect", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	DashEffectRenderer->ChangeAnimation("DashEffect");
}

void HollowKnightDashEffect::Update(float _Delta)
{
	if (true == DashEffectRenderer->IsAnimationEnd())
	{
		if (DashEffectRenderer != nullptr)
		{
			DashEffectRenderer->Death();
			DashEffectRenderer = nullptr;
			Death();
		}
	}
}