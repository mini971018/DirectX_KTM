#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Slam Effect
class SlamEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	SlamEffect();
	~SlamEffect();

	// delete Function
	SlamEffect(const SlamEffect& _Other) = delete;
	SlamEffect(SlamEffect&& _Other) noexcept = delete;
	SlamEffect& operator=(const SlamEffect& _Other) = delete;
	SlamEffect& operator=(SlamEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SlamEffectRenderer;
};

