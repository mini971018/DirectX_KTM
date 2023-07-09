#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "DoubleJumpEffect.h"

DoubleJumpEffect::DoubleJumpEffect() 
{
}

DoubleJumpEffect::~DoubleJumpEffect() 
{
}


void DoubleJumpEffect::Start()
{
	JumpEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPB_Effect);
	JumpEffectRenderer->CreateAnimation({ .AnimationName = "DoubleJumpEffect", .SpriteName = "102.DoubleJumpEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	JumpEffectRenderer->GetTransform()->SetLocalPosition({0.0f, 100.0f});
	JumpEffectRenderer->GetTransform()->SetLocalScale({ 0.8f, 0.8f });
	JumpEffectRenderer->ChangeAnimation("DoubleJumpEffect");
	JumpEffectRenderer->Off();
}

void DoubleJumpEffect::Update(float _Delta)
{
	if (true == JumpEffectRenderer->IsAnimationEnd())
	{
		JumpEffectRenderer->Off();
	}
}

void DoubleJumpEffect::JumpEffectOn()
{
	JumpEffectRenderer->ChangeAnimation("DoubleJumpEffect");
	JumpEffectRenderer->On();
}

void DoubleJumpEffect::JumpEffectOff()
{
	JumpEffectRenderer->Off();
}