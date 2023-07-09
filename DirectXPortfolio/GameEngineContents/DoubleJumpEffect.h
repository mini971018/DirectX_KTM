#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class DoubleJumpEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	DoubleJumpEffect();
	~DoubleJumpEffect();

	// delete Function
	DoubleJumpEffect(const DoubleJumpEffect& _Other) = delete;
	DoubleJumpEffect(DoubleJumpEffect&& _Other) noexcept = delete;
	DoubleJumpEffect& operator=(const DoubleJumpEffect& _Other) = delete;
	DoubleJumpEffect& operator=(DoubleJumpEffect&& _Other) noexcept = delete;

	void JumpEffectOn();
	void JumpEffectOff();

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> JumpEffectRenderer;

};

