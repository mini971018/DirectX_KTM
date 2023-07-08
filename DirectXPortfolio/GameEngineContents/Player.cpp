#include "PrecompileHeader.h"

#include "Player.h"
#include "ShadowDashRechargedEffect.h"
#include "ScreamEffect.h"
#include "PlayerFireBall.h"
#include "FireballCastEffect.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>

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
}

void Player::Update(float _Delta)
{
	FSM.Update(_Delta);

	//카메라 관련
	CamDeltaTime += _Delta * 10.0f;
	if (CamDeltaTime >= 1.0f)
	{
		CamDeltaTime = 1.0f;
	}
	CameraMoveLerp();

	SlashCalTime += _Delta; // 일반공격 애니메이션을 확인하기 위한 변수
	ShadowDashCalTime += _Delta; // ShadowDash 쿨타임 계산을 위한 변수

	if (ShadowDashCalTime >= (ShadowDashCooltime - 0.68) && ShadowDashEffectIsOn == false)
	{
		ShadowDashRechargedEffectActor->OnRechargedEffect();
		ShadowDashEffectIsOn = true;
	}

	SetStateAbleValue();
}

void Player::Render(float _Delta)
{

}

void Player::CreateKey()
{
	if (false == GameEngineInput::IsKey("ChangeNextLevel"))
	{
		GameEngineInput::CreateKey("TestButton", '1');
		GameEngineInput::CreateKey("TestButton2", '2');
		GameEngineInput::CreateKey("TestButton3", '3');
		GameEngineInput::CreateKey("TestButton4", '4');
		
		GameEngineInput::CreateKey("ChangeNextLevel", '0');

		GameEngineInput::CreateKey("MoveUp", VK_UP);
		GameEngineInput::CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("MoveLeft", VK_LEFT);

		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'Z');
		GameEngineInput::CreateKey("Dash", 'C');
		GameEngineInput::CreateKey("Skill", 'A');
	}
}

void Player::Test()
{
	GetTransform()->AddWorldPosition({ 960.0f, 0.0f });
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

void Player::InitPlayer(std::string_view ColMap)
{
	std::shared_ptr<GameEngineTexture> ColmapTexture = GameEngineTexture::Find(ColMap);

	if (nullptr != ColmapTexture)
	{
		PlayerColmapTexture = ColmapTexture;
	}
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
	PlayerRenderer->CreateAnimation({ .AnimationName = "FocusEffect", .SpriteName = "94.FocusEffect",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "LoopFocusEffect", .SpriteName = "95.LoopFocusEffect",  .FrameInter = 0.055f, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "EndFocusEffect", .SpriteName = "96.EndFocusEffect",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "HealingEffect", .SpriteName = "97.HealingEffect",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });

	//Scream
	PlayerRenderer->CreateAnimation({ .AnimationName = "AnticScream", .SpriteName = "29.AnticScream",  .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "LoopScream", .SpriteName = "30.LoopScream",  .FrameInter = 0.07f, .ScaleToTexture = true, });
	PlayerRenderer->CreateAnimation({ .AnimationName = "EndScream", .SpriteName = "31.EndScream",  .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true, });

	//Fireball
	PlayerRenderer->CreateAnimation({ .AnimationName = "FireballCast", .SpriteName = "32.FireballCast",  .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true, });


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
}

void Player::CameraMoveLerp()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 CamTargetPos = GetTransform()->GetWorldPosition();

	CamTargetPos.z = -1000.0f;
	CamTargetPos.y = CameraPos.y;

	//CamTargetPos.y += 400.0f;

	//float4 ScreenSize = GameEngineWindow::GetScreenSize();
	//CamTargetPos += { -(ScreenSize.x / 2), (ScreenSize.y / 2) - 420.0f };

	float value = CameraPos.XYDistance(CamTargetPos);

	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(float4::Lerp(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition(), CamTargetPos, CamDeltaTime));

	if (value >= 0.5f)
	{
		CamDeltaTime = 0.0f;
	}
	

}

void Player::CalSlashAnimation()
{
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

void Player::SetScreamSkillEffect()
{
	float4 PivotPos = Pivot->GetTransform()->GetWorldPosition();
	float4 EffectPos = { PivotPos.x, PivotPos.y + 130.0f, -70.0f };

	std::shared_ptr<class ScreamEffect> ScreamSkillEffect = GetLevel()->CreateActor<ScreamEffect>();
	ScreamSkillEffect->GetTransform()->SetLocalScale({ 1.5f, 1.5f, 1.0f });
	ScreamSkillEffect->GetTransform()->SetLocalPosition(EffectPos);
}