#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "BossDeathEffect.h"

BossDeathEffect::BossDeathEffect() 
{
}

BossDeathEffect::~BossDeathEffect() 
{
}

void BossDeathEffect::Start()
{
	BossDeathEffectActor = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);
	BossDeathEffectActor->CreateAnimation({ .AnimationName = "EndDeath", .SpriteName = "51.EndDeath", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
	BossDeathEffectActor->ChangeAnimation("EndDeath");
}

void BossDeathEffect::Update(float _Delta)
{
	if (true == BossDeathEffectActor->IsAnimationEnd())
	{
		if (BossDeathEffectActor != nullptr)
		{
			BossDeathEffectActor->Death();
			BossDeathEffectActor = nullptr;
			Death();
		}
	}
}