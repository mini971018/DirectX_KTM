#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "DashEffect.h"

DashEffect::DashEffect() 
{
}

DashEffect::~DashEffect() 
{
}

void DashEffect::Start()
{
	DashEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPB_Effect);
	DashEffectRenderer->CreateAnimation({ .AnimationName = "DashEffect", .SpriteName = "103.DashEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	DashEffectRenderer->GetTransform()->SetLocalPosition({ -160.0f, 30.0f });
	DashEffectRenderer->ChangeAnimation("DashEffect");
	DashEffectRenderer->Off();
}

void DashEffect::Update(float _Delta)
{
	if (true == DashEffectRenderer->IsAnimationEnd())
	{
		DashEffectRenderer->Off();
	}
}

void DashEffect::OnDashEffect()
{
	DashEffectRenderer->On();
	DashEffectRenderer->ChangeAnimation("DashEffect");
}