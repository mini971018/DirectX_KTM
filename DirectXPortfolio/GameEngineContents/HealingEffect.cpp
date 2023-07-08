#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "HealingEffect.h"

HealingEffect::HealingEffect() 
{
}

HealingEffect::~HealingEffect() 
{
}

void HealingEffect::Start()
{
	HealingEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);
	HealingEffectRenderer->CreateAnimation({ .AnimationName = "HealingEffect", .SpriteName = "97.HealingEffect", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	//HealingEffectRenderer->GetTransform()->SetLocalPosition({ 0.0f, .0f });
	HealingEffectRenderer->ChangeAnimation("HealingEffect");
}

void HealingEffect::Update(float _Delta)
{
	if (true == HealingEffectRenderer->IsAnimationEnd())
	{
		if (HealingEffectRenderer != nullptr)
		{
			HealingEffectRenderer->Death();
			HealingEffectRenderer = nullptr;
			Death();
		}
	}
}