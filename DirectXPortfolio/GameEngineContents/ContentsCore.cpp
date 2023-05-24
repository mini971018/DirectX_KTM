
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

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::GameStart() 
{
	GameEngineCore::CreateLevel<MainMenuLevel>();
	GameEngineCore::CreateLevel<HollowKnightLevel>();
	GameEngineCore::CreateLevel<TestLevel3D>();

	GameEngineCore::ChangeLevel("MainMenuLevel");
}

void ContentsCore::GameEnd() 
{

}

void ContentsCore::ContentsResourcesCreate()
{
	// 텍스처 로드만 각 레벨별로 하고 정리하는 습관을 들이세요.

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("ContentsShader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		// 쉐이더 자동컴파일
		GameEngineVertexShader::Load(Files[0].GetFullPath(), "MyShader_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "MyShader_PS");
	}

	//{
	//	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("My2DTexture");

	//	Pipe->SetVertexBuffer("Rect");
	//	Pipe->SetIndexBuffer("Rect");
	//	Pipe->SetVertexShader("MyShader.fx");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("MyShader.fx");
	//	Pipe->SetBlendState("AlphaBlend");
	//	Pipe->SetDepthState("EngineDepth");
	//}



}