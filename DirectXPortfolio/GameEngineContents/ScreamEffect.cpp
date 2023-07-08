#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "ScreamEffect.h"

ScreamEffect::ScreamEffect() 
{
}

ScreamEffect::~ScreamEffect() 
{
}

void ScreamEffect::Start()
{
	ScreamEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	ScreamEffectRenderer->CreateAnimation({ .AnimationName = "ScreamEffect", .SpriteName = "92.ScreamEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	ScreamEffectRenderer->ChangeAnimation("ScreamEffect");
	//ScreamEffectRenderer->GetTransform()->SetParent(GetTransform());
	//ScreamEffectRenderer->GetTransform()->SetLocalPosition({ 0, 0, 0 });
}

void ScreamEffect::Update(float _Delta)
{
	if (true == ScreamEffectRenderer->IsAnimationEnd())
	{
		if (ScreamEffectRenderer != nullptr)
		{
			ScreamEffectRenderer->Death();
			ScreamEffectRenderer = nullptr;
			Death();
		}
	}
}
