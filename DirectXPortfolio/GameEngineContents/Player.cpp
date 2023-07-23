#include "PrecompileHeader.h"

#include "Player.h"
#include "ShadowDashRechargedEffect.h"
#include "FocusEffect.h"
#include "ScreamEffect.h"
#include "PlayerFireBall.h"
#include "FireballCastEffect.h"
#include "HealingEffect.h"
#include "DoubleJumpEffect.h"
#include "SlashEffect.h"
#include "DashEffect.h"
#include "ShadowDashEffect.h"
#include "FireballHitEnemyEffect.h"
#include "PlayerHitEffect.h"
#include "PlayerHitSlashEffect.h"
#include "GetDamageEffect.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>

std::shared_ptr<Player> Player::CurrentLevelPlayer = nullptr;
// 레벨 변경 시, 레벨의 메인 플레이어를 넣어 줌.
void Player::SetCurrentLevelPlayer(std::shared_ptr<Player> _Player)
{
	CurrentLevelPlayer = _Player;
}

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	CreateKey();
	SpriteInit();
	AttackStateInit();
	AnimationInit();
	StateInit();
	EffectInit();
	CollisionInit();
}

void Player::Update(float _Delta)
{
	FSM.Update(_Delta);

	//카메라 관련
	CameraMoveLerp(_Delta);

	SlashCalTime += _Delta; // 일반공격 애니메이션을 확인하기 위한 변수
	ShadowDashCalTime += _Delta; // ShadowDash 쿨타임 계산을 위한 변수

	if (ShadowDashCalTime >= (ShadowDashCooltime - 0.68) && ShadowDashEffectIsOn == false)
	{
		ShadowDashRechargedEffectActor->OnRechargedEffect();
		ShadowDashEffectIsOn = true;
	}

	SetStateAbleValue();

	if (GameEngineInput::IsDown("SwitchCollisionDebug"))
	{
		GameEngineLevel::IsDebugSwitch();
	}

	CameraShakeTime -= _Delta;
	SetIsCameraShake();

	PlayerDamagedTime -= _Delta;
	PlayerGetDamagedCheck();
	SetPlayerColor(_Delta);

	Test();
}

void Player::Render(float _Delta)
{

}

void Player::CreateKey()
{
	if (false == GameEngineInput::IsKey("ChangeNextLevel"))
	{
		GameEngineInput::CreateKey("TestButton1", '1');
		GameEngineInput::CreateKey("TestButton2", '2');
		GameEngineInput::CreateKey("TestButton3", '3');
		GameEngineInput::CreateKey("TestButton4", '4');
		
		GameEngineInput::CreateKey("TestButton8", '8');

		GameEngineInput::CreateKey("ChangeNextLevel", '0');

		GameEngineInput::CreateKey("MoveUp", VK_UP);
		GameEngineInput::CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("MoveLeft", VK_LEFT);

		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'Z');
		GameEngineInput::CreateKey("Dash", 'C');
		GameEngineInput::CreateKey("Skill", 'A');

		GameEngineInput::CreateKey("SwitchCollisionDebug", '9');
	}
}

void Player::Test()
{

}

