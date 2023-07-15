#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "FireBallHitWallEffect.h"

#include "PlayerFireBall.h"

PlayerFireBall::PlayerFireBall() 
{
}

PlayerFireBall::~PlayerFireBall() 
{
}

void PlayerFireBall::Start()
{
	FIreBallRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPB_Effect);
	FIreBallRenderer->CreateAnimation({ .AnimationName = "AnticFireBallEffect", .SpriteName = "87.AnticFireBallEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	FIreBallRenderer->CreateAnimation({ .AnimationName = "LoopFireBallEffect", .SpriteName = "88.LoopFireBallEffect", .FrameInter = 0.04f, .Loop = true, .ScaleToTexture = true });
	FIreBallRenderer->CreateAnimation({ .AnimationName = "EndFireBallEffect", .SpriteName = "89.EndFireBallEffect", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
	FIreBallRenderer->ChangeAnimation("AnticFireBallEffect");

	if (nullptr == Pivot)
	{
		Pivot = CreateComponent<GameEngineComponent>();
	}

	if (nullptr == WallCheckTransform)
	{
		WallCheckTransform = CreateComponent<GameEngineComponent>();
	}

	FIreBallRenderer->GetTransform()->SetParent(Pivot->GetTransform());
	WallCheckTransform->GetTransform()->SetParent(Pivot->GetTransform());
	WallCheckTransform->GetTransform()->SetLocalPosition({ 100.0f, 0.0f });

	FireballCollision = CreateComponent<GameEngineCollision>();
	FireballCollision->SetColType(ColType::AABBBOX2D);
	FireballCollision->On();
	FireballCollision->GetTransform()->SetLocalScale({ 105, 67 });
	FireballCollision->SetOrder(static_cast<int>(HollowKnightCollisionType::PlayerSkill));
}

void PlayerFireBall::Update(float _Delta)
{
	if (true == IsWall)
	{
		if (true == FIreBallRenderer->IsAnimationEnd())
		{
			if (FIreBallRenderer != nullptr)
			{
				FIreBallRenderer->Death();
				FIreBallRenderer = nullptr;
			}

			if (FireballCollision != nullptr)
			{
				FireballCollision->Death();
				FireballCollision = nullptr;
			}

			Death();
		}
	}
	else
	{
		if (true == FIreBallRenderer->IsAnimationEnd())
		{
			FIreBallRenderer->ChangeAnimation("LoopFireBallEffect");
		}

		if (nullptr != CurrentColmapTexture)
		{
			float4 Pos = WallCheckTransform->GetTransform()->GetWorldPosition();

			if (GameEnginePixelColor::Black == CurrentColmapTexture->GetPixel(static_cast<int>(Pos.x), static_cast<int>(-Pos.y)))
			{
				FIreBallRenderer->ChangeAnimation("EndFireBallEffect");

				std::shared_ptr<class FireBallHitWallEffect> HitWallEffect = GetLevel()->CreateActor<FireBallHitWallEffect>();
				HitWallEffect->GetTransform()->SetWorldPosition(WallCheckTransform->GetTransform()->GetWorldPosition());

				if (float4::Left == Dir)
				{
					HitWallEffect->GetTransform()->SetLocalNegativeScaleX();
				}

				IsWall = true;
			}
		}

		GetTransform()->AddLocalPosition(Dir * FireBallSpeed * _Delta);
	}
}

void PlayerFireBall::SetFireBall(std::shared_ptr<class GameEngineTexture> _Colmap, float4 _Dir)
{
	CurrentColmapTexture = _Colmap;
	Dir = _Dir;


	if (float4::Left == _Dir)
	{
		Pivot->GetTransform()->SetLocalNegativeScaleX();
		FireballCollision->GetTransform()->SetLocalPosition({ -50, -5 });
	}
	else
	{
		FireballCollision->GetTransform()->SetLocalPosition({ 50, -5 });
	}
	

}