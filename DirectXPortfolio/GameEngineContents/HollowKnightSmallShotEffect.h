#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class HollowKnightSmallShotEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	HollowKnightSmallShotEffect();
	~HollowKnightSmallShotEffect();

	// delete Function
	HollowKnightSmallShotEffect(const HollowKnightSmallShotEffect& _Other) = delete;
	HollowKnightSmallShotEffect(HollowKnightSmallShotEffect&& _Other) noexcept = delete;
	HollowKnightSmallShotEffect& operator=(const HollowKnightSmallShotEffect& _Other) = delete;
	HollowKnightSmallShotEffect& operator=(HollowKnightSmallShotEffect&& _Other) noexcept = delete;

	void OnEffect();
	void OffEffect();

protected:
	void Start();
	void Update(float _Delta) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ShotEffectRenderer = nullptr;
};

