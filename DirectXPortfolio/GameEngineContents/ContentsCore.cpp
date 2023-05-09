#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>

#include "MainMenuLevel.h"
#include "TestLevel3D.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::GameStart() 
{
	GameEngineCore::CreateLevel<MainMenuLevel>();
	GameEngineCore::CreateLevel<TestLevel3D>();

	GameEngineCore::ChangeLevel("MainMenuLevel");
}

void ContentsCore::GameEnd() 
{

}