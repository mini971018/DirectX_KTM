#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 보스 인트로 중 쉴드가 부셔지는 이펙트
class BindBreakEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BindBreakEffect();
	~BindBreakEffect();

	// delete Function
	BindBreakEffect(const BindBreakEffect& _Other) = delete;
	BindBreakEffect(BindBreakEffect&& _Other) noexcept = delete;
	BindBreakEffect& operator=(const BindBreakEffect& _Other) = delete;
	BindBreakEffect& operator=(BindBreakEffect&& _Other) noexcept = delete;

	void SetBindBreakRenderer(float4 _Pos);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BindBreakRenderer;
};

