#include "PrecompileHeader.h"

#include "MainMenuLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FadeEffect.h"
#include "TestObject1.h"
#include "MenuBG.h"
#include "MenuTitle.h"
#include "ContentsEnum.h"
#include "MainMenuUIManager.h"

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

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("MainMenuUI");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UISelect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UIUnSelect").GetFullPath());
	}

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Sound");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".mp3", ".wav"});

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineSound::Load(File[i].GetFullPath());
		}
	}

	FEffect = GetLastTarget()->CreateEffect<FadeEffect>();

	//GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });	
	GetMainCamera()->GetCamTarget()->DepthSettingOff();

	//메인 메뉴 오브젝트 생성
	{
		std::shared_ptr<MenuBG> Background = CreateActor<MenuBG>(UIRenderOrder::Background);
		std::shared_ptr<MenuTitle> Title = CreateActor<MenuTitle>(UIRenderOrder::Title);
		MainMenuUIManagerActor = CreateActor<MainMenuUIManager>();

		//UIManager->GetTransform()->SetWorldPosition({0, 0, -71.0f});
	}
}

void MainMenuLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ChangeNextLevel"))
	{
		GameEngineCore::ChangeLevel("HollowKnightLevel");
	}
}

void MainMenuLevel::LevelChangeStart()
{
	BgmPlayer = GameEngineSound::Play("Title.wav");
	BgmPlayer.SetLoop();
	BgmPlayer.SoundFadeIn(2.0);

	FEffect->FadeOut();

	MainMenuUIManagerActor->ResetUIManager(FEffect, BgmPlayer);
}

void MainMenuLevel::LevelChangeEnd()
{
	BgmPlayer.Stop();
}
