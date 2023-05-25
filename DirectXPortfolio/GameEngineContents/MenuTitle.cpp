#include "PrecompileHeader.h"

#include "MenuTitle.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

MenuTitle::MenuTitle() 
{
}

MenuTitle::~MenuTitle() 
{
}

void MenuTitle::Start()
{
	TitleImage = CreateComponent<GameEngineSpriteRenderer>();

	TitleImage->SetTexture("MenuTitle.png");
	TitleImage->GetTransform()->SetLocalScale({ 1199, 463 });

	TitleImage->GetTransform()->AddLocalPosition({ 0, 200, -70 });
}