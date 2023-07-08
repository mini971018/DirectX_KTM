#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HealingEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	HealingEffect();
	~HealingEffect();

	// delete Function
	HealingEffect(const HealingEffect& _Other) = delete;
	HealingEffect(HealingEffect&& _Other) noexcept = delete;
	HealingEffect& operator=(const HealingEffect& _Other) = delete;
	HealingEffect& operator=(HealingEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HealingEffectRenderer;
};

