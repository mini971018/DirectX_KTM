#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

// ���� :
class HollowKnightBoss : public GameEngineActor
{
public:
	// constrcuter destructer
	HollowKnightBoss();
	~HollowKnightBoss();

	// delete Function
	HollowKnightBoss(const HollowKnightBoss& _Other) = delete;
	HollowKnightBoss(HollowKnightBoss&& _Other) noexcept = delete;
	HollowKnightBoss& operator=(const HollowKnightBoss& _Other) = delete;
	HollowKnightBoss& operator=(HollowKnightBoss&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) {}
	void LevelChangeStart() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BossRender;

	void SpriteInit();
	void AnimationInit();

	GameEngineFSM FSM;
	void StateInit();  //���� �ӽ� ������Ʈ�� init

	float StateCalTime = 0.0f;
};

