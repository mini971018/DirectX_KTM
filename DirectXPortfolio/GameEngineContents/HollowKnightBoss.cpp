#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <map>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "RoarEffect.h"
#include "BindBreakEffect.h"
#include "HollowKnightBoss.h"
#include "HollowKnightBlasts.h"
#include "HollowKnightBullet.h"
#include "HollowKnightSmallShotEffect.h"
#include "ChestShotEffect.h"
#include "SlamEffect.h"
#include "SelfStabEffect.h"
#include "HitDustEffect.h"

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
	CollisionInit();
	StateInit();
	AttackStateInit();
	BossPatternInit();
	EffectInit();

	//To do : 이후 레벨 들어올 때 
	ResetBoss();
}

void HollowKnightBoss::SpriteInit()
{
	if (nullptr == GameEngineSprite::Find("00.HollowKnightChainIdle"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("57.DashEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("58.AnticTeleport").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("59.EndTeleport").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("95.SelfStabFlash").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("96.SlamEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("97.HollowKnightBulletSplash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("98.HollowKnightBullet").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("99.ShieldBreakEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("100.HitDust").GetFullPath());

		//GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("100.HitDust").GetFullPath());

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

		//Counter
		BossRenderer->CreateAnimation({ .AnimationName = "AnticCounter", .SpriteName = "19.AnticCounter", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "ReadyCounter", .SpriteName = "20.ReadyCounter", .FrameInter = 0.09f, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "NoneBlockCounter", .SpriteName = "21.NoneBlockCounter", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "BlockCounter", .SpriteName = "22.BlockCounter", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "CounterSlash2", .SpriteName = "22.BlockCounter", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });

		//SmallShot
		BossRenderer->CreateAnimation({ .AnimationName = "AnticSmallShot", .SpriteName = "24.AnticSmallShot", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "SmallShot", .SpriteName = "25.SmallShot", .FrameInter = 0.09f, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "EndSmallShot", .SpriteName = "26.EndSmallShot", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });

		//Blasts
		BossRenderer->CreateAnimation({ .AnimationName = "AnticBlasts", .SpriteName = "28.AnticBlasts", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "SmashBlasts", .SpriteName = "29.SmashBlasts", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "LandBlasts", .SpriteName = "30.LandBlasts", .FrameInter = 0.07f, .ScaleToTexture = true });

		//Teleport
		BossRenderer->CreateAnimation({ .AnimationName = "AnticTeleport", .SpriteName = "58.AnticTeleport", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "EndTeleport", .SpriteName = "59.EndTeleport", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });

		//SelfStab
		BossRenderer->CreateAnimation({ .AnimationName = "AnticSelfStab", .SpriteName = "33.AnticSelfStab", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "AnticLoopSelfStab", .SpriteName = "34.AnticLoopSelfStab", .FrameInter = 0.1f, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "SelfStab", .SpriteName = "35.SelfStab", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "LoopSelfStab", .SpriteName = "36.LoopSelfStab", .FrameInter = 0.07f, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "ReAnticSelfStab", .SpriteName = "37.ReAnticSelfStab", .FrameInter = 0.085f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "ReSelfStab", .SpriteName = "38.ReSelfStab", .FrameInter = 0.08f, .Loop = false, .ScaleToTexture = true });

		//StunLand
		BossRenderer->CreateAnimation({ .AnimationName = "StunLand", .SpriteName = "39.StunLand", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "StunToIdle", .SpriteName = "40.StunToIdle", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

		//PuppetSlam
		BossRenderer->CreateAnimation({ .AnimationName = "AnticPuppet", .SpriteName = "41.AnticPuppet", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "UpPuppet", .SpriteName = "42.UpPuppet", .FrameInter = 0.1f,  .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "DownPuppet", .SpriteName = "43.DownPuppet", .FrameInter = 0.07f, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "SlamPuppet", .SpriteName = "44.SlamPuppet", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "EndPuppet", .SpriteName = "45.EndPuppet", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });

		//ChestShot
		BossRenderer->CreateAnimation({ .AnimationName = "AnticChestShot", .SpriteName = "46.AnticChestShot", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		BossRenderer->CreateAnimation({ .AnimationName = "ShotChest", .SpriteName = "47.ShotChest", .FrameInter = 0.1f,  .ScaleToTexture = true });

		//Jump
		BossRenderer->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "55.Jump", .FrameInter = 0.07f, .ScaleToTexture = true });

		//Evade
		BossRenderer->CreateAnimation({ .AnimationName = "Evade", .SpriteName = "52.Evade", .FrameInter = 0.07f, .ScaleToTexture = true });

		//Antic
		BossRenderer->CreateAnimation({ .AnimationName = "Antic", .SpriteName = "53.Antic", .FrameInter = 0.07f, .ScaleToTexture = true });

		BossRenderer->ChangeAnimation("ChainIdle");

		if (nullptr == Pivot)
		{
			Pivot = CreateComponent<GameEngineComponent>();
			BossRenderer->GetTransform()->SetParent(Pivot->GetTransform());
		}

		std::shared_ptr<class GameEngineSpriteRenderer> BossPosRender = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Test);
		BossPosRender->GetTransform()->SetLocalScale({ 10, 10, 1 });
		BossPosRender->GetTransform()->SetLocalPosition({ 0, 0, -70 });
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

void HollowKnightBoss::CollisionInit()
{
	//보스 몸통
	HollowKnightCollision = CreateComponent<GameEngineCollision>();
	HollowKnightCollision->SetColType(ColType::AABBBOX2D);
	HollowKnightCollision->GetTransform()->SetParent(Pivot->GetTransform());

	SetIdleCollision();

	HollowKnightCollision->SetOrder(static_cast<int>(HollowKnightCollisionType::Boss));

	//공격 콜리전
	AttackCollision = CreateComponent<GameEngineCollision>();
	AttackCollision->SetColType(ColType::AABBBOX2D);
	AttackCollision->GetTransform()->SetParent(Pivot->GetTransform());
	AttackCollision->Off();
}
 
void HollowKnightBoss::SetDamagedColor()
{
	if (DamagedTime <= ConstDamagedTime)
	{
		BossRenderer->ColorOptionValue.PlusColor = DamagedColor;
		BossRenderer->ColorOptionValue.MulColor = DamagedColor;
		BossRenderer->ColorOptionValue.MulColor.a = 1.0f;
	}
	else
	{
		BossRenderer->ColorOptionValue.PlusColor = float4::Null;
		BossRenderer->ColorOptionValue.MulColor = float4::One;
	}
}

void HollowKnightBoss::EffectInit()
{
	SmallShotEffectActor = GetLevel()->CreateActor<HollowKnightSmallShotEffect>();

	SmallShotEffectActor->GetTransform()->SetParent(Pivot->GetTransform());
	SmallShotEffectActor->GetTransform()->SetLocalPosition({ 140, 0, 0 });

	ChestShotEffectActor = GetLevel()->CreateActor<ChestShotEffect>();

	ChestShotEffectActor->GetTransform()->SetParent(Pivot->GetTransform());
	ChestShotEffectActor->GetTransform()->SetLocalPosition({ 0, 0, 0 });
}

void HollowKnightBoss::Update(float _Delta)
{
	FSM.Update(_Delta);

	if (GameEngineInput::IsUp("TestButton1"))
	{
		//SetBullet();
	}

	if (GameEngineInput::IsUp("TestButton2"))
	{
		ResetBoss();
	}

	if (GameEngineInput::IsUp("TestButton3"))
	{
		FSM.ChangeState("Idle");
	}

	if (GameEngineInput::IsUp("TestButton4"))
	{
		CurrentHp -= 400.0f;
	}

	DamagedTime += _Delta;

	GetDamageCheck();
	SetDamagedColor();
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
		std::vector<short> Phase3Patterns = std::vector<short>{2, 3, 4, 5, 6};

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::Phase3), Phase3Patterns));
	}
	//Phase 4
	{
		std::vector<short> Phase4Patterns = std::vector<short>{1, 5};

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::Phase4), Phase4Patterns));
	}
	//BeforeAttack
	{
		std::vector<short> BeforeAttackPatterns = std::vector<short>{ 0, 1, 2, 3, 4 };

		BossPatterns.insert(std::pair(static_cast<short>(HollowKnightPatternEnum::BeforeAttack), BeforeAttackPatterns));
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
	CurrentHp = BossHP;
	HollowKnightCollision->Off();
	
}

