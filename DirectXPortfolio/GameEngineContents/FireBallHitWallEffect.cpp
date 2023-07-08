#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FireBallHitWallEffect.h"


FireBallHitWallEffect::FireBallHitWallEffect() 
{
}

FireBallHitWallEffect::~FireBallHitWallEffect() 
{
}

void FireBallHitWallEffect::Start()
{
	HitWallEffect = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BBPB_Effect);
	HitWallEffect->CreateAnimation({ .AnimationName = "FireballHitWallEffect", .SpriteName = "91.FireballHitWallEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	HitWallEffect->ChangeAnimation("FireballHitWallEffect");
}

void FireBallHitWallEffect::Update(float _Delta)
{
	if (true == HitWallEffect->IsAnimationEnd())
	{
		if (HitWallEffect != nullptr)
		{
			HitWallEffect->Death();
			HitWallEffect = nullptr;
			Death();
		}
	}
}