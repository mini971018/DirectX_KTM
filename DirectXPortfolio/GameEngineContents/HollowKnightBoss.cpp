#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "HollowKnightBoss.h"


HollowKnightBoss::HollowKnightBoss() 
{
}

HollowKnightBoss::~HollowKnightBoss() 
{
}

void HollowKnightBoss::Start()
{
	SpriteInit();
	AnimationInit();
	StateInit();
}

void HollowKnightBoss::SpriteInit()
{
	if (nullptr == GameEngineSprite::Find("HollowKnightShakeChain"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("HollowKnight");
		NewDir.Move("BossSprites");
		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("00.HollowKnightChainIdle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("01.HollowKnightShakeChain").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("02.HollowKnightBreakChain").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("03.HollowKnightBreakChainFall").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("04.HollowKnightBreakChainLand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("05.HollowKnightRoarAntic").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("06.HollowKnightRoar").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("07.HollowKnightRoarToIdle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("08.HollowKnightIdle").GetFullPath());
	}
}

void HollowKnightBoss::AnimationInit()
{
	if (nullptr == BossRenderer)
	{
		BossRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Boss);

		BossRenderer->CreateAnimation({ .AnimationName = "ChainIdle", .SpriteName = "00.HollowKnightChainIdle", .Loop = false, .ScaleToTexture = true, });
		BossRenderer->CreateAnimation({ .AnimationName = "ShakeChain", .SpriteName = "01.HollowKnightShakeChain", .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "BreakChain", .SpriteName = "02.HollowKnightBreakChain",  .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "BreakChainFall", .SpriteName = "03.HollowKnightBreakChainFall", .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "BreakChainLand", .SpriteName = "04.HollowKnightBreakChainLand", .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "RoarAntic", .SpriteName = "05.HollowKnightRoarAntic",  .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "Roar", .SpriteName = "06.HollowKnightRoar", .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "RoarToIdle", .SpriteName = "07.HollowKnightRoarToIdle", .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "08.HollowKnightIdle", .ScaleToTexture = true });

		BossRenderer->ChangeAnimation("ChainIdle");
		GetTransform()->SetLocalNegativeScaleX();
	}


	if (nullptr == BossWeaponRenderer)
	{
		BossWeaponRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BossWeaponRenderer->SetScaleToTexture("HollowKnightNail.png");
		BossWeaponRenderer->GetTransform()->SetWorldPosition({ -3190, -1200, -70 });
		BossWeaponRenderer->GetTransform()->SetWorldRotation({ 0, 0, 10 });

	}

	std::shared_ptr<GameEngineTexture> ColmapTexture = GameEngineTexture::Find("HollowKnightBossColmap.png");

	if (nullptr != ColmapTexture)
	{
		BossColmapTexture = ColmapTexture;
	}
}

void HollowKnightBoss::Update(float _Delta)
{
	FSM.Update(_Delta);

	if (nullptr != BossColmapTexture)
	{
		//float4 CheckPos = GetTransform()->GetWorldPosition();
		float4 CheckPos = float4{ 2800, 1000 };

		if (GameEnginePixelColor::Black == BossColmapTexture->GetPixel(CheckPos.x, CheckPos.y))
		{
			int a = 0;
		}
	}

}

void HollowKnightBoss::LevelChangeStart()
{

}

void HollowKnightBoss::Render(float _Delta)
{

}

void HollowKnightBoss::SetBossRendererPivot()
{
	BossRenderer->GetTransform()->SetLocalPosition({ PivotPos.x, PivotPos.y, -70.0f });
}