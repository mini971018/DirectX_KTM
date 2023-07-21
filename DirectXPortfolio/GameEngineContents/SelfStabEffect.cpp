#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "SelfStabEffect.h"


SelfStabEffect::SelfStabEffect() 
{
}

SelfStabEffect::~SelfStabEffect() 
{
}

void SelfStabEffect::Start()
{
	SelfStabEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);
	SelfStabEffectRenderer->CreateAnimation({ .AnimationName = "SelfStabFlash", .SpriteName = "95.SelfStabFlash", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	SelfStabEffectRenderer->ChangeAnimation("SelfStabFlash");
}


void SelfStabEffect::Update(float _Delta)
{
	if (true == SelfStabEffectRenderer->IsAnimationEnd())
	{
		if (SelfStabEffectRenderer != nullptr)
		{
			SelfStabEffectRenderer->Death();
			SelfStabEffectRenderer = nullptr;
			Death();
		}
	}
}