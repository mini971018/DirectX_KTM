#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "EndingVideo.h"
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
	NewDir.Move("Texture");
	NewDir.Move("Ending");

	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EndingVideo").GetFullPath());

	EndingVideoObject = CreateActor<EndingVideo>();

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	
}

void EndLevel::Update(float _DeltaTime)
{

}

void EndLevel::LevelChangeStart()
{
	EndingVideoObject->StartVideo();
}

void EndLevel::LevelChangeEnd()
{

}