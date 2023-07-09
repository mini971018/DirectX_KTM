#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	SlashEffectRenderer->CreateAnimation({ .AnimationName = "Slash2Effect", .SpriteName = "99.Slash2Effect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	SlashEffectRenderer->CreateAnimation({ .AnimationName = "UpSlashEffect", .SpriteName = "100.UpSlashEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	SlashEffectRenderer->CreateAnimation({ .AnimationName = "DownSlashEffect", .SpriteName = "101.DownSlashEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });

	SlashEffectRenderer->ChangeAnimation("SlashEffect");

	SlashEffectRenderer->Off();
}

void SlashEffect::Update(float _Delta)
{
	if (true == SlashEffectRenderer->IsAnimationEnd())
	{
		SlashEffectRenderer->Off();
	}
}

void SlashEffect::SetSlashEffect(PlayerSlashAnimation _SlashType, float4 _Pos)
{
	std::string_view AnimationType = "";

	switch (_SlashType)
	{
	case PlayerSlashAnimation::Slash1:
		AnimationType = "SlashEffect";
		break;
	case PlayerSlashAnimation::Slash2:
		AnimationType = "Slash2Effect";
		break;
	case PlayerSlashAnimation::UpperSlash:
		AnimationType = "UpSlashEffect";
		break;
	case PlayerSlashAnimation::DownSlash:
		AnimationType = "DownSlashEffect";
		break;
	default:
		break;
	}

	SlashEffectRenderer->ChangeAnimation(AnimationType);
	SlashEffectRenderer->GetTransform()->SetLocalPosition(_Pos);
	SlashEffectRenderer->On();
}