#include "PrecompileHeader.h"

#include "HollowKnightLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "Player.h"
#include "HollowKnightBossRoom.h"
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

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->SetSortType(PlayRenderOrder::Background, SortType::ZSort);
	GetMainCamera()->GetTransform()->SetLocalPosition({ -1540, -210, -1000.0f });

	//오브젝트 생성
	{
		std::shared_ptr PlayerActor = CreateActor<Player>(PlayRenderOrder::Player);
		std::shared_ptr RoomActor = CreateActor<HollowKnightBossRoom>();
	}
}

void HollowKnightLevel::Update(float _DeltaTime)
{

}