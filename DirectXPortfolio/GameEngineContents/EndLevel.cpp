#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineVideo.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "EndLevel.h"

EndLevel::EndLevel() 
{
}

EndLevel::~EndLevel() 
{
}


void EndLevel::Start()
{
	//메인 메뉴에서 사용될 리소스 가져옴
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Movie");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	
}

void EndLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsUp("TestButton2"))
	{

	}

	//if (EndingVideo->IsFinished() == true)
	//{
	//	GameEngineCore::ChangeLevel("MainMenuLevel");
	//}
}


void EndLevel::LevelChangeStart()
{
}

void EndLevel::LevelChangeEnd()
{

}