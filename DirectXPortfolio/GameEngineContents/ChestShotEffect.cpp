#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "ChestShotEffect.h"

ChestShotEffect::ChestShotEffect() 
{
}

ChestShotEffect::~ChestShotEffect() 
{
}

void ChestShotEffect::Start()
{
	ChestShotEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	ChestShotEffectRenderer->CreateAnimation({ .AnimationName = "EffectChestShot", .SpriteName = "48.EffectChestShot", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	ChestShotEffectRenderer->ChangeAnimation("EffectChestShot");
	ChestShotEffectRenderer->Off();
}

void ChestShotEffect::OnEffect()
{
	ChestShotEffectRenderer->ChangeAnimation("EffectChestShot");
	ChestShotEffectRenderer->On();
}

void ChestShotEffect::OffEffect()
{
	ChestShotEffectRenderer->Off();
}