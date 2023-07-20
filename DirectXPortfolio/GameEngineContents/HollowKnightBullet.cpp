#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "HollowKnightBullet.h"

HollowKnightBullet::HollowKnightBullet() 
{
}

HollowKnightBullet::~HollowKnightBullet() 
{
}

void HollowKnightBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::BFPF_Effect);
	BulletRenderer->CreateAnimation({ .AnimationName = "HollowKnightBulletSplash", .SpriteName = "97.HollowKnightBulletSplash", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	BulletRenderer->CreateAnimation({ .AnimationName = "HollowKnightBullet", .SpriteName = "98.HollowKnightBullet", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = false });
	BulletRenderer->ChangeAnimation("HollowKnightBullet");
	//BulletRenderer->GetTransform()->SetLocalPosition({ 0.0f, 200.0f, 0.0f });
	BulletRenderer->GetTransform()->SetLocalScale({ 122.0f, 60.0f, 1.0f });
	BulletRenderer->On();

	BulletCollision = CreateComponent<GameEngineCollision>();
	BulletCollision->SetColType(ColType::SPHERE2D);
	BulletCollision->GetTransform()->SetLocalScale({ 40.0f, 40.0f, 1.0f });
	BulletCollision->GetTransform()->SetLocalPosition({ 37.0f, 0.0f, 0.0f });
	BulletCollision->SetOrder(static_cast<int>(HollowKnightCollisionType::BossAttack));

	WallCheckTransform = CreateComponent<GameEngineComponent>();
	WallCheckTransform->GetTransform()->SetParent(GetTransform());
	WallCheckTransform->GetTransform()->SetLocalPosition({ 50.0f, 0.0f });
}

void HollowKnightBullet::Update(float _Delta)
{
	if (false == IsWall)
	{
		//그래비티
		Dir += float4::Down * Gravity * _Delta;

		float angle = float4::GetAngleVectorToVectorDeg360(GetAngleVector.NormalizeReturn(), Dir.NormalizeReturn());

		GetTransform()->SetWorldRotation({ 0, 0, angle });
		GetTransform()->AddWorldPosition(Dir * _Delta);

		if (nullptr != CurrentColmapTexture)
		{
			float4 Pos = WallCheckTransform->GetTransform()->GetWorldPosition();

			if (GameEnginePixelColor::Black == CurrentColmapTexture->GetPixel(static_cast<int>(Pos.x), static_cast<int>(-Pos.y)))
			{
				//BulletRenderer->GetTransform()->SetLocalScale({ 68.0f, 79.0f, 1.0f });
				GetTransform()->SetLocalScale({ 1.5f, 1.5f, 1.0f });
				BulletRenderer->GetTransform()->SetLocalRotation({ 0, 0, 90 });
				BulletRenderer->ChangeAnimation("HollowKnightBulletSplash");
				BulletCollision->Off();

				BulletRenderer->ColorOptionValue.PlusColor = SplashColor;
				BulletRenderer->ColorOptionValue.MulColor = SplashColor;
				BulletRenderer->ColorOptionValue.MulColor.a = 1.0f;

				IsWall = true;
			}
		}
	}
	else
	{
		if (true == BulletRenderer->IsAnimationEnd())
		{
			if (BulletRenderer != nullptr)
			{
				BulletRenderer->Death();
				BulletRenderer = nullptr;
			}

			if (BulletCollision != nullptr)
			{
				BulletCollision->Death();
				BulletCollision = nullptr;
			}

			if (WallCheckTransform != nullptr)
			{
				WallCheckTransform->Death();
				WallCheckTransform = nullptr;
			}
			Death();
		}
	}
}

void HollowKnightBullet::SetBullet(std::shared_ptr<class GameEngineTexture> _Colmap, float4 _Dir, float _Force)
{
	Dir = _Dir.NormalizeReturn();
	CurrentColmapTexture = _Colmap;

	Dir *= _Force;
}