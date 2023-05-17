#include "PrecompileHeader.h"

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
	BackGroundImage->GetTransform()->AddLocalPosition({ 0, 0, -70 });  //원본 크기 기준 z -> -70.0f
}