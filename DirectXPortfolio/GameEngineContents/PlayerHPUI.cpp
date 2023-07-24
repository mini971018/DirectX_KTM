#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "PlayerHPUI.h"

PlayerHPUI::PlayerHPUI() 
{
}

PlayerHPUI::~PlayerHPUI() 
{
}

void PlayerHPUI::Start()
{
	{
		// UIHud
		HPUIRenderer = CreateComponent<GameEngineUIRenderer>();

		HPUIRenderer->CreateAnimation({ .AnimationName = "HealthAppear", .SpriteName = "04.HealthAppear", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		HPUIRenderer->CreateAnimation({ .AnimationName = "HealthBreak", .SpriteName = "05.HealthBreak", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		HPUIRenderer->CreateAnimation({ .AnimationName = "HealthIdle", .SpriteName = "06.HealthIdle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		HPUIRenderer->CreateAnimation({ .AnimationName = "HealthEmpty", .SpriteName = "07.HealthEmpty", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		HPUIRenderer->CreateAnimation({ .AnimationName = "HealthRefill", .SpriteName = "08.HealthRefill", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		
		HPUIRenderer->ChangeAnimation("HealthAppear");
	}
}

void PlayerHPUI::Update(float _Delta)
{
	if (CurrentType == HealthUIType::Idle && true == HPUIRenderer->IsAnimationEnd())
	{
		HPUIRenderer->ChangeAnimation("HealthIdle");
	}
	
	if (CurrentType == HealthUIType::Break && true == HPUIRenderer->IsAnimationEnd())
	{
		HPUIRenderer->ChangeAnimation("HealthEmpty");
	}
}

void PlayerHPUI::HealthBreak()
{
	HPUIRenderer->ChangeAnimation("HealthBreak");
	CurrentType = HealthUIType::Break;
}

void PlayerHPUI::HealthRefill()
{
	HPUIRenderer->ChangeAnimation("HealthRefill");
	CurrentType = HealthUIType::Idle;
}