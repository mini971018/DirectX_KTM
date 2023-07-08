#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FireBallHitWallEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	FireBallHitWallEffect();
	~FireBallHitWallEffect();

	// delete Function
	FireBallHitWallEffect(const FireBallHitWallEffect& _Other) = delete;
	FireBallHitWallEffect(FireBallHitWallEffect&& _Other) noexcept = delete;
	FireBallHitWallEffect& operator=(const FireBallHitWallEffect& _Other) = delete;
	FireBallHitWallEffect& operator=(FireBallHitWallEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HitWallEffect;
};

