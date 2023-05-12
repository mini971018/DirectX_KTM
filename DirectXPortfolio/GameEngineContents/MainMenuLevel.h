#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// 설명 : 게임 시작시, 시작 종료 등 메인메뉴를 보여주는 레벨
class MainMenuLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MainMenuLevel();
	~MainMenuLevel();

	// delete Function
	MainMenuLevel(const MainMenuLevel& _Other) = delete;
	MainMenuLevel(MainMenuLevel&& _Other) noexcept = delete;
	MainMenuLevel& operator=(const MainMenuLevel& _Other) = delete;
	MainMenuLevel& operator=(MainMenuLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override {}
	void LevelChangeEnd() override {}

private:

};

