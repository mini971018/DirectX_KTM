#include "PrecompileHeader.h"

#include "MenuBG.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

MenuBG::MenuBG() 
{
}

MenuBG::~MenuBG() 
{
}

void MenuBG::Start()
{
	BackGroundImage = CreateComponent<GameEngineSpriteRenderer>();

	BackGroundImage->SetTexture("MenuBG.png");
	BackGroundImage->GetTransform()->SetLocalScale({1930, 1080});
	BackGroundImage->GetTransform()->AddLocalPosition({ 0, 0, -70 });  //���� ũ�� ���� z -> -70.0f

}