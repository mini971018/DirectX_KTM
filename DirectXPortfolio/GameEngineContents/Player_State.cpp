#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Player.h"

void Player::StateInit()
{
	FSM.CreateState(
		{
			.Name = "Idle",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Idle");

			PivotPos = { 0, 90.0f };
			SetPlayerRendererPivot();
		},
			.Update = [this](float _DeltaTime)
		{

			if (true == GameEngineInput::IsPress("MoveRight") && false == GameEngineInput::IsPress("MoveLeft"))
			{
				PlayerDir = float4::Right;

				FSM.ChangeState("Sprint");
				return;
			}

			if (false == GameEngineInput::IsPress("MoveRight") && true == GameEngineInput::IsPress("MoveLeft"))
			{
				PlayerDir = float4::Left;

				FSM.ChangeState("Sprint");
				return;
			}

		},
			.End = [this]()
		{
			if (PlayerDir == float4::Right)
			{
				Pivot->GetTransform()->SetLocalNegativeScaleX();
			}
			else
			{
				Pivot->GetTransform()->SetLocalPositiveScaleX();
			}
		},

		}
	);


	FSM.CreateState(
		{
			.Name = "Sprint",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("AnticSprint");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				PlayerRenderer->ChangeAnimation("Sprint");
			}

			if (false == GameEngineInput::IsPress("MoveRight") && false == GameEngineInput::IsPress("MoveLeft"))
			{
				FSM.ChangeState("SprintToIdle");
				return;
			}

			if (true == GameEngineInput::IsPress("MoveRight") && true == GameEngineInput::IsPress("MoveLeft"))
			{
				FSM.ChangeState("SprintToIdle");
				return;
			}

			if (true == GameEngineInput::IsPress("MoveLeft") && false == GameEngineInput::IsPress("MoveRight"))
			{
				if (float4::Right == PlayerDir)
				{
					PlayerDir = float4::Left;

					FSM.ChangeState("Turn");
					return;
				}
				else
				{
					GetTransform()->AddWorldPosition(float4::Left * MoveSpeed * _DeltaTime);
				}
			}
			else if (false == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("MoveRight"))
			{
				if (float4::Left == PlayerDir)
				{
					PlayerDir = float4::Right;

					FSM.ChangeState("Turn");
					return;
				}
				else
				{
					GetTransform()->AddWorldPosition(float4::Right * MoveSpeed * _DeltaTime);
				}
			}



		},
			.End = [this]()
		{
			int a = 0;
		},

		}
	);

	FSM.CreateState(
		{
			.Name = "SprintToIdle",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("SprintToIdle");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Idle");
				return;
			}

			if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft"))
			{
				FSM.ChangeState("Idle");
				return;
			}
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "Turn",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Turn");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Idle");
				return;
			}
		},
			.End = [this]()
		{
			if (PlayerDir == float4::Right)
			{
				Pivot->GetTransform()->SetLocalNegativeScaleX();
			}
			else
			{
				Pivot->GetTransform()->SetLocalPositiveScaleX();
			}

			int a = 0;
		},

		}
	);


	FSM.ChangeState("Idle");
}