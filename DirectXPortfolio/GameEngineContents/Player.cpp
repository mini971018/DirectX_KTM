#include "PrecompileHeader.h"

#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>

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

}

void Player::Render(float _Delta)
{

}

void Player::CreateKey()
{
	if (false == GameEngineInput::IsKey("ChangeNextLevel"))
	{
		GameEngineInput::CreateKey("ChangeNextLevel", '1');
		GameEngineInput::CreateKey("TestButton1", VK_RBUTTON);
	}
}