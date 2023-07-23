#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "SlashEffect.h"

SlashEffect::SlashEffect() 
{
}

SlashEffect::~SlashEffect() 
{
}

void SlashEffect::Start()
{
	SlashEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	SlashEffectRenderer->CreateAnimation({ .AnimationName = "SlashEffect", .SpriteName = "98.SlashEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	SlashEffectRenderer->SetAnimationStartEvent("SlashEffect", 1, [this]
		{
			SlashCollision->On();
		});
	SlashEffectRenderer->SetAnimationStartEvent("SlashEffect", 4, [this]
		{
			SlashCollision->Off();
		});
	SlashEffectRenderer->CreateAnimation({ .AnimationName = "Slash2Effect", .SpriteName = "99.Slash2Effect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	SlashEffectRenderer->SetAnimationStartEvent("Slash2Effect", 1, [this]
		{
			SlashCollision->On();
		});
	SlashEffectRenderer->SetAnimationStartEvent("Slash2Effect", 4, [this]
		{
			SlashCollision->Off();
		});
	SlashEffectRenderer->CreateAnimation({ .AnimationName = "UpSlashEffect", .SpriteName = "100.UpSlashEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	SlashEffectRenderer->SetAnimationStartEvent("UpSlashEffect", 1, [this]
		{
			SlashCollision->On();
		});
	SlashEffectRenderer->SetAnimationStartEvent("UpSlashEffect", 4, [this]
		{
			SlashCollision->Off();
		});
	SlashEffectRenderer->CreateAnimation({ .AnimationName = "DownSlashEffect", .SpriteName = "101.DownSlashEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	SlashEffectRenderer->SetAnimationStartEvent("DownSlashEffect", 1, [this]
		{
			SlashCollision->On();
		});
	SlashEffectRenderer->SetAnimationStartEvent("DownSlashEffect", 4, [this]
		{
			SlashCollision->Off();
		});

	SlashEffectRenderer->ChangeAnimation("SlashEffect");

	SlashEffectRenderer->Off();

	SlashCollision = CreateComponent<GameEngineCollision>();
	SlashCollision->SetColType(ColType::AABBBOX2D);
	SlashCollision->Off();
	SlashCollision->SetOrder(static_cast<int>(HollowKnightCollisionType::PlayerAttack));
}

void SlashEffect::Update(float _Delta)
{
	std::shared_ptr<GameEngineCollision> HitCollision = SlashCollision->Collision(HollowKnightCollisionType::Boss);

	if (nullptr != HitCollision)
	{
		IsHit = true;
	}

	if (true == SlashEffectRenderer->IsAnimationEnd())
	{
		SlashEffectRenderer->Off();
	}
}

void SlashEffect::SetSlashEffect(PlayerSlashAnimation _SlashType, float4 _Pos, float _Damage)
{
	SlashDamage = _Damage;

	std::string_view AnimationType = "";

	switch (_SlashType)
	{
	case PlayerSlashAnimation::Slash1:
		SlashCollision->GetTransform()->SetLocalPosition(SlashCollisionPos);
		SlashCollision->GetTransform()->SetLocalScale(SlashCollisionScale);
		AnimationType = "SlashEffect";
		break;
	case PlayerSlashAnimation::Slash2:
		SlashCollision->GetTransform()->SetLocalPosition(SlashCollisionPos);
		SlashCollision->GetTransform()->SetLocalScale(SlashCollisionScale);
		AnimationType = "Slash2Effect";
		break;
	case PlayerSlashAnimation::UpperSlash:
		SlashCollision->GetTransform()->SetLocalPosition(UpperSlashCollisionPos);
		SlashCollision->GetTransform()->SetLocalScale(UpperSlashCollisionScale);
		AnimationType = "UpSlashEffect";
		break;
	case PlayerSlashAnimation::DownSlash:
		SlashCollision->GetTransform()->SetLocalPosition(DownSlashCollisionPos);
		SlashCollision->GetTransform()->SetLocalScale(DownSlashCollisionScale);
		AnimationType = "DownSlashEffect";
		break;
	default:
		break;
	}

	SlashEffectRenderer->ChangeAnimation(AnimationType);
	SlashEffectRenderer->GetTransform()->SetLocalPosition(_Pos);
	SlashEffectRenderer->On();
	IsHit = false;


}