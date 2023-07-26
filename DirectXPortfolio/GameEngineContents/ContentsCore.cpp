
#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

#include "MainMenuLevel.h"
#include "HollowKnightLevel.h"
#include "TestLevel3D.h"
#include "EndLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::GameStart() 
{
	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<MainMenuLevel>();
	GameEngineCore::CreateLevel<HollowKnightLevel>();
	GameEngineCore::CreateLevel<EndLevel>();
	
	//GameEngineCore::CreateLevel<TestLevel3D>();
	GameEngineCore::ChangeLevel("MainMenuLevel");
}

void ContentsCore::GameEnd() 
{

}
