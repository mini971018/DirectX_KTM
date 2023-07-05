#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : �÷��̾��� ShadowDash�� �غ�Ǿ����� �˷��ִ� ����Ʈ
class ShadowDashRechargedEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ShadowDashRechargedEffect();
	~ShadowDashRechargedEffect();

	// delete Function
	ShadowDashRechargedEffect(const ShadowDashRechargedEffect& _Other) = delete;
	ShadowDashRechargedEffect(ShadowDashRechargedEffect&& _Other) noexcept = delete;
	ShadowDashRechargedEffect& operator=(const ShadowDashRechargedEffect& _Other) = delete;
	ShadowDashRechargedEffect& operator=(ShadowDashRechargedEffect&& _Other) noexcept = delete;

	void OnRechargedEffect();

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ShadowDashRechargedRenderer;


};