void HollowKnightBoss::SetRandomPattern()
{
	// 페이즈 4에서는 공격 전조 패턴 없이 즉시 공격 패턴 사용
	if (CurrentPhase == HollowKnightPatternEnum::Phase4)
	{
		int min = 0;
		int max = 1;

		int PatternNum = GameEngineRandom::MainRandom.RandomInt(min, max);

		switch (PatternNum)
		{
		case 0:
			StateCalInt = 0;
			CurrentState = "ReAnticSelfStab";
			FSM.ChangeState(CurrentState);
			break;
			break;
		case 1:
			SetRandomAttackPattern();
			break;
		default:
			MsgAssert("존재할 수 없는 공허의 기사 Phase4 패턴입니다.");
			break;
		}

		return; 
	}

	int min = 0;
	int max = BossPatterns[static_cast<short>(HollowKnightPatternEnum::BeforeAttack)].size() - 1;

	HollowKnightNoneAttackState PatternNum = static_cast<HollowKnightNoneAttackState>(GameEngineRandom::MainRandom.RandomInt(min, max));
	PatternNum = HollowKnightNoneAttackState::SelfStab;

	switch (PatternNum)
	{
	case HollowKnightNoneAttackState::Teleport:
		CurrentState = "AnticTeleport";
		FSM.ChangeState(CurrentState);
		break;
	case HollowKnightNoneAttackState::Jump:
		//To do : 콜리전 추가 후 변경
		//FSM.ChangeState("Jump");
		//break;
	case HollowKnightNoneAttackState::Evade:
		CurrentState = "Evade";
		FSM.ChangeState("Antic");
		break;
	case HollowKnightNoneAttackState::AttackReady:
		SetRandomAttackPattern();
		break;
	case HollowKnightNoneAttackState::SelfStab:
		//3페이즈부터 SelfStab
		//if (static_cast<short>(CurrentPhase) <= 1)
		//{
		//	SetRandomPattern();
		//	break;
		//}
		StateCalInt = 0;
		CurrentState = "ReAnticSelfStab";
		FSM.ChangeState(CurrentState);
		break;
	default:
		MsgAssert("존재할 수 없는 공허의 기사 전조 패턴입니다.");
		break;
	}

}

