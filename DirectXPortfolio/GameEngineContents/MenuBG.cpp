#include "MenuBG.h"

#include "PrecompileHeader.h"
#include <GameEngineCore/GameEngineRenderer.h>

MenuBG::MenuBG() 
{
}

MenuBG::~MenuBG() 
{
}

void MenuBG::Start()
{
	BackGroundImage = CreateComponent<GameEngineRenderer>();
	BackGroundImage->SetPipeLine("2DTexture");

	BackGroundImage->GetShaderResHelper().SetTexture("DiffuseTex", "MenuBG.png");
	BackGroundImage->GetTransform()->SetLocalScale({1930, 1080});
}