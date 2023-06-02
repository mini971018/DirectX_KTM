#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : ���� ��Ʈ�� �� ���尡 �μ����� ����Ʈ
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

