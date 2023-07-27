#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MainMenuUIManager : public GameEngineActor
{
public:
	// constrcuter destructer
	MainMenuUIManager();
	~MainMenuUIManager();

	// delete Function
	MainMenuUIManager(const MainMenuUIManager& _Other) = delete;
	MainMenuUIManager(MainMenuUIManager&& _Other) noexcept = delete;
	MainMenuUIManager& operator=(const MainMenuUIManager& _Other) = delete;
	MainMenuUIManager& operator=(MainMenuUIManager&& _Other) noexcept = delete;

	void ResetUIManager(std::shared_ptr<class FadeEffect> _FEffect, GameEngineSoundPlayer _BGMPlayer);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	int CurrentSelectNum = 0;
	int SelectNum = 0;

	int ButtonCount = 0;

	std::vector<std::shared_ptr<class MainMenuUIButton>> UIButtonVector;

	void EnterUI();
	void InitUIButton();
	int ReturnClampNum(int _Num);

	bool IsLevelChangeState = false;
	float CalStateTime = 0.0f;

	GameEngineSoundPlayer BgmPlayer;
	std::shared_ptr<class FadeEffect> FEffect;
	bool LevelChangeState = false;
};

