#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

// ���� : ���� ���۽�, ���� ���� �� ���θ޴��� �����ִ� ����
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

	std::shared_ptr<class FadeEffect> FEffect;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	GameEngineSoundPlayer BgmPlayer;

	std::shared_ptr<class MainMenuUIManager> MainMenuUIManagerActor;

	bool LevelChangeState = false;
	float CalTime = 0.0f;
};

