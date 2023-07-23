#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GetDamageEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	GetDamageEffect();
	~GetDamageEffect();

	// delete Function
	GetDamageEffect(const GetDamageEffect& _Other) = delete;
	GetDamageEffect(GetDamageEffect&& _Other) noexcept = delete;
	GetDamageEffect& operator=(const GetDamageEffect& _Other) = delete;
	GetDamageEffect& operator=(GetDamageEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> GetDamageEffectRenderer;
};

