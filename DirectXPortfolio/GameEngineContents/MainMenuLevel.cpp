#include "PrecompileHeader.h"

#include "MainMenuLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore\GameEngineCore.h>

#include "TestObject1.h"
#include "MenuBG.h"
#include "MenuTitle.h"
#include "ContentsEnum.h"

MainMenuLevel::MainMenuLevel() 
{
}

MainMenuLevel::~MainMenuLevel() 
{
}

void MainMenuLevel::Start()
{
	//���� �޴����� ���� ���ҽ� ������
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

	//GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//���� �޴� ������Ʈ ����
	{
		std::shared_ptr<MenuBG> Background = CreateActor<MenuBG>(UIRenderOrder::Background);
		std::shared_ptr<MenuTitle> Title = CreateActor<MenuTitle>(UIRenderOrder::Title);
	}
}

void MainMenuLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ChangeNextLevel"))
	{
		GameEngineCore::ChangeLevel("HollowKnightLevel");
	}
}
