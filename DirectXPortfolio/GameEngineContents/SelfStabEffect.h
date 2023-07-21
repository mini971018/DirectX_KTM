#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SelfStabEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	SelfStabEffect();
	~SelfStabEffect();

	// delete Function
	SelfStabEffect(const SelfStabEffect& _Other) = delete;
	SelfStabEffect(SelfStabEffect&& _Other) noexcept = delete;
	SelfStabEffect& operator=(const SelfStabEffect& _Other) = delete;
	SelfStabEffect& operator=(SelfStabEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SelfStabEffectRenderer;
};

