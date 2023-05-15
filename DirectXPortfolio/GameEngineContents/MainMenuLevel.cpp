#include "PrecompileHeader.h"

#include "MainMenuLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "MenuBG.h"
#include "MenuTitle.h"

MainMenuLevel::MainMenuLevel() 
{
}

MainMenuLevel::~MainMenuLevel() 
{
}

void MainMenuLevel::Start()
{
	//메인 메뉴에서 사용될 리소스 가져옴
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("MainMenu");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//메인 메뉴 오브젝트 생성
	{
		std::shared_ptr<MenuBG> Background = CreateActor<MenuBG>();
		std::shared_ptr<MenuTitle> Title = CreateActor<MenuTitle>();
	}
}

void MainMenuLevel::Update(float _DeltaTime)
{

}