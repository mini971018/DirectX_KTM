#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <map>

#include "RoarEffect.h"
#include "BindBreakEffect.h"
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
	BossPatternInit();
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
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("99.ShieldBreakEffect").GetFullPath());
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
		BossRenderer->SetAnimationStartEvent("BreakChain", 4, [this]
			{
				std::shared_ptr BreakShieldEffect = GetLevel()->CreateActor<BindBreakEffect>();
				BreakShieldEffect->SetBindBreakRenderer(GetTransform()->GetWorldPosition() + PivotPos);
			});
		BossRenderer->CreateAnimation({ .AnimationName = "BreakChainFall", .SpriteName = "03.HollowKnightBreakChainFall",.Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "BreakChainLand", .SpriteName = "04.HollowKnightBreakChainLand", .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "RoarAntic", .SpriteName = "05.HollowKnightRoarAntic", .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "Roar", .SpriteName = "06.HollowKnightRoar", .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "RoarToIdle", .SpriteName = "07.HollowKnightRoarToIdle", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "08.HollowKnightIdle", .ScaleToTexture = true });

		BossRenderer->ChangeAnimation("ChainIdle");
		GetTransform()->SetLocalNegativeScaleX();

		if (nullptr == Pivot)
		{
			Pivot = CreateComponent<GameEngineComponent>();
			BossRenderer->GetTransform()->SetParent(Pivot->GetTransform());
		}

	}


	if (nullptr == BossWeaponRenderer)
	{
		BossWeaponRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BossWeaponRenderer->GetTransform()->SetParent(GetLevel()->GetTransform());
		BossWeaponRenderer->SetScaleToTexture("HollowKnightNail.png");
		BossWeaponRenderer->GetTransform()->SetWorldPosition({ 3190, -1200, -70 });
		BossWeaponRenderer->GetTransform()->SetWorldRotation({ 0, 0, -10 });

	}

	std::shared_ptr<GameEngineTexture> ColmapTexture = GameEngineTexture::Find("HollowKnightBossColmap.bmp");

	if (nullptr != ColmapTexture)
	{
		BossColmapTexture = ColmapTexture;
	}
}

void HollowKnightBoss::Update(float _Delta)
{
	FSM.Update(_Delta);

	if (GameEngineInput::IsUp("TestButton2"))
	{
		FSM.ChangeState("ChainIdle");
	}
}

void HollowKnightBoss::LevelChangeStart()
{

}

void HollowKnightBoss::Render(float _Delta)
{
	//HDC DoubleDC = GameEngineWindow::GetWindowBackBufferHdc();
	//float4 PivotRenderPos = GetTransform()->GetWorldPosition();
	//
	//Rectangle(DoubleDC,
	//	PivotRenderPos.ix() - 1000,
	//	PivotRenderPos.iy() - 1000,
	//	PivotRenderPos.ix() + 1000,
	//	PivotRenderPos.iy() + 1000
	//);
}

void HollowKnightBoss::SetBossRendererPivot()
{
	Pivot->GetTransform()->SetLocalPosition({ PivotPos.x, PivotPos.y, -70.0f });
}

void HollowKnightBoss::CreateRoarEffect(RoarType _Type, float4 _Pos)
{
	std::shared_ptr BossRoarEffect = GetLevel()->CreateActor<RoarEffect>();
	BossRoarEffect->SetRoarEffect(_Type, _Pos);
}

bool HollowKnightBoss::IsGround(float4 _Pos)
{
	if (nullptr != BossColmapTexture)
	{
		float4 CheckPos = GetTransform()->GetWorldPosition();

		if (GameEnginePixelColor::Black == BossColmapTexture->GetPixel(_Pos.x,  -_Pos.y ))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	MsgAssert("보스의 콜리전 맵이 없습니다.");
	return false;

}

void HollowKnightBoss::SetGravity(float _Delta)
{
	float4 NextPos = GetTransform()->GetWorldPosition() + float4{ 0, -Gravity * _Delta ,0 };

	GetTransform()->SetWorldPosition(NextPos);
}

void HollowKnightBoss::BossPatternInit()
{
	//Phase 1
	{
		std::vector<short> Phase1Patterns = std::vector<short>{0, 1, 2};

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightStateMachineEnum::Phase1), Phase1Patterns));
	}
	//Phase 2
	{
		std::vector<short> Phase2Patterns = std::vector<short>{0, 1, 2, 3, 4};

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightStateMachineEnum::Phase2), Phase2Patterns));
	}
	//Phase 3
	{
		std::vector<short> Phase3Patterns = std::vector<short>{2, 3, 4, 5, 6, 7 };

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightStateMachineEnum::Phase3), Phase3Patterns));
	}
	//Phase 4
	{
		std::vector<short> Phase4Patterns = std::vector<short>{8, 9, 10};

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightStateMachineEnum::Phase3), Phase4Patterns));
	}
	//BeforeAttack
	{
		std::vector<short> BeforeAttackPatterns = std::vector<short>{ 0, 1, 2, 3, 4 };

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightStateMachineEnum::BeforeAttack), BeforeAttackPatterns));
	}
}