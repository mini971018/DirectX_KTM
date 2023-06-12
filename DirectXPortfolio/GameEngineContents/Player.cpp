#include "PrecompileHeader.h"

#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	CreateKey();
}

void Player::Update(float _Delta)
{
	if (GameEngineInput::IsPress("MoveRight"))
	{
		GetLevel()->GetMainCamera()->GetTransform()->AddWorldPosition(float4::Right * 1500.0f * _Delta);
	}

	if (GameEngineInput::IsPress("MoveLeft"))
	{
		GetLevel()->GetMainCamera()->GetTransform()->AddWorldPosition(float4::Left * 1500.0f * _Delta);
	}
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
		GameEngineInput::CreateKey("ChangeNextLevel", '0');
		GameEngineInput::CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("MoveLeft", VK_LEFT);
	}
}