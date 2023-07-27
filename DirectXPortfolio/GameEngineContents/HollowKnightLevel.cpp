#include "PrecompileHeader.h"

#include "HollowKnightLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVideo.h>

#include "FadeEffect.h"
#include "Player.h"
#include "HollowKnightBossRoom.h"
#include "HollowKnightBoss.h"
#include "ContentsEnum.h"

HollowKnightLevel::HollowKnightLevel() 
{
}

HollowKnightLevel::~HollowKnightLevel() 
{
}

void HollowKnightLevel::Start()
{
	//메인 메뉴에서 사용될 리소스 가져옴
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("HollowKnight");
		NewDir.Move("BossRoom");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".bmp", ".jpg"});

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	FEffect = GetLastTarget()->CreateEffect<FadeEffect>();

	GetMainCamera()->GetCamTarget()->DepthSettingOff();
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->SetSortType(PlayRenderOrder::Background, SortType::ZSort);
	GetMainCamera()->SetSortType(PlayRenderOrder::UpperLayer, SortType::ZSort);
	GetMainCamera()->SetSortType(PlayRenderOrder::UpperEffect, SortType::ZSort);

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	GetMainCamera()->GetTransform()->SetLocalPosition({ (ScreenSize.x / 2),  -(ScreenSize.y / 2) - 420.0f, -1000.0f });

	//오브젝트 생성
	{
		HollowKnightLevelPlayer = CreateActor<Player>();
		HollowKnightLevelPlayer->InitPlayer("HollowKnightBossColmap.bmp", CameraClampType::HollowKnightBossRoom);

		HollowKnightLevelPlayer->GetTransform()->SetWorldPosition({ 694 , -1348, 0 });

		std::shared_ptr RoomActor = CreateActor<HollowKnightBossRoom>();
		RoomActor->GetTransform()->SetWorldPosition({ 2500, -750, 0 });

		HollowKnightLevelBoss = CreateActor<HollowKnightBoss>();
		HollowKnightLevelBoss->InitBoss(FEffect);
	}
}

void HollowKnightLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ChangeNextLevel"))
	{
		GameEngineCore::ChangeLevel("EndLevel");
	}
}

void HollowKnightLevel::LevelChangeStart()
{
	Player::SetCurrentLevelPlayer(HollowKnightLevelPlayer);

	FEffect->FadeOut();

	HollowKnightLevelPlayer->ResetPlayer();
	HollowKnightLevelBoss->ResetBoss();
}

void HollowKnightLevel::LevelChangeEnd()
{

}