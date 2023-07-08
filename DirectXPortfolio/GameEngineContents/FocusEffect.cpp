#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FocusEffect.h"

FocusEffect::FocusEffect() 
{
}

FocusEffect::~FocusEffect() 
{
}



void FocusEffect::Start()
{

	FocusEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	FocusEffectRenderer->CreateAnimation({ .AnimationName = "FocusEffect", .SpriteName = "94.FocusEffect", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	FocusEffectRenderer->CreateAnimation({ .AnimationName = "LoopFocusEffect", .SpriteName = "95.LoopFocusEffect", .FrameInter = 0.06f, .ScaleToTexture = true });
	FocusEffectRenderer->CreateAnimation({ .AnimationName = "EndFocusEffect", .SpriteName = "96.EndFocusEffect", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	FocusEffectRenderer->GetTransform()->SetLocalPosition({ 0.0f, 55.0f });
	FocusEffectRenderer->ChangeAnimation("FocusEffect");

	FocusEffectRenderer->Off();

}

void FocusEffect::Update(float _Delta)
{
	if (true == IsOn && true == FocusEffectRenderer->IsAnimationEnd())
	{
		FocusEffectRenderer->ChangeAnimation("LoopFocusEffect");
	}

	if (false == IsOn && true == FocusEffectRenderer->IsAnimationEnd())
	{
		FocusEffectRenderer->Off();
	}
}

void FocusEffect::OnFocusEffect()
{
	IsOn = true;
	FocusEffectRenderer->On();
	FocusEffectRenderer->ChangeAnimation("FocusEffect");
}

void FocusEffect::OffFocusEffect()
{
	IsOn = false;
	FocusEffectRenderer->ChangeAnimation("EndFocusEffect");
}