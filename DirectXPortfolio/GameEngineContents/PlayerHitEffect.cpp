#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "PlayerHitEffect.h"

PlayerHitEffect::PlayerHitEffect() 
{
}

PlayerHitEffect::~PlayerHitEffect() 
{
}

void PlayerHitEffect::Start()
{
	HitEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);
	
	HitEffectRenderer->CreateAnimation({ .AnimationName = "HitEffect", .SpriteName = "82.HitEffect", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	HitEffectRenderer->ChangeAnimation("HitEffect");
}

void PlayerHitEffect::Update(float _Delta)
{
	if (true == HitEffectRenderer->IsAnimationEnd())
	{
		if (HitEffectRenderer != nullptr)
		{
			HitEffectRenderer->Death();
			HitEffectRenderer = nullptr;
			Death();
		}
	}

}

void PlayerHitEffect::SetEnemyHitEffect(float4 _Pos, float4 _Scale, float _Angle)
{
	GetTransform()->SetWorldPosition(_Pos);
	GetTransform()->SetWorldScale(_Scale);
	GetTransform()->AddLocalRotation(float4{ 0.0f, 0.0f, _Angle });
}