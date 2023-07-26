#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HollowKnightDashEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	HollowKnightDashEffect();
	~HollowKnightDashEffect();

	// delete Function
	HollowKnightDashEffect(const HollowKnightDashEffect& _Other) = delete;
	HollowKnightDashEffect(HollowKnightDashEffect&& _Other) noexcept = delete;
	HollowKnightDashEffect& operator=(const HollowKnightDashEffect& _Other) = delete;
	HollowKnightDashEffect& operator=(HollowKnightDashEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DashEffectRenderer;

};

