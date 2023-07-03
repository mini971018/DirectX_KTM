#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Player.h"

void Player::AttackStateInit()
{
	FSM.CreateState(
		{
			.Name = "Slash",
			.Start = [this]()
		{
			if (GameEngineInput::IsDown("Attack"))
			{
				if (PlayerSlashAnimation::Slash1 == CalAttackAnimation())
				{
					PlayerRenderer->ChangeAnimation("Slash1");
				}
				else
				{
					PlayerRenderer->ChangeAnimation("Slash2");
				}
			}

		},
			.Update = [this](float _DeltaTime)
		{


			if (true == GameEngineInput::IsPress("MoveLeft") && false == GameEngineInput::IsPress("MoveRight"))
			{
				if (float4::Right == PlayerDir)
				{
					PlayerDir = float4::Left;
					Pivot->GetTransform()->SetLocalPositiveScaleX();
				}

				GetTransform()->AddWorldPosition(float4::Left * MoveSpeed * _DeltaTime);
			}
			else if (false == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("MoveRight"))
			{
				if (float4::Left == PlayerDir)
				{
					PlayerDir = float4::Right;
					Pivot->GetTransform()->SetLocalNegativeScaleX();
				}

				GetTransform()->AddWorldPosition(float4::Right * MoveSpeed * _DeltaTime);
			}

			if (PlayerState::Jump == CurrentState)
			{

			}
			else if (PlayerState::Fall == CurrentState)
			{

			}
			else
			{
				if (true == PlayerRenderer->IsAnimationEnd())
				{
					FSM.ChangeState("Idle");
					return;
				}
			}

		},
			.End = [this]()
		{
			SlashCalTime = 0.0f;

			CurrentState = PlayerState::Slash;
		},

		}
	);
}