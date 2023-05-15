#include "PrecompileHeader.h"

#include "MenuTitle.h"

#include <GameEngineCore/GameEngineRenderer.h>

MenuTitle::MenuTitle() 
{
}

MenuTitle::~MenuTitle() 
{
}

void MenuTitle::Start()
{
	TitleImage = CreateComponent<GameEngineRenderer>();
	TitleImage->SetPipeLine("2DTexture");

	TitleImage->GetShaderResHelper().SetTexture("DiffuseTex", "Test.png");
	TitleImage->GetTransform()->SetLocalScale({ 1199, 463 });
	TitleImage->GetTransform()->AddLocalPosition({ 0, 200 });
}