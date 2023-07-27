#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerDeathEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerDeathEffect();
	~PlayerDeathEffect();

	// delete Function
	PlayerDeathEffect(const PlayerDeathEffect& _Other) = delete;
	PlayerDeathEffect(PlayerDeathEffect&& _Other) noexcept = delete;
	PlayerDeathEffect& operator=(const PlayerDeathEffect& _Other) = delete;
	PlayerDeathEffect& operator=(PlayerDeathEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DeathEffect;
};

