#include "PrecompileHeader.h"

#include "Player.h"

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
	AnimationInit();
	StateInit();
}

void Player::Update(float _Delta)
{
	if (GameEngineInput::IsPress("MoveRight"))
	{
		//GetLevel()->GetMainCamera()->GetTransform()->AddWorldPosition(float4::Right * 1500.0f * _Delta);
		GetTransform()->AddWorldPosition(float4::Right * 500.0f * _Delta);
	}

	if (GameEngineInput::IsPress("MoveLeft"))
	{
		//GetLevel()->GetMainCamera()->GetTransform()->AddWorldPosition(float4::Left * 1500.0f * _Delta);
		GetTransform()->AddWorldPosition(float4::Left * 500.0f * _Delta);
	}


	CamDeltaTime += _Delta;
	if (CamDeltaTime >= 1.0f)
	{
		CamDeltaTime = 1.0f;
	}

	CameraMoveLerp();
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
		GameEngineInput::CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("MoveLeft", VK_LEFT);
	}
}

void Player::Test()
{
	GetTransform()->AddWorldPosition({ 960.0f, 0.0f });
}

void Player::SetPlayerRendererPivot()
{
	Pivot->GetTransform()->SetLocalPosition({ PivotPos.x, PivotPos.y, -70.0f });
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
	PlayerRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "00.Idle", .ScaleToTexture = true, });

	if (nullptr == Pivot)
	{
		Pivot = CreateComponent<GameEngineComponent>();
		PlayerRenderer->GetTransform()->SetParent(Pivot->GetTransform());
	}

	std::shared_ptr<class GameEngineSpriteRenderer> PlayerPosRender = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Test);
	PlayerPosRender->GetTransform()->SetLocalScale({ 10, 10, 1 });
	PlayerPosRender->GetTransform()->SetLocalPosition({ 0, 0, -70 });
}

void Player::CameraMoveLerp()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 CamTargetPos = GetTransform()->GetWorldPosition();

	CamTargetPos.z = -1000.0f;
	CamTargetPos.y += 420.0f;

	//float4 ScreenSize = GameEngineWindow::GetScreenSize();
	//CamTargetPos += { -(ScreenSize.x / 2), (ScreenSize.y / 2) - 420.0f };

	float value = CameraPos.XYDistance(CamTargetPos);

	if (value >= 10.0f)
	{
		CamDeltaTime = 0.0f;
	}
	
	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(float4::Lerp(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition(), CamTargetPos, CamDeltaTime));

}