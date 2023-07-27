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
	BackGroundImage = CreateComponent<GameEngineSpriteRenderer>(UIRenderOrder::Title);

	BackGroundImage->SetScaleToTexture("MenuBG.png");
	BackGroundImage->GetTransform()->AddLocalPosition({ 0, 0, -70 });  //원본 크기 기준 z -> -70.0f

}