void HollowKnightBoss::SetRandomAttackPattern()
{
	std::vector<short> CurrentPhaseVector = BossPatterns[static_cast<short>(CurrentPhase)];

	int Min = 0;
	int Max = BossPatterns[static_cast<short>(CurrentPhase)].size() - 1;
	short RandomValue = static_cast<short>(GameEngineRandom::MainRandom.RandomInt(Min, Max));

	HollowKnightAttackState PatternNum = static_cast<HollowKnightAttackState>(CurrentPhaseVector[RandomValue]);

	PatternNum = HollowKnightAttackState::PuppetSlam;

	switch (PatternNum)
	{
	case HollowKnightAttackState::DashAttack:
		CurrentState = "AnticDashAttack";
		FSM.ChangeState(CurrentState);
		break;
	case HollowKnightAttackState::Slash:
		CurrentState = "AnticSlash1";
		FSM.ChangeState(CurrentState); 
		break; 
	case HollowKnightAttackState::Counter:
		CurrentState = "AnticCounter";
		FSM.ChangeState(CurrentState);
		break;
	case HollowKnightAttackState::SmallShot:
		CurrentState = "AnticSmallShot";
		FSM.ChangeState(CurrentState);
		break;
	case HollowKnightAttackState::Blasts:
		CurrentState = "AnticBlasts";
		FSM.ChangeState("AnticTeleport");
		break;
	case HollowKnightAttackState::PuppetSlam:
		CurrentState = "AnticPuppet";
		FSM.ChangeState(CurrentState);
		break;
	case HollowKnightAttackState::ChestShot:
		CurrentState = "AnticChestShot";
		FSM.ChangeState(CurrentState);
		break;
	default:
		MsgAssert("존재할 수 없는 공허의 기사 공격 패턴입니다.");
		break;
	}

	//FSM.ChangeState("Idle");
}

