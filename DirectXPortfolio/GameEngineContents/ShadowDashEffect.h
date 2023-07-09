#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ShadowDashEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ShadowDashEffect();
	~ShadowDashEffect();

	// delete Function
	ShadowDashEffect(const ShadowDashEffect& _Other) = delete;
	ShadowDashEffect(ShadowDashEffect&& _Other) noexcept = delete;
	ShadowDashEffect& operator=(const ShadowDashEffect& _Other) = delete;
	ShadowDashEffect& operator=(ShadowDashEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ShadowDashEffectRenderer;
};

