#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FireballHitEnemyEffect.h"

FireballHitEnemyEffect::FireballHitEnemyEffect() 
{
}

FireballHitEnemyEffect::~FireballHitEnemyEffect() 
{
}

void FireballHitEnemyEffect::Start()
{
	HitEnemyEffect = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPB_Effect);
	HitEnemyEffect->CreateAnimation({ .AnimationName = "HitSkillEffect", .SpriteName = "85.HitSkillEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	HitEnemyEffect->ChangeAnimation("HitSkillEffect");
	HitEnemyEffect->Off();
}

void FireballHitEnemyEffect::Update(float _Delta)
{
	if (true == HitEnemyEffect->IsAnimationEnd())
	{
		if (HitEnemyEffect != nullptr)
		{
			HitEnemyEffect->Death();
			HitEnemyEffect = nullptr;
			Death();
		}
	}
}

void FireballHitEnemyEffect::SetFireballHitEffect(float4 _Pos, float4 _Scale)
{
	GetTransform()->SetWorldPosition(_Pos);
	GetTransform()->SetWorldScale(_Scale);

	HitEnemyEffect->ChangeAnimation("HitSkillEffect");
	HitEnemyEffect->On();
}