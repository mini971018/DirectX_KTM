#include "PrecompileHeader.h"

#include "HollowKnightLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "Player.h"
#include "HollowKnightBossRoom.h"

HollowKnightLevel::HollowKnightLevel() 
{
}

HollowKnightLevel::~HollowKnightLevel() 
{
}

void HollowKnightLevel::Start()
{
	//���� �޴����� ���� ���ҽ� ������
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
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//������Ʈ ����
	{
		std::shared_ptr PlayerActor = CreateActor<Player>(1);
		std::shared_ptr RoomActor = CreateActor<HollowKnightBossRoom>();
	}
}

void HollowKnightLevel::Update(float _DeltaTime)
{

}