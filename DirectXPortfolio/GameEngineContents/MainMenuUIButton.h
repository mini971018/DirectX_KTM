#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
class MainMenuUIButton : public GameEngineActor
{
public:
	// constrcuter destructer
	MainMenuUIButton();
	~MainMenuUIButton();

	// delete Function
	MainMenuUIButton(const MainMenuUIButton& _Other) = delete;
	MainMenuUIButton(MainMenuUIButton&& _Other) noexcept = delete;
	MainMenuUIButton& operator=(const MainMenuUIButton& _Other) = delete;
	MainMenuUIButton& operator=(MainMenuUIButton&& _Other) noexcept = delete;

	void SetButton(std::string_view _Name);
	void SetSelectState(bool _IsSelect);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> LeftArrowRenderer;
	std::shared_ptr<GameEngineUIRenderer> RightArrowRenderer;
	std::shared_ptr<GameEngineUIRenderer> ButtonRenderer;

	bool SelectState = false;
};

