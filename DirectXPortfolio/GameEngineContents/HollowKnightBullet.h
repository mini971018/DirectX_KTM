#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HollowKnightBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	HollowKnightBullet();
	~HollowKnightBullet();

	// delete Function
	HollowKnightBullet(const HollowKnightBullet& _Other) = delete;
	HollowKnightBullet(HollowKnightBullet&& _Other) noexcept = delete;
	HollowKnightBullet& operator=(const HollowKnightBullet& _Other) = delete;
	HollowKnightBullet& operator=(HollowKnightBullet&& _Other) noexcept = delete;

	void SetBullet(std::shared_ptr<class GameEngineTexture> _Colmap, float4 _Dir, float _Force);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer>  BulletRenderer = nullptr;
	std::shared_ptr<class GameEngineCollision> BulletCollision = nullptr;
	std::shared_ptr<class GameEngineComponent> WallCheckTransform = nullptr;

	std::shared_ptr<class GameEngineTexture> CurrentColmapTexture;

	float4 Dir = float4::Zero;

	bool IsWall = false;

	const float Gravity = 1200.0f;

	const float4 GetAngleVector = { 1, 0, 0 };

	const float4 SplashColor = float4{ static_cast<float>((201.0f * 0.75f) / 255.0f) , static_cast<float>((84.0f * 0.75f) / 255.0f), static_cast<float>((16.0f * 0.75f) / 255.0f) , 0 };
};

