#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 : 보스의 Roar Effect
class RoarEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	RoarEffect();
	~RoarEffect();

	// delete Function
	RoarEffect(const RoarEffect& _Other) = delete;
	RoarEffect(RoarEffect&& _Other) noexcept = delete;
	RoarEffect& operator=(const RoarEffect& _Other) = delete;
	RoarEffect& operator=(RoarEffect&& _Other) noexcept = delete;

	void SetRoarEffect(RoarType _Type, float4 Pos);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RoarEffectRenderer;
};