bool Player::IsGround(float4 _Pos)
{
	if (nullptr != PlayerColmapTexture)
	{
		if (GameEnginePixelColor::Black == PlayerColmapTexture->GetPixel(static_cast<int>(_Pos.x), static_cast<int>(-_Pos.y)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	MsgAssert("플레이어의 콜리전 맵이 없습니다.");
	return false;

}

void Player::SetGravity(float _Delta)
{
	float4 NextPos = GetTransform()->GetWorldPosition() + float4{ 0, -Gravity * _Delta ,0 };

	GetTransform()->SetWorldPosition(NextPos);
}


void Player::SetStateAbleValue()
{
	if (true == IsGround(GetTransform()->GetWorldPosition()))
	{
		Dashable = true;
		DoubleJumpable = true;
	}
}

void Player::SetDashState()
{
	if (ShadowDashCalTime >= ShadowDashCooltime)
	{
		FSM.ChangeState("ShadowDash");
	}
	else
	{
		FSM.ChangeState("Dash");
	}
}

void Player::ResetShadowDashValue()
{
	ShadowDashCalTime = 0.0f;
	ShadowDashEffectIsOn = false;
}


void Player::ResetFallValue()
{
	StateCalTime = 0.0f;
	Gravity = 100.0f;
	StateCalFloat = JumpForce; //점프 내에서 최대 점프 거리까지 가면 올라가는 속도를 줄여주기 위한 변수
}

void Player::SetPlayerRendererPivot()
{
	Pivot->GetTransform()->SetLocalPosition({ PivotPos.x, PivotPos.y, -70.0f });
}

void Player::InitPlayer(std::string_view ColMap, CameraClampType _ClampType)
{
	std::shared_ptr<GameEngineTexture> ColmapTexture = GameEngineTexture::Find(ColMap);

	if (nullptr != ColmapTexture)
	{
		PlayerColmapTexture = ColmapTexture;
	}

	ClampType = _ClampType;
	CurrentPlayerHP = PlayerMaxHP;

}

void Player::SpriteInit()
{
	if (nullptr == GameEngineSprite::Find("00.HollowKnightChainIdle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("HollowKnight");
		NewDir.Move("Player");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("00.Idle").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("01.Turn").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("02.Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("03.Fall").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("04.FallLoop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("05.Land").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("06.AnticSprint").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("07.Sprint").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("24.SprintToIdle").GetFullPath());
		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("08.Stun").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("09.Slash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("10.Slash2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("11.UpSlash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("12.DownSlash").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("13.DoubleJump").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("14.Dash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("15.DashToIdle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("16.DashDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("17.DashDownLand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("18.ShadowDash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("19.DownShadowDash").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("20.RoarLock").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("21.RoarLockLoop").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("22.Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("23.DeathLoop").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("25.AnticFocus").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("26.LoopFocus").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("27.EndFocus").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("28.GetOnFocus").GetFullPath());
		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("29.AnticScream").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("30.LoopScream").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("31.EndScream").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("32.FireballCast").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("33.GetDamaged").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("81.GetDamagedEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("82.HitEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("83.HitSlashEffect1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("84.HitSlashEffect2").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("85.HitSkillEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("86.FireballCastEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("87.AnticFireBallEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("88.LoopFireBallEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("89.EndFireBallEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("90.FireballHitEnemyEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("91.FireballHitWallEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("92.ScreamEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("94.FocusEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("95.LoopFocusEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("96.EndFocusEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("97.HealingEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("98.SlashEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("99.Slash2Effect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("100.UpSlashEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("101.DownSlashEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("102.DoubleJumpEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("103.DashEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("104.ShadowDashEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("105.ShadowDashRechargedEffect").GetFullPath());

		//GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("").GetFullPath());
	}
}

void Player::AnimationInit()
{
	if (nullptr == PlayerRenderer)
	{
		PlayerRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Player);
	}

	//플레이어 애니메이션 추가

	//Idle
	PlayerRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "00.Idle", .ScaleToTexture = true, });

	//Sprint
	PlayerRenderer->CreateAnimation({ .AnimationName = "AnticSprint", .SpriteName = "06.AnticSprint", .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "Sprint", .SpriteName = "07.Sprint", .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "SprintToIdle", .SpriteName = "24.SprintToIdle",  .FrameInter = 0.03f, .Loop = false, .ScaleToTexture = true, });

	//Turn
	PlayerRenderer->CreateAnimation({ .AnimationName = "Turn", .SpriteName = "01.Turn",  .FrameInter = 0.03f, .Loop = false, .ScaleToTexture = true, });

	//Jump
	PlayerRenderer->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "02.Jump",  .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "03.Fall",  .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "FallLoop", .SpriteName = "04.FallLoop",  .FrameInter = 0.07f, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "Land", .SpriteName = "05.Land",  .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true, });

	//DoubleJump
	PlayerRenderer->CreateAnimation({ .AnimationName = "DoubleJump", .SpriteName = "13.DoubleJump",  .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true, });
	
	//Slash
	PlayerRenderer->CreateAnimation({ .AnimationName = "Slash1", .SpriteName = "09.Slash",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "Slash2", .SpriteName = "10.Slash2",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "UpSlash", .SpriteName = "11.UpSlash",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "DownSlash", .SpriteName = "12.DownSlash",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });

	//Dash
	PlayerRenderer->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "14.Dash",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "DashToIdle", .SpriteName = "15.DashToIdle",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "DashDown", .SpriteName = "16.DashDown",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "DashDownLand", .SpriteName = "17.DashDownLand",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "ShadowDash", .SpriteName = "18.ShadowDash",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "DownShadowDash", .SpriteName = "19.DownShadowDash",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "DashEffect", .SpriteName = "103.DashEffect",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "ShadowDashEffect", .SpriteName = "104.ShadowDashEffect",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	//PlayerRenderer->CreateAnimation({ .AnimationName = "ShadowDashRechargedEffect", .SpriteName = "105.ShadowDashRechargedEffect",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });

	//Healing
	PlayerRenderer->CreateAnimation({ .AnimationName = "AnticFocus", .SpriteName = "25.AnticFocus",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "LoopFocus", .SpriteName = "26.LoopFocus",  .FrameInter = 0.055f, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "EndFocus", .SpriteName = "27.EndFocus",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "GetOnFocus", .SpriteName = "28.GetOnFocus",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });

	//Scream
	PlayerRenderer->CreateAnimation({ .AnimationName = "AnticScream", .SpriteName = "29.AnticScream",  .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "LoopScream", .SpriteName = "30.LoopScream",  .FrameInter = 0.07f, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "EndScream", .SpriteName = "31.EndScream",  .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true, });

	//Fireball
	PlayerRenderer->CreateAnimation({ .AnimationName = "FireballCast", .SpriteName = "32.FireballCast",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });

	//Roarlock
	PlayerRenderer->CreateAnimation({ .AnimationName = "RoarLock", .SpriteName = "20.RoarLock",  .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "RoarLockLoop", .SpriteName = "21.RoarLockLoop",  .FrameInter = 0.065f, .Loop = false, .ScaleToTexture = true, });

	//GetDamged
	PlayerRenderer->CreateAnimation({ .AnimationName = "GetDamaged", .SpriteName = "33.GetDamaged",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true, });
	PlayerRenderer->SetAnimationStartEvent("GetDamaged", 1, [this]
		{
			GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(1.0f);
		});

	if (nullptr == Pivot)
	{
		Pivot = CreateComponent<GameEngineComponent>();
	}
	PlayerRenderer->GetTransform()->SetParent(Pivot->GetTransform());
	Pivot->GetTransform()->SetLocalNegativeScaleX();

	std::shared_ptr<class GameEngineSpriteRenderer> PlayerPosRender = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Test);
	PlayerPosRender->GetTransform()->SetLocalScale({ 10, 10, 1 });
	PlayerPosRender->GetTransform()->SetLocalPosition({ 0, 0, -70 });
}

void Player::EffectInit()
{
	if (nullptr == Pivot)
	{
		Pivot = CreateComponent<GameEngineComponent>();
	}

	//ShadowDashRecharged
	ShadowDashRechargedEffectActor = GetLevel()->CreateActor<ShadowDashRechargedEffect>();
	ShadowDashRechargedEffectActor->GetTransform()->SetParent(Pivot->GetTransform());

	FocusEffectActor = GetLevel()->CreateActor<FocusEffect>();
	FocusEffectActor->GetTransform()->SetParent(Pivot->GetTransform());

	JumpEffectActor = GetLevel()->CreateActor<DoubleJumpEffect>();
	JumpEffectActor->GetTransform()->SetLocalNegativeScaleX();
	JumpEffectActor->GetTransform()->SetParent(Pivot->GetTransform());

	SlashEffectActor = GetLevel()->CreateActor<SlashEffect>();
	//SlashEffectActor->GetTransform()->SetLocalNegativeScaleX();
	SlashEffectActor->GetTransform()->SetParent(GetTransform());

	DashEffectActor = GetLevel()->CreateActor<DashEffect>();
	DashEffectActor->GetTransform()->SetLocalScale({ 1.5f, 1.5f, 1.0f });
	DashEffectActor->GetTransform()->SetParent(Pivot->GetTransform());
}

void Player::CollisionInit()
{
	PlayerCollision = CreateComponent<GameEngineCollision>();
	PlayerCollision->SetColType(ColType::AABBBOX2D);
	PlayerCollision->GetTransform()->SetLocalScale({ 52.0f, 114.0f, 1.0f});
	PlayerCollision->GetTransform()->SetLocalPosition({ 0.0f, 65.0f , -70.0f});
	PlayerCollision->SetOrder(static_cast<int>(HollowKnightCollisionType::Player));
}

void Player::SetCameraShakeOff()
{
	CameraShakeTime = 0.0f;
}

void Player::SetCameraShakeLoop(float _Force)
{
	SetCameraShakeValue(100000.0f, _Force);
}

void Player::SetCameraShakeOnce(float _Force)
{
	SetCameraShakeValue(0.15f, _Force);
}

void Player::SetIsCameraShake()
{
	if (CameraShakeTime >= 0.0f)
	{
		IsCameraShake = true;
	}
	else
	{
		IsCameraShake = false;
	}
}

void Player::CameraMoveLerp(float _Delta)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	CamTarget = GetTransform()->GetWorldPosition();

	CamTarget = SetCameraTarget(CamTarget);
	CamTarget = SetCameraClamp(CamTarget);

	float4 CamTargetPosValue = CamTarget;

	if (true == IsCameraShake)
	{
		CamDeltaTime += _Delta * 20.0f;
		if (CamDeltaTime >= 1.0f)
		{
			CamDeltaTime = 1.0f;
		}

		CamTargetPosValue = SetCameraShake(CamTargetPosValue);
	}
	else
	{
		CamDeltaTime += _Delta * 10.0f;
		if (CamDeltaTime >= 1.0f)
		{
			CamDeltaTime = 1.0f;
		}
	}

	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(float4::Lerp(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition(), CamTargetPosValue, CamDeltaTime));

	float value = CameraPos.XYDistance(CamTargetPosValue);

	if (value >= 0.5f)
	{
		CamDeltaTime = 0.0f;
	}
}

// 포지션을 카메라 값에 맞는 값으로 리턴
float4 Player::SetCameraTarget(float4 _Pos)
{
	//_Pos.y += 393.0f;
	_Pos.z = -1000.0f;

	return _Pos;
}

float4 Player::SetCameraClamp(float4 _Pos)
{
	switch (ClampType)
	{
	case CameraClampType::HollowKnightBossRoom:
		if (_Pos.x < 834.0f)
		{
			_Pos.x = 834.0f;
		}

		if (_Pos.x > 3850.0f)
		{
			_Pos.x = 3850.0f;
		}

		_Pos.y = -960.0f;

		break;
	case CameraClampType::HollowKnightInBoss:
		break;
	default:
		break;
	}

	return _Pos;
}

float4 Player::SetCameraShake(float4 _Pos)
{
	float4 RandomPosDir = float4{ CameraShakeForce, 0.0f, 0.0f };
	float RandomAngle = GameEngineRandom::MainRandom.RandomFloat(0, 359);

	RandomPosDir.RotaitonZDeg(RandomAngle);
	
	return _Pos + RandomPosDir;

	//float RandomFloatX = GameEngineRandom::MainRandom.RandomFloat(-_Value, _Value);
	//float RandomFloatY = GameEngineRandom::MainRandom.RandomFloat(-_Value, _Value);

	//return _Pos + float4{RandomFloatX, RandomFloatY, 0};
}


void Player::CalSlashAnimation()
{
	if (float4::Right == PlayerDir)
	{
		SlashEffectActor->GetTransform()->SetLocalNegativeScaleX();
	}
	else
	{
		SlashEffectActor->GetTransform()->SetLocalPositiveScaleX();
	}
	
	if (GameEngineInput::IsPress("MoveUp"))
	{
		CurrentSlash = PlayerSlashAnimation::UpperSlash;
	}
	else if (GameEngineInput::IsPress("MoveDown"))
	{
		if (true == IsGround(GetTransform()->GetWorldPosition()))
		{
			CurrentSlash = CalAttackAnimation();
		}
		else
		{
			CurrentSlash = PlayerSlashAnimation::DownSlash;
		}
	}
	else
	{
		CurrentSlash = CalAttackAnimation();
	}
}


PlayerSlashAnimation Player::CalAttackAnimation()
{
	if (SlashCalTime <= 1.0f)
	{
		if (PlayerSlashAnimation::Slash2 != CurrentSlash)
		{
			CurrentSlash = PlayerSlashAnimation::Slash2;

			return PlayerSlashAnimation::Slash2;
		}
		else
		{
			CurrentSlash = PlayerSlashAnimation::Slash1;

			return PlayerSlashAnimation::Slash1;
		}
	}
	else
	{
		CurrentSlash = PlayerSlashAnimation::Slash2;

		return PlayerSlashAnimation::Slash2;
	}
}

void Player::SetFireBall()
{
	std::shared_ptr<class PlayerFireBall> FireBall = GetLevel()->CreateActor<PlayerFireBall>();
	FireBall->GetTransform()->SetWorldPosition(Pivot->GetTransform()->GetWorldPosition());
	FireBall->SetFireBall(PlayerColmapTexture, PlayerDir);
}

void Player::SetFireBallCastEffect()
{
	float4 PivotPos = Pivot->GetTransform()->GetWorldPosition();
	
	std::shared_ptr<class FireballCastEffect> CastEffect = GetLevel()->CreateActor<FireballCastEffect>();
	//CastEffect->GetTransform()->SetLocalScale({ 1.5f, 1.5f, 1.5f });

	if (float4::Left == PlayerDir)
	{
		CastEffect->GetTransform()->SetLocalNegativeScaleX();
		
		float4 EffectPos = float4{ PivotPos.x -50.0f, PivotPos.y, -70.0f };

		CastEffect->GetTransform()->SetLocalPosition(EffectPos);
	}
	else
	{
		float4 EffectPos = float4{ PivotPos.x + 50.0f, PivotPos.y, -70.0f };

		CastEffect->GetTransform()->SetLocalPosition(EffectPos);
	}

}

void Player::SetShadowDashEffect()
{
	float4 PivotPos = Pivot->GetTransform()->GetWorldPosition();

	std::shared_ptr<class ShadowDashEffect> ShadowDashEffectActor = GetLevel()->CreateActor<ShadowDashEffect>();
	ShadowDashEffectActor->GetTransform()->SetLocalScale({ 1.5f, 1.5f, 1.0f});

	if (float4::Left == PlayerDir)
	{
		float4 EffectPos = float4{ PivotPos.x + 150.0f, PivotPos.y - 60.0f};

		ShadowDashEffectActor->GetTransform()->SetWorldPosition(EffectPos);
	}
	else
	{
		ShadowDashEffectActor->GetTransform()->SetLocalNegativeScaleX();
		float4 EffectPos = float4{ PivotPos.x - 150.0f, PivotPos.y -60.0f };

		ShadowDashEffectActor->GetTransform()->SetWorldPosition(EffectPos);
	}
}


void Player::SetScreamSkillEffect()
{
	float4 PivotPos = Pivot->GetTransform()->GetWorldPosition();
	float4 EffectPos = { PivotPos.x, PivotPos.y + 130.0f, -70.0f };

	std::shared_ptr<class ScreamEffect> ScreamSkillEffect = GetLevel()->CreateActor<ScreamEffect>();
	ScreamSkillEffect->GetTransform()->SetLocalScale({ 1.5f, 1.5f, 1.0f });
	ScreamSkillEffect->GetTransform()->SetLocalPosition(EffectPos);
}

void Player::SetHealingEffect()
{
	float4 PivotPos = Pivot->GetTransform()->GetWorldPosition();
	float4 EffectPos = { PivotPos.x, PivotPos.y, -70.0f };

	std::shared_ptr<class HealingEffect> HealingUpEffect = GetLevel()->CreateActor<HealingEffect>();
	//HealingUpEffect->GetTransform()->SetLocalScale({ 1.5f, 1.5f, 1.0f });
	HealingUpEffect->GetTransform()->SetLocalPosition(EffectPos);
}

void Player::SetGetDamagedEffect()
{
	float4 PivotPos = Pivot->GetTransform()->GetWorldPosition();
	//float4 EffectPos = { PivotPos.x, PivotPos.y + 130.0f, -70.0f };

	std::shared_ptr<class GetDamageEffect> GetDamageEffectActor = GetLevel()->CreateActor<GetDamageEffect>();
	GetDamageEffectActor->GetTransform()->SetLocalScale({ 2.5f, 2.5f, 1.0f });
	GetDamageEffectActor->GetTransform()->SetLocalPosition(PivotPos);
}

void Player::SetPlayerColor(float _Delta)
{
	if (PlayerDamagedTime >= 0)
	{
		DamagedColorAlpha += DamagedColorValue * _Delta * 1.85f;

		if (DamagedColorAlpha >= 1.0f)
		{
			DamagedColorAlpha = 1.0f;
			DamagedColorValue = -1.0f;
		}
		else if (DamagedColorAlpha <= 0.1f)
		{
			DamagedColorAlpha = 0.1f;
			DamagedColorValue = 1.0f;
		}

		//PlayerRenderer->ColorOptionValue.PlusColor = float4{ 1.0f / 255.0f,  1.0f / 255.0f,  1.0f / 255.0f, 0 };
		//PlayerRenderer->ColorOptionValue.MulColor = float4{ 1.0f / 255.0f,  1.0f / 255.0f,  1.0f / 255.0f, 0 };
		//PlayerRenderer->ColorOptionValue.MulColor.a = 1.0f;

		PlayerRenderer->ColorOptionValue.PlusColor = float4{ 0,  0,  0, 0 };
		PlayerRenderer->ColorOptionValue.MulColor = float4{ 255 * DamagedColorAlpha / 255.0f,  255 * DamagedColorAlpha / 255.0f,  255 * DamagedColorAlpha / 255.0f, 1 };
		PlayerRenderer->ColorOptionValue.MulColor.a = 1.0f;
	}
	else
	{
		PlayerRenderer->ColorOptionValue.PlusColor = float4::Null;
		PlayerRenderer->ColorOptionValue.MulColor = float4::One;
	}
}

void Player::OnRoarLockState(float4 _PlayerDir)
{
	PlayerDir = _PlayerDir;

	FSM.ChangeState("RoarLock");
}

void Player::OffRoarLockState()
{
	FSM.ChangeState("Idle");
}

void Player::SetPlayerCollisionPos(float _Value)
{
	if (0.0f == _Value)
	{
		PlayerCollision->GetTransform()->SetLocalPosition(PlayerCollisionPos);
		return;
	}

	if (float4::Left == PlayerDir)
	{
		PlayerCollision->GetTransform()->AddLocalPosition({ -_Value, 0 });	
	}
	else
	{
		PlayerCollision->GetTransform()->AddLocalPosition({ _Value, 0 });
	}
}

float4 Player::GetPlayerCollisionPos()
{
	return PlayerCollision->GetTransform()->GetWorldPosition();
}

void Player::SetFireballHitEffect(float4 _Pos, float4 _Scale)
{
	std::shared_ptr<class FireballHitEnemyEffect> FireballHitEnemyEffectActor = GetLevel()->CreateActor<FireballHitEnemyEffect>();

	FireballHitEnemyEffectActor->SetFireballHitEffect(_Pos, _Scale);
}

void Player::SetEnemyHitSlashEffect(float4 _Pos, float4 _Scale)
{
	std::shared_ptr<class PlayerHitSlashEffect> PlayerHitSlashEffectActor = GetLevel()->CreateActor<PlayerHitSlashEffect>();

	float4 _Dir = _Pos - GetTransform()->GetWorldPosition();

	PlayerHitSlashEffectActor->SetEnemyHitSlashEffect(_Pos, _Scale, CurrentSlash);

	if (_Dir.x <= 0.0f)
	{
		PlayerHitSlashEffectActor->GetTransform()->SetLocalNegativeScaleX();
	}
}

void Player::SetEnemyHitEffect(float4 _Pos, float4 _Scale)
{
	float RandomFloat = GameEngineRandom::MainRandom.RandomFloat(-55.0f, 5.0f);

	std::shared_ptr<class PlayerHitEffect> PlayerHitEffectActor = GetLevel()->CreateActor<PlayerHitEffect>();

	PlayerHitEffectActor->SetEnemyHitEffect(_Pos, _Scale, RandomFloat);
}

void Player::PlayerGetDamagedCheck()
{
	if (PlayerDamagedTime > 0.0f)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> BossCollision = PlayerCollision->Collision(HollowKnightCollisionType::Boss);
	std::shared_ptr<GameEngineCollision> BossAttackCollision = PlayerCollision->Collision(HollowKnightCollisionType::BossAttack);
	std::shared_ptr<GameEngineCollision> BossHardAttackCollision = PlayerCollision->Collision(HollowKnightCollisionType::BossHardAttack);

	if (BossCollision != nullptr)
	{
		PlayerGetDamage(1, PlayerCollision->GetTransform()->GetWorldPosition() - BossCollision->GetTransform()->GetWorldPosition());
		return;
	}

	if (BossAttackCollision != nullptr)
	{
		PlayerGetDamage(1, PlayerCollision->GetTransform()->GetWorldPosition() - BossAttackCollision->GetTransform()->GetWorldPosition());
		return;
	}

	if (BossHardAttackCollision != nullptr)
	{
		PlayerGetDamage(2, PlayerCollision->GetTransform()->GetWorldPosition() - BossHardAttackCollision->GetTransform()->GetWorldPosition());
		return;
	}
}

void Player::PlayerGetDamage(int _Damage, float4 _Dir)
{
	StateCalDir = _Dir;
	PlayerDamagedTime = PlayerConstDamagedTime;

	//UI 만들어서 데미지 깎이는 애니메이션 추가

	DamagedColorAlpha = 0.0f;
	DamagedColorValue = 1.0f;

	CurrentPlayerHP -= _Damage;

	FSM.ChangeState("GetDamaged");
}