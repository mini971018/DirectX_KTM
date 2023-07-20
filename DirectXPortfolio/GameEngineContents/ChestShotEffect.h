#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ChestShotEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ChestShotEffect();
	~ChestShotEffect();

	// delete Function
	ChestShotEffect(const ChestShotEffect& _Other) = delete;
	ChestShotEffect(ChestShotEffect&& _Other) noexcept = delete;
	ChestShotEffect& operator=(const ChestShotEffect& _Other) = delete;
	ChestShotEffect& operator=(ChestShotEffect&& _Other) noexcept = delete;

	void OnEffect();
	void OffEffect();

protected:
	void Start();
	void Update(float _Delta) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ChestShotEffectRenderer = nullptr;
};

