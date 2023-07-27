#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PlayerDeathEffect.h"

PlayerDeathEffect::PlayerDeathEffect() 
{
}

PlayerDeathEffect::~PlayerDeathEffect() 
{
}

void PlayerDeathEffect::Start()
{
	DeathEffect = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);
	DeathEffect->CreateAnimation({ .AnimationName = "PlayerDeathEffect", .SpriteName = "80.PlayerDeathEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	DeathEffect->ChangeAnimation("PlayerDeathEffect");
}

void PlayerDeathEffect::Update(float _Delta)
{
	if (true == DeathEffect->IsAnimationEnd())
	{
		if (DeathEffect != nullptr)
		{
			DeathEffect->Death();
			DeathEffect = nullptr;
			Death();
		}
	}

	if (DeathEffect != nullptr)
	{
		DeathEffect->SetScaleRatio(DeathEffect->GetScaleRatio() + (40.0f * _Delta));

	}
}
