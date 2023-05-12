#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 메뉴 BG
class MenuBG : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuBG();
	~MenuBG();

	// delete Function
	MenuBG(const MenuBG& _Other) = delete;
	MenuBG(MenuBG&& _Other) noexcept = delete;
	MenuBG& operator=(const MenuBG& _Other) = delete;
	MenuBG& operator=(MenuBG&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override {}
	void Render(float _Delta) override {}

private:
	std::shared_ptr<class GameEngineRenderer>  BackGroundImage;
};

