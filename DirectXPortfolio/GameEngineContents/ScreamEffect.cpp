#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ScreamEffect.h"

ScreamEffect::ScreamEffect() 
{
}

ScreamEffect::~ScreamEffect() 
{
}

void ScreamEffect::Start()
{
	ScreamEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPB_Effect);
	ScreamEffectRenderer->CreateAnimation({ .AnimationName = "ScreamEffect", .SpriteName = "92.ScreamEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	ScreamEffectRenderer->SetAnimationStartEvent("ScreamEffect", 1, [this]
		{
			ScreamSkillCollision->On();
		});
	ScreamEffectRenderer->SetAnimationStartEvent("ScreamEffect", 10, [this]
		{
			ScreamSkillCollision->Off();
		});
	ScreamEffectRenderer->ChangeAnimation("ScreamEffect");

	ScreamSkillCollision = CreateComponent<GameEngineCollision>();
	ScreamSkillCollision->SetColType(ColType::AABBBOX2D);
	ScreamSkillCollision->Off();
	ScreamSkillCollision->GetTransform()->SetLocalScale({ 220, 230 });
	ScreamSkillCollision->SetOrder(static_cast<int>(HollowKnightCollisionType::PlayerSkill));

}

void ScreamEffect::Update(float _Delta)
{
	if (true == ScreamEffectRenderer->IsAnimationEnd())
	{
		if (ScreamEffectRenderer != nullptr)
		{
			ScreamEffectRenderer->Death();
			ScreamEffectRenderer = nullptr;
		}

		if (ScreamSkillCollision != nullptr)
		{
			ScreamSkillCollision->Death();
			ScreamSkillCollision = nullptr;
		}

		Death();

	}
}
