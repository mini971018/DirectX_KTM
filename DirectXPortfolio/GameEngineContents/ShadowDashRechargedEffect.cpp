#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "ShadowDashRechargedEffect.h"


ShadowDashRechargedEffect::ShadowDashRechargedEffect() 
{
}

ShadowDashRechargedEffect::~ShadowDashRechargedEffect() 
{
}

void ShadowDashRechargedEffect::Start()
{
	ShadowDashRechargedRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);
	ShadowDashRechargedRenderer->CreateAnimation({ .AnimationName = "ShadowDashRechargedEffect", .SpriteName = "105.ShadowDashRechargedEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	
	ShadowDashRechargedRenderer->SetAnimationStartEvent("ShadowDashRechargedEffect", 17, [this]
		{
			GameEngineSoundPlayer PlayerShadowDashCharge = GameEngineSound::Play("PlayerShadowDashCharge.wav");
		});


	
	ShadowDashRechargedRenderer->GetTransform()->SetLocalPosition({ 0, 50, 0 });
	ShadowDashRechargedRenderer->Off();
}

void ShadowDashRechargedEffect::Update(float _Delta)
{
	if (true == ShadowDashRechargedRenderer->IsAnimationEnd())
	{
		ShadowDashRechargedRenderer->Off();
	}
}

void ShadowDashRechargedEffect::OnRechargedEffect()
{
	ShadowDashRechargedRenderer->On();
	ShadowDashRechargedRenderer->ChangeAnimation("ShadowDashRechargedEffect", true);
}