void HollowKnightBoss::SetRandomTeleportPos()
{
	int Value = GameEngineRandom::MainRandom.RandomInt(0, 1);
	float RandomPositionValue = GameEngineRandom::MainRandom.RandomFloat(MinTeleportDistance, MaxTeleportDistance);

	if (0 == Value % 2)
	{
		RandomPositionValue *= -1.0f;
	}

	GetTransform()->AddWorldPosition({ RandomPositionValue, 0.0f });

	if (true == CheckRenderRotationValue())
	{
		RotationRenderPivotY();
	}
}

bool HollowKnightBoss::CheckRenderRotationValue()
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

void HollowKnightBoss::RotationRenderPivotY()
{
	if (Pivot->GetTransform()->GetLocalScale().x > 0.0f)
	{
		Pivot->GetTransform()->SetLocalNegativeScaleX();
	}
	else
	{
		Pivot->GetTransform()->SetLocalPositiveScaleX();
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

bool HollowKnightBoss::IsNextPhase()
{
	switch (CurrentPhase)
	{
	case HollowKnightPatternEnum::Phase1:
		if (CurrentHp <= 950)
		{
			CurrentPhase = HollowKnightPatternEnum::Phase2;
			FSM.ChangeState("AnticRoar");
			return true;
		}

		return false;

		break;
	case HollowKnightPatternEnum::Phase2:
		if (CurrentHp <= 650)
		{
			CurrentPhase = HollowKnightPatternEnum::Phase3;
			CurrentState = "AnticSelfStab";
			FSM.ChangeState("AnticRoar");
			return true;
		}
		
		return false;

		break;
	case HollowKnightPatternEnum::Phase3:
		if (CurrentHp <= 250)
		{
			CurrentPhase = HollowKnightPatternEnum::Phase4;
			CurrentState = "StunLand";
			FSM.ChangeState("AnticRoar");

			return true;
		}

		return false;

		break;
	default:

		return false;
		//MsgAssert("지정되지 않은 보스 페이즈 입니다.")
		break;
	}
}

bool HollowKnightBoss::CounterAvailability()
{
	//To do : Collision 추가 후 로직 구현 (플레이어가 콜리전과 맞닿아 있고, 방향이 서로 다름)
	return true;
}

bool HollowKnightBoss::BossStageStart()
{
	float4 BossToPlayerDir = Player::CurrentLevelPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

	float Value = fabs(BossToPlayerDir.x);

	if (Value <= StartDistanceX)
	{
		return true;
	}
	else
	{
		return false;
	}

	

}

void HollowKnightBoss::GetDamageCheck()
{
	if (DamagedTime < ConstDamagedTime)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> AttackCollision = HollowKnightCollision->Collision(HollowKnightCollisionType::PlayerAttack);
	std::shared_ptr<GameEngineCollision> SkillCollision = HollowKnightCollision->Collision(HollowKnightCollisionType::PlayerSkill);

	float AttackDamage = Player::CurrentLevelPlayer->GetPlayerDamage();
	float SkillDamage = Player::CurrentLevelPlayer->GetPlayerSkillDamage();

	if (AttackCollision != nullptr)
	{
		GetDamage(AttackDamage, PlayerAttackType::Slash, AttackCollision->GetTransform()->GetWorldPosition());
	}

	if (SkillCollision != nullptr)
	{
		GetDamage(SkillDamage, PlayerAttackType::Skill);
	}
}

void HollowKnightBoss::GetDamage(float _Damage, PlayerAttackType _Type, float4 _Pos)
{
	if (true == DamageReduceState)
	{
		_Damage = 1.0f;
	}

	CurrentHp -= _Damage;
	
	float4 EffectPos = float4::Null;

	switch (_Type)
	{
	case PlayerAttackType::Slash:
		//Hit Slash Effect 추가
		EffectPos = float4::Lerp(HollowKnightCollision->GetTransform()->GetWorldPosition(), _Pos, 0.5f);
		PlayerHitEffect();
		Player::CurrentLevelPlayer->SetEnemyHitEffect(EffectPos, float4{ 3 , 3 });
		Player::CurrentLevelPlayer->SetEnemyHitSlashEffect(EffectPos, float4{ 1 ,1 });
		break;
	case PlayerAttackType::Skill:
		PlayerHitEffect();
		EffectPos = HollowKnightCollision->GetTransform()->GetWorldPosition();
		//EffectPos = EffectPos - float4{ 0, 30.0f };
		Player::CurrentLevelPlayer->SetFireballHitEffect(EffectPos, float4{2 ,2});
		//Hit Skill Effect 추가
		break;
	case PlayerAttackType::SelfStab:

		break;
	default:
		MsgAssert("보스의 GetDamage 중 존재할 수 없는 데미지 타입 입니다.");
		break;
	}

	StateCalBool = true; //stunland 상태에서 데미지를 체크하기 위해
	DamagedTime = 0.0f;
}

void HollowKnightBoss::SetIdleCollision()
{
	SetCollisionValue(HollowKnightCollisionIdleScale, HollowKnightCollisionIdlePos);
}

void HollowKnightBoss::SetCollisionValue(float4 _Scale, float4 _Pos)
{
	HollowKnightCollision->GetTransform()->SetLocalScale(_Scale);
	HollowKnightCollision->GetTransform()->SetLocalPosition({_Pos.x, _Pos.y, 0.0f});
}

void HollowKnightBoss::SetSlashAttackCollision()
{
	AttackCollision->GetTransform()->SetLocalScale(SlashCollisionScale);
	AttackCollision->GetTransform()->SetLocalPosition(SlashCollisionPos);
	AttackCollision->On();
}

void HollowKnightBoss::SetSlamEffect()
{
	std::shared_ptr<class SlamEffect> SlamEffectActor = GetLevel()->CreateActor<SlamEffect>();
	SlamEffectActor->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	SlamEffectActor->GetTransform()->AddLocalPosition({ 0, 100, 0 });
	SlamEffectActor->GetTransform()->SetLocalScale({ 1.5f, 1.5f, 1.0f });
}

void HollowKnightBoss::SetStabEffect()
{
	std::shared_ptr<class SelfStabEffect> SelfStabEffectActor = GetLevel()->CreateActor<SelfStabEffect>();
	SelfStabEffectActor->GetTransform()->SetParent(Pivot->GetTransform());
	//SelfStabEffectActor->GetTransform()->SetWorldPosition(Pivot->GetTransform()->GetWorldPosition());
	SelfStabEffectActor->GetTransform()->SetLocalPosition({0, 0, 0});
	SelfStabEffectActor->GetTransform()->AddLocalPosition({-120, -50, 0});
	SelfStabEffectActor->GetTransform()->SetLocalScale({1.5f, 1.5f, 1.0f});
	SelfStabEffectActor->GetTransform()->SetLocalRotation({ 0, 0, -45.0f });
	//SelfStabEffectActor->GetTransform()->AddLocalPosition({ 0, 100, 0 });

	//if (float4::Left == ReturnPatternDir())
	//{
	//	SelfStabEffectActor->GetTransform()->SetLocalRotation({ 0, 0, -45.0f });
	//}
	//else
	//{
	//	SelfStabEffectActor->GetTransform()->SetLocalRotation({ 0, 0, 45.0f });
	//}

}

void HollowKnightBoss::SetBlasts()
{
	float4 Pos = GetTransform()->GetWorldPosition();
	float4 LeftPos = Pos;
	float4 RightPos = Pos;
	float Interval = 275.0f;

	while (LeftPos.x >= MinBlastsPosX)
	{
		LeftPos.x -= Interval;
		std::shared_ptr<class HollowKnightBlasts> LeftBlasts = GetLevel()->CreateActor<HollowKnightBlasts>();
		LeftBlasts->GetTransform()->SetWorldPosition({ LeftPos.x, LeftPos.y - 5.0f, -70.0f });
	}

	while (RightPos.x <= MaxBlastsPosX)
	{
		RightPos.x += Interval;
		std::shared_ptr<class HollowKnightBlasts> RightBlasts = GetLevel()->CreateActor<HollowKnightBlasts>();
		RightBlasts->GetTransform()->SetWorldPosition({ RightPos.x, RightPos.y - 5.0f, -70.0f });
	}

	std::shared_ptr<class HollowKnightBlasts> Blasts = GetLevel()->CreateActor<HollowKnightBlasts>();
	Blasts->GetTransform()->SetWorldPosition({ Pos.x, Pos.y - 5.0f, -70.0f });
}

void HollowKnightBoss::SetBullet(float4 _Dir, float4 _Pos, float _Force)
{
	std::shared_ptr<class HollowKnightBullet> BulletActor = GetLevel()->CreateActor<HollowKnightBullet>();
	BulletActor->GetTransform()->SetWorldPosition(_Pos);
	BulletActor->SetBullet(BossColmapTexture, _Dir, _Force);
}

void HollowKnightBoss::SetRandomBullet()
{
	float4 _Dir = { 1, 0, 0 };

	float Angle = 130.0f;
	float Force = 1000.0f;

	int RandomInt = GameEngineRandom::MainRandom.RandomInt(0, 1);
	float RandomFloat = GameEngineRandom::MainRandom.RandomFloat(-Angle / 2.0f, Angle / 2.0f);
	float RandomFloat2 = GameEngineRandom::MainRandom.RandomFloat(Force - 200.0f, Force + 200.0f);

	if (RandomInt == 0)
	{
		_Dir *= -1;
	}

	_Dir.RotaitonZDeg(RandomFloat);

	SetBullet(_Dir, Pivot->GetTransform()->GetWorldPosition(), RandomFloat2);
}

void HollowKnightBoss::PlayerHitEffect()
{
	float4 PlayerToBossDir = HollowKnightCollision->GetTransform()->GetWorldPosition() - Player::CurrentLevelPlayer->GetPlayerCollisionPos();
	float Value = HollowKnightCollision->GetTransform()->GetWorldScale().y / 2;

	if (PlayerToBossDir.y >= fabs(Value) || PlayerToBossDir.y <= -fabs(Value))
	{
		SetHitEffect(float4::Up);
		
		return;
	}
	
	if (PlayerToBossDir.x <= 0.0f)
	{
		SetHitEffect(float4::Left);
	}
	else
	{
		SetHitEffect(float4::Right);
	}

}

void HollowKnightBoss::SetHitEffect(float4 _Dir)
{
	//float4 PlayerToBossDir = HollowKnightCollision->GetTransform()->GetWorldPosition() - Player::CurrentLevelPlayer->GetTransform()->GetWorldPosition();
	float4 EffectDir = float4::Null;
	float Angle;

	if (float4::Up == _Dir)
	{
		EffectDir = float4::Up;
		Angle = 30.0f;
	}
	else if (float4::Left == _Dir)
	{
		EffectDir = float4::Left;
		Angle = 45.0f;
	}
	else if (float4::Right == _Dir)
	{
		EffectDir = float4::Right;
		Angle = 45.0f;
	}
	else
	{
		MsgAssert("HollowKnight SetHitEffect 중 존재할 수 없는 값 입니다");
	}

	for (int i = 0; i < 9; ++i)
	{
		float4 AngleDir = EffectDir;
		float RandomAngle = 0.0f;

		if (_Dir == float4::Up)
		{
			RandomAngle = GameEngineRandom::MainRandom.RandomFloat(-Angle, Angle);
		}
		else if (_Dir == float4::Left)
		{
			RandomAngle = GameEngineRandom::MainRandom.RandomFloat(-Angle, 0);
		}
		else
		{
			RandomAngle = GameEngineRandom::MainRandom.RandomFloat(0, Angle);
		}

		AngleDir.RotaitonZDeg(RandomAngle);

		std::shared_ptr<class HitDustEffect> HitDustEffectActor = GetLevel()->CreateActor<HitDustEffect>();
		HitDustEffectActor->GetTransform()->SetWorldPosition(HollowKnightCollision->GetTransform()->GetWorldPosition());
		HitDustEffectActor->SetHitDust(AngleDir);
	}
}