#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <map>
#include <GameEngineBase/GameEngineRandom.h>

#include "Player.h"
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

	//To do : 이후 레벨 들어올 때 
	ResetBoss();
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("09.AnticDashAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("10.DashAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("11.EndDashAttack").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("12.AnticSlash1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("13.Slash1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("14.EndSlash1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("15.Slash2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("16.EndSlash2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("17.Slash3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("18.EndSlash3").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("19.AnticCounter").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("20.ReadyCounter").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("21.NoneBlockCounter").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("22.BlockCounter").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("23.FlashEffectCounter").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("24.AnticSmallShot").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("25.SmallShot").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("26.EndSmallShot").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("27.EffectSmallShot").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("28.AnticBlasts").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("29.SmashBlasts").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("30.LandBlasts").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("31.AnticEffectBlasts").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("32.EffectBlasts").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("33.AnticSelfStab").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("34.AnticLoopSelfStab").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("35.SelfStab").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("36.LoopSelfStab").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("37.ReAnticSelfStab").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("38.ReSelfStab").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("39.StunLand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("40.StunToIdle").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("41.AnticPuppet").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("42.UpPuppet").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("43.DownPuppet").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("44.SlamPuppet").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("45.EndPuppet").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("46.AnticChestShot").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("47.ShotChest").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("48.EffectChestShot").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("49.AnticDeath").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("50.LoopDeath").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("51.EndDeath").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("52.Evade").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("53.Antic").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("54.Recover").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("55.Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("56.Turn").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("99.ShieldBreakEffect").GetFullPath());

		//GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("").GetFullPath());

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
		BossRenderer->CreateAnimation({ .AnimationName = "Turn", .SpriteName = "56.Turn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "Recover", .SpriteName = "54.Recover", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });

		//DashAttack
		BossRenderer->CreateAnimation({ .AnimationName = "AnticDashAttack", .SpriteName = "09.AnticDashAttack", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "DashAttack", .SpriteName = "10.DashAttack", .FrameInter = 0.07f, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "EndDashAttack", .SpriteName = "11.EndDashAttack", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });

		//Slash1
		BossRenderer->CreateAnimation({ .AnimationName = "AnticSlash1", .SpriteName = "12.AnticSlash1", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "Slash1", .SpriteName = "13.Slash1", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "EndSlash1", .SpriteName = "14.EndSlash1", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "Slash2", .SpriteName = "15.Slash2", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "EndSlash2", .SpriteName = "16.EndSlash2", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "Slash3", .SpriteName = "17.Slash3", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "EndSlash3", .SpriteName = "18.EndSlash3", .FrameInter = 0.03f, .Loop = false, .ScaleToTexture = true });

		BossRenderer->ChangeAnimation("ChainIdle");

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
		ResetBoss();
	}

	if (GameEngineInput::IsUp("TestButton3"))
	{
		FSM.ChangeState("Idle");
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

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::Phase1), Phase1Patterns));
	}
	//Phase 2
	{
		std::vector<short> Phase2Patterns = std::vector<short>{0, 1, 2, 3, 4};

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::Phase2), Phase2Patterns));
	}
	//Phase 3
	{
		std::vector<short> Phase3Patterns = std::vector<short>{2, 3, 4, 5, 6, 7 };

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::Phase3), Phase3Patterns));
	}
	//Phase 4
	{
		std::vector<short> Phase4Patterns = std::vector<short>{8, 9, 10};

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::Phase3), Phase4Patterns));
	}
	//BeforeAttack
	{
		std::vector<short> BeforeAttackPatterns = std::vector<short>{ 0, 1, 2, 3, 4 };

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::BeforeAttack), BeforeAttackPatterns));
	}
	//Phase4BeforeAttack
	{
		std::vector<short> Phase4BeforeAttackPatterns = std::vector<short>{ 4 };

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::Phase4BeforeAttack), Phase4BeforeAttackPatterns));
	}
}

