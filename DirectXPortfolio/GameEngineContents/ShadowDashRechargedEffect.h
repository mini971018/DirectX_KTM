#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 플레이어의 ShadowDash가 준비되었는지 알려주는 이펙트
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

