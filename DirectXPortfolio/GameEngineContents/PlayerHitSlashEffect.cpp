#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PlayerHitSlashEffect.h"

PlayerHitSlashEffect::PlayerHitSlashEffect() 
{
}

PlayerHitSlashEffect::~PlayerHitSlashEffect() 
{
}


void PlayerHitSlashEffect::Start()
{
	HitSlashEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);
	HitSlashEffectRenderer->CreateAnimation({ .AnimationName = "HitSlashEffect1", .SpriteName = "83.HitSlashEffect1", .FrameInter = 0.024f, .Loop = false, .ScaleToTexture = true });
	HitSlashEffectRenderer->CreateAnimation({ .AnimationName = "HitSlashEffect2", .SpriteName = "84.HitSlashEffect2", .FrameInter = 0.024f, .Loop = false, .ScaleToTexture = true });

	HitSlashEffectRenderer->ChangeAnimation("HitSlashEffect1");
	HitSlashEffectRenderer->Off();

}

void PlayerHitSlashEffect::Update(float _Delta)
{
	if (true == HitSlashEffectRenderer->IsAnimationEnd())
	{
		if (HitSlashEffectRenderer != nullptr)
		{
			HitSlashEffectRenderer->Death();
			HitSlashEffectRenderer = nullptr;
			Death();
		}
	}
}

void PlayerHitSlashEffect::SetEnemyHitSlashEffect(float4 _Pos, float4 _Scale, PlayerSlashAnimation _Type)
{
	GetTransform()->SetWorldPosition(_Pos);
	GetTransform()->SetWorldScale(_Scale);

	switch (_Type)
	{
	case PlayerSlashAnimation::Slash1:
		HitSlashEffectRenderer->ChangeAnimation("HitSlashEffect1");
		break;
	case PlayerSlashAnimation::Slash2:
		HitSlashEffectRenderer->ChangeAnimation("HitSlashEffect2");
		break;
	case PlayerSlashAnimation::UpperSlash:
		GetTransform()->AddLocalRotation(float4{ 0.0f, 0.0f, 90.0f });
		HitSlashEffectRenderer->ChangeAnimation("HitSlashEffect1");
		break;
	case PlayerSlashAnimation::DownSlash:
		GetTransform()->AddLocalRotation(float4{ 0.0f, 0.0f, 90.0f });
		HitSlashEffectRenderer->ChangeAnimation("HitSlashEffect2");
		break;
	default:
		break;
	}

	HitSlashEffectRenderer->On();
}