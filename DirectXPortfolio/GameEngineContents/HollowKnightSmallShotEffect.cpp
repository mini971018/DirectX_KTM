#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "HollowKnightSmallShotEffect.h"

HollowKnightSmallShotEffect::HollowKnightSmallShotEffect() 
{
}

HollowKnightSmallShotEffect::~HollowKnightSmallShotEffect() 
{
}

void HollowKnightSmallShotEffect::Start()
{
	ShotEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	ShotEffectRenderer->CreateAnimation({ .AnimationName = "EffectSmallShot", .SpriteName = "27.EffectSmallShot", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	ShotEffectRenderer->ChangeAnimation("EffectSmallShot");
	ShotEffectRenderer->Off();
}



void HollowKnightSmallShotEffect::OnEffect()
{
	ShotEffectRenderer->ChangeAnimation("EffectSmallShot");
	ShotEffectRenderer->On();
}

void HollowKnightSmallShotEffect::OffEffect()
{
	ShotEffectRenderer->Off();
}