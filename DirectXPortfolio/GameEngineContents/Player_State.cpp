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

			if (true == GameEngineInput::IsDown("Jump"))
			{
				FSM.ChangeState("Jump");
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

			if (true == GameEngineInput::IsDown("Jump"))
			{
				FSM.ChangeState("Jump");
				return;
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

	FSM.CreateState(
		{
			.Name = "Jump",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Jump");

			Gravity = 250.0f;
			StateCalTime = 0.0f;
			StateCalFloat = JumpForce; //���� ������ �ִ� ���� �Ÿ����� ���� �ö󰡴� �ӵ��� �ٿ��ֱ� ���� ����
		},
			.Update = [this](float _DeltaTime)
		{

			if (StateCalTime >= 0.1f && false == GameEngineInput::IsPress("Jump"))
			{
				FSM.ChangeState("Fall");
				return;
			}
			else if (StateCalTime >= 0.5f)
			{
				FSM.ChangeState("Fall");
				return;
			}
			else if (StateCalTime >= 0.3f)
			{
				StateCalFloat *= 0.99f;

				if (StateCalFloat <= Gravity)
				{
					FSM.ChangeState("Fall");
					return;
				}

				GetTransform()->AddWorldPosition(float4::Up * StateCalFloat * _DeltaTime);
			}
			else
			{
				GetTransform()->AddWorldPosition(float4::Up * StateCalFloat * _DeltaTime);
			}

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

			SetGravity(_DeltaTime);
			StateCalTime += _DeltaTime;

			
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "Fall",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Fall");
			Gravity = 400.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			Gravity *= 1.005f;

			if (true == PlayerRenderer->IsAnimationEnd())
			{
				PlayerRenderer->ChangeAnimation("FallLoop");
			}

			if (true == IsGround(GetTransform()->GetWorldPosition()))
			{
				FSM.ChangeState("Land");
				return;
			}

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

			SetGravity(_DeltaTime);
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "Land",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Land");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Idle");
				return;
			}

			if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft") || true == GameEngineInput::IsDown("Jump"))
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


	FSM.ChangeState("Idle");
}