#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 메뉴 타이틀
class MenuTitle : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuTitle();
	~MenuTitle();

	// delete Function
	MenuTitle(const MenuTitle& _Other) = delete;
	MenuTitle(MenuTitle&& _Other) noexcept = delete;
	MenuTitle& operator=(const MenuTitle& _Other) = delete;
	MenuTitle& operator=(MenuTitle&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override {}
	void Render(float _Delta) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> TitleImage;
};

