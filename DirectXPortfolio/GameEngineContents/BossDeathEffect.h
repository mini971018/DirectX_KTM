#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BossDeathEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BossDeathEffect();
	~BossDeathEffect();

	// delete Function
	BossDeathEffect(const BossDeathEffect& _Other) = delete;
	BossDeathEffect(BossDeathEffect&& _Other) noexcept = delete;
	BossDeathEffect& operator=(const BossDeathEffect& _Other) = delete;
	BossDeathEffect& operator=(BossDeathEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BossDeathEffectActor = nullptr;
};

