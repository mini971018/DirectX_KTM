#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "ShadowDashEffect.h"

ShadowDashEffect::ShadowDashEffect() 
{
}

ShadowDashEffect::~ShadowDashEffect() 
{
}

void ShadowDashEffect::Start()
{
	ShadowDashEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPB_Effect);
	ShadowDashEffectRenderer->CreateAnimation({ .AnimationName = "ShadowDashEffect", .SpriteName = "104.ShadowDashEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	ShadowDashEffectRenderer->ChangeAnimation("ShadowDashEffect");
}

void ShadowDashEffect::Update(float _Delta)
{
	if (true == ShadowDashEffectRenderer->IsAnimationEnd())
	{
		if (ShadowDashEffectRenderer != nullptr)
		{
			ShadowDashEffectRenderer->Death();
			ShadowDashEffectRenderer = nullptr;
			Death();
		}
	}
}