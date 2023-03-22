#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "TestLevel3D.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::GameStart() 
{
	GameEngineCore::CreateLevel<TestLevel3D>();

	GameEngineCore::ChangeLevel("TestLevel3D");
}

void ContentsCore::GameEnd() 
{

}