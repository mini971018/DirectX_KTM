#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "HollowKnightBlasts.h"

HollowKnightBlasts::HollowKnightBlasts() 
{
}

HollowKnightBlasts::~HollowKnightBlasts() 
{
}



void HollowKnightBlasts::Start()
{
	BlastsRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	BlastsRenderer->CreateAnimation({ .AnimationName = "AnticEffectBlasts", .SpriteName = "31.AnticEffectBlasts", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = false });
	BlastsRenderer->CreateAnimation({ .AnimationName = "EffectBlasts", .SpriteName = "32.EffectBlasts", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = false });
	BlastsRenderer->SetAnimationStartEvent("EffectBlasts", 2, [this]
		{
			BlastsCollision->On();
		});
	BlastsRenderer->SetAnimationStartEvent("EffectBlasts", 9, [this]
		{
			BlastsCollision->Off();
		});
	BlastsRenderer->ChangeAnimation("AnticEffectBlasts");
	BlastsRenderer->GetTransform()->SetLocalPosition({ 0.0f, 200.0f, 0.0f });
	BlastsRenderer->GetTransform()->SetLocalScale({ 360.0f, 415.0f, 1.0f });
	BlastsRenderer->On();

	BlastsCollision = CreateComponent<GameEngineCollision>();
	BlastsCollision->SetColType(ColType::AABBBOX2D);
	BlastsCollision->GetTransform()->SetLocalScale({ 125.0f, 900.5f, 1.0f });
	BlastsCollision->SetOrder(static_cast<int>(HollowKnightCollisionType::BossAttack));
	BlastsCollision->Off();
}

void HollowKnightBlasts::Update(float _Delta)
{
	if (true == BlastsRenderer->IsAnimationEnd() && false == IsBlasts)
	{
		IsBlasts = true;
		BlastsRenderer->ChangeAnimation("EffectBlasts");

		BlastsRenderer->GetTransform()->SetLocalPosition({ 0.0f, 450.0f, 0.0f });
		BlastsRenderer->GetTransform()->SetLocalScale({ 400.0f, 900.5f, 1.0f });

		BlastsCollision->GetTransform()->SetLocalPosition({ 10.0f, 450.0f, 0.0f });

		BlastsCollision->On();
	}

	if (true == BlastsRenderer->IsAnimationEnd() && true == IsBlasts)
	{
		if (BlastsRenderer != nullptr)
		{
			BlastsRenderer->Death();
			BlastsRenderer = nullptr;
			Death();
		}

		if (BlastsCollision != nullptr)
		{
			BlastsCollision->Death();
			BlastsCollision = nullptr;
			Death();
		}

		Death();
	}
	
}
