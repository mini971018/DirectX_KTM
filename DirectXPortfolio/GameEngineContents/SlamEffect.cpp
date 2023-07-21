#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "SlamEffect.h"

SlamEffect::SlamEffect() 
{
}

SlamEffect::~SlamEffect() 
{
}

void SlamEffect::Start()
{
	SlamEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	SlamEffectRenderer->CreateAnimation({ .AnimationName = "SlamEffect", .SpriteName = "96.SlamEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	SlamEffectRenderer->ChangeAnimation("SlamEffect");
}

void SlamEffect::Update(float _Delta)
{
	if (true == SlamEffectRenderer->IsAnimationEnd())
	{
		if (SlamEffectRenderer != nullptr)
		{
			SlamEffectRenderer->Death();
			SlamEffectRenderer = nullptr;
			Death();
		}
	}
}