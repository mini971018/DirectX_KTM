#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "GetDamageEffect.h"

GetDamageEffect::GetDamageEffect() 
{
}

GetDamageEffect::~GetDamageEffect() 
{
}

void GetDamageEffect::Start()
{
	GetDamageEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperEffect);

	GetDamageEffectRenderer->CreateAnimation({ .AnimationName = "GetDamagedEffect", .SpriteName = "81.GetDamagedEffect", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	GetDamageEffectRenderer->ChangeAnimation("GetDamagedEffect");
}

void GetDamageEffect::Update(float _Delta)
{
	if (true == GetDamageEffectRenderer->IsAnimationEnd())
	{
		if (GetDamageEffectRenderer != nullptr)
		{
			GetDamageEffectRenderer->Death();
			GetDamageEffectRenderer = nullptr;
			Death();
		}
	}

}
