#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 플레이어 Focus Effect
class FocusEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	FocusEffect();
	~FocusEffect();

	// delete Function
	FocusEffect(const FocusEffect& _Other) = delete;
	FocusEffect(FocusEffect&& _Other) noexcept = delete;
	FocusEffect& operator=(const FocusEffect& _Other) = delete;
	FocusEffect& operator=(FocusEffect&& _Other) noexcept = delete;

	void OnFocusEffect();
	void OffFocusEffect();

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FocusEffectRenderer;

	bool IsOn = false;
};

