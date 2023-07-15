#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 플레이어 스킬 중 파이어볼
class PlayerFireBall : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerFireBall();
	~PlayerFireBall();

	// delete Function
	PlayerFireBall(const PlayerFireBall& _Other) = delete;
	PlayerFireBall(PlayerFireBall&& _Other) noexcept = delete;
	PlayerFireBall& operator=(const PlayerFireBall& _Other) = delete;
	PlayerFireBall& operator=(PlayerFireBall&& _Other) noexcept = delete;

	void SetFireBall(std::shared_ptr<class GameEngineTexture> _Colmap, float4 _Dir);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FIreBallRenderer;
	
	std::shared_ptr<class GameEngineComponent> Pivot;

	std::shared_ptr<class GameEngineComponent> WallCheckTransform;

	std::shared_ptr<class GameEngineTexture> CurrentColmapTexture;

	const float FireBallSpeed = 2000.0f;

	bool IsWall = false;
	float4 Dir = float4::Right;

	std::shared_ptr<class GameEngineCollision> FireballCollision = nullptr;
};

