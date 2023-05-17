#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// 설명 : 보스 - 공허의 기사 레벨
class HollowKnightLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	HollowKnightLevel();
	~HollowKnightLevel();

	// delete Function
	HollowKnightLevel(const HollowKnightLevel& _Other) = delete;
	HollowKnightLevel(HollowKnightLevel&& _Other) noexcept = delete;
	HollowKnightLevel& operator=(const HollowKnightLevel& _Other) = delete;
	HollowKnightLevel& operator=(HollowKnightLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override {}
	void LevelChangeEnd() override {}


private:

};

