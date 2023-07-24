#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "PlayerHPUI.h"
#include "Player.h"
#include "PlayerUIManager.h"

PlayerUIManager::PlayerUIManager() 
{
}

PlayerUIManager::~PlayerUIManager() 
{
}

void PlayerUIManager::Start()
{
	if (nullptr == GameEngineSprite::Find("00.UIHudOn"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("HollowKnight");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("00.UIHudOn").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("02.SoulOrb").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("03.SoulOrbBurstEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("04.HealthAppear").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("05.HealthBreak").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("06.HealthIdle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("07.HealthEmpty").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("08.HealthRefill").GetFullPath());

		//GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("").GetFullPath());
	}


	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	GetTransform()->SetLocalPosition({ -700.0f, 400.0f });

	{
		// UIHud
		UIHud = CreateComponent<GameEngineUIRenderer>();

		UIHud->CreateAnimation({ .AnimationName = "UIHudOn", .SpriteName = "00.UIHudOn", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		UIHud->ChangeAnimation("UIHudOn");	
	}
}

void PlayerUIManager::SetHPUIManager(int _PlayerHP)
{
	PlayerMaxHP = _PlayerHP;
	CurrentPlayerHP = _PlayerHP;

	HPUIVector.reserve(PlayerMaxHP);
	for (int i = 0; i < PlayerMaxHP; ++i)
	{
		std::shared_ptr<class PlayerHPUI> PlayerHPUIActor = GetLevel()->CreateActor<PlayerHPUI>();

		float4 HPUIPosition = HPUIStartPos;
		HPUIPosition.x += HPUIInterval * i;

		PlayerHPUIActor->GetTransform()->SetParent(GetTransform());
		PlayerHPUIActor->GetTransform()->SetLocalScale({0.7f, 0.7f, 1.0f});
		PlayerHPUIActor->GetTransform()->SetLocalPosition(HPUIPosition);

		HPUIVector.push_back(PlayerHPUIActor);
	}
}

void PlayerUIManager::Update(float _Delta)
{
	int a = CurrentPlayerHP;
	int b = Player::CurrentLevelPlayer->GetCurrentPlayerHP();

	if (CurrentPlayerHP != Player::CurrentLevelPlayer->GetCurrentPlayerHP())
	{
		if (CurrentPlayerHP > Player::CurrentLevelPlayer->GetCurrentPlayerHP())
		{
			for (int i = Player::CurrentLevelPlayer->GetCurrentPlayerHP(); i < CurrentPlayerHP ; ++i)
			{
				HPUIVector[i]->HealthBreak();
			}
		}
		else
		{
			for (int i = Player::CurrentLevelPlayer->GetCurrentPlayerHP() - 1; i > CurrentPlayerHP - 1; --i)
			{
				HPUIVector[i]->HealthRefill();
			}
		}

		CurrentPlayerHP = Player::CurrentLevelPlayer->GetCurrentPlayerHP();
	}
}