void HollowKnightBoss::ResetBoss()
{
	FSM.ChangeState("ChainIdle");

	PivotPos = { -20 , 230 };
	SetBossRendererPivot();
	GetTransform()->SetWorldPosition({ 3080, -950, 0 });
	Pivot->GetTransform()->SetLocalNegativeScaleX();
	
	BossRenderer->ChangeAnimation("ChainIdle");
	BossWeaponRenderer->On();

	CurrentPhase = HollowKnightPatternEnum::Phase1;
}

void HollowKnightBoss::SetRandomPattern()
{
	// 페이즈 4에서는 공격 전조 패턴 없이 즉시 공격 패턴 사용
	if (CurrentPhase == HollowKnightPatternEnum::Phase4)
	{
		SetRandomAttackPattern();
		return; 
	}

	int min = 0;
	int max = BossPatterns[static_cast<short>(HollowKnightPatternEnum::BeforeAttack)].size() - 1;

	HollowKnightNoneAttackState PatternNum = static_cast<HollowKnightNoneAttackState>(GameEngineRandom::MainRandom.RandomInt(min, max));

	switch (PatternNum)
	{
	case HollowKnightNoneAttackState::Teleport:
		//To do : 텔레포트 스테이트로 변경
		//break;
	case HollowKnightNoneAttackState::BackJump:
		//To do : 백점프 스테이트로 변경
		//break;
	case HollowKnightNoneAttackState::Jump:
		//To do : 점프 스테이트로 변경
		//break;
	case HollowKnightNoneAttackState::Evade:
		//To do : 회피 스테이트로 변경
		//break;
	case HollowKnightNoneAttackState::AttackReady:
		SetRandomAttackPattern();
		break;
	default:
		MsgAssert("존재할 수 없는 공허의 기사 전조 패턴입니다.");
		break;
	}

}

void HollowKnightBoss::SetRandomAttackPattern()
{
	int min = 0;
	int max = BossPatterns[static_cast<short>(CurrentPhase)].size() - 1;

	HollowKnightAttackState PatternNum = static_cast<HollowKnightAttackState>(GameEngineRandom::MainRandom.RandomInt(min, max));

	PatternNum = HollowKnightAttackState::Slash;

	switch (PatternNum)
	{
	case HollowKnightAttackState::DashAttack:
		FSM.ChangeState("AnticDashAttack");
		break;
	case HollowKnightAttackState::Slash:
		FSM.ChangeState("AnticSlash1");
		break;
	case HollowKnightAttackState::Counter:
		break;
	case HollowKnightAttackState::SmallShot:
		break;
	case HollowKnightAttackState::Blasts:
		break;
	case HollowKnightAttackState::Suicide:
		break;
	case HollowKnightAttackState::PuppetSlam:
		break;
	case HollowKnightAttackState::ChestShot:
		break;
	case HollowKnightAttackState::Phase4Slash:
		break;
	case HollowKnightAttackState::Phase4PuppetSlam:
		break;
	case HollowKnightAttackState::Phase4Suicide:
		break;
	default:
		MsgAssert("존재할 수 없는 공허의 기사 공격 패턴입니다.");
		break;
	}

	//FSM.ChangeState("Idle");
}

bool HollowKnightBoss::TurnCheck()
{
	float4 BossToPlayerDir = Player::CurrentLevelPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();
	float PivotScaleX = Pivot->GetTransform()->GetLocalScale().x;

	//보스와 플레이어의 위치와 현재 방향에 따라 회전할지 하지 않을지를 return 함
	if (BossToPlayerDir.x >= 0)
	{
		if (PivotScaleX >= 0) 
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (PivotScaleX >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

float4 HollowKnightBoss::ReturnPatternDir()
{
	if (Pivot->GetTransform()->GetLocalScale().x >= 0)
	{
		return float4::Right;
	}
	else
	{
		return float4::Left;
	}
}