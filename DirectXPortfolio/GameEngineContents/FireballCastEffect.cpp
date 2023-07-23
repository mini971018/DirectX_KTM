#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FireballCastEffect.h"

FireballCastEffect::FireballCastEffect() 
{
}

FireballCastEffect::~FireballCastEffect() 
{
}

void FireballCastEffect::Start()
{
	CastEffect = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);
	CastEffect->CreateAnimation({ .AnimationName = "FireballCastEffect", .SpriteName = "86.FireballCastEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	CastEffect->ChangeAnimation("FireballCastEffect");
}

void FireballCastEffect::Update(float _Delta)
{
	if (true == CastEffect->IsAnimationEnd())
	{
		if (CastEffect != nullptr)
		{
			CastEffect->Death();
			CastEffect = nullptr;
			Death();
		}
	}
}