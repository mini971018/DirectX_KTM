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
			SkillCalTime = 0.0f;
			SetPlayerRendererPivot();
		},
			.Update = [this](float _DeltaTime)
		{

			if (true == GameEngineInput::IsPress("Skill"))
			{
				SkillCalTime += _DeltaTime;
			}
			else
			{
				SkillCalTime = 0.0f;
			}

			if (true == GameEngineInput::IsUp("Skill") && true == GameEngineInput::IsPress("MoveUp"))
			{
				FSM.ChangeState("Scream");
				return;
			}
		
			if (true == GameEngineInput::IsUp("Skill"))
			{
				FSM.ChangeState("Fireball");
				return;
			}

			if (SkillCalTime >= 0.3f)
			{
				FSM.ChangeState("Healing");
				return;
			}

			if (false == IsGround(GetTransform()->GetWorldPosition()))
			{
				FSM.ChangeState("Fall");
				return;
			}

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

			if (true == Dashable && true == GameEngineInput::IsDown("Dash"))
			{
				SetDashState();
				return;
			}

			if (true == GameEngineInput::IsDown("Attack"))
			{
				FSM.ChangeState("Slash");
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

			CurrentState = PlayerState::Idle;
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

			if (false == IsGround(GetTransform()->GetWorldPosition()))
			{
				FSM.ChangeState("Fall");
				return;
			}

			if (true == GameEngineInput::IsUp("Skill") && true == GameEngineInput::IsPress("MoveUp"))
			{
				FSM.ChangeState("Scream");
				return;
			}

			if (true == GameEngineInput::IsUp("Skill"))
			{
				FSM.ChangeState("Fireball");
				return;
			}

			if (true == Dashable && true == GameEngineInput::IsDown("Dash"))
			{
				SetDashState();
				return;
			}

			if (true == GameEngineInput::IsDown("Jump"))
			{
				FSM.ChangeState("Jump");
				return;
			}

			if (true == GameEngineInput::IsDown("Attack"))
			{
				FSM.ChangeState("Slash");
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
			CurrentState = PlayerState::Sprint;
		},

		}
	);

	//ToIdleState
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

			if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft") || true == GameEngineInput::IsPress("Skill"))
			{
				FSM.ChangeState("Idle");
				return;
			}

			CurrentState = PlayerState::Sprint;
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

			CurrentState = PlayerState::Idle;
		},

		}
	);

	FSM.CreateState(
		{
			.Name = "Jump",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Jump");

			if (CurrentState != PlayerState::Slash)
			{
				ResetFallValue();
			}
		},
			.Update = [this](float _DeltaTime)
		{

			if (StateCalTime >= 0.1f && false == GameEngineInput::IsPress("Jump"))
			{
				FSM.ChangeState("Fall");
				return;
			}

			if (true == GameEngineInput::IsPress("Attack"))
			{
				FSM.ChangeState("Slash");
				return;
			}

			if (true == GameEngineInput::IsUp("Skill") && true == GameEngineInput::IsPress("MoveUp"))
			{
				FSM.ChangeState("Scream");
				return;
			}

			if (true == GameEngineInput::IsUp("Skill"))
			{
				FSM.ChangeState("Fireball");
				return;
			}

			if (true == Dashable && true == GameEngineInput::IsDown("Dash"))
			{
				SetDashState();
				return;
			}
			else if (StateCalTime >= 0.35f)
			{
				StateCalFloat *= 0.95f;

				if (StateCalFloat <= 100.0f)
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

			//SetGravity(_DeltaTime);
			StateCalTime += _DeltaTime;

		},
			.End = [this]()
		{
			CurrentState = PlayerState::Jump;
		},

		}
	);

	FSM.CreateState(
		{
			.Name = "DoubleJump",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("DoubleJump");

			if (CurrentState != PlayerState::Slash)
			{
				ResetFallValue();
			}
		},
			.Update = [this](float _DeltaTime)
		{

			if (StateCalTime >= 0.1f && false == GameEngineInput::IsPress("Jump"))
			{
				FSM.ChangeState("Fall");
				return;
			}


			if (true == GameEngineInput::IsPress("Attack"))
			{
				FSM.ChangeState("Slash");
				return;
			}

			if (true == GameEngineInput::IsUp("Skill") && true == GameEngineInput::IsPress("MoveUp"))
			{
				FSM.ChangeState("Scream");
				return;
			}

			if (true == GameEngineInput::IsUp("Skill"))
			{
				FSM.ChangeState("Fireball");
				return;
			}

			if (true == Dashable && true == GameEngineInput::IsDown("Dash"))
			{
				SetDashState();
				return;
			}
			else if (StateCalTime >= 0.35f)
			{
				StateCalFloat *= 0.95f;

				if (StateCalFloat <= 100.0f)
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

			//SetGravity(_DeltaTime);
			StateCalTime += _DeltaTime;

		},
			.End = [this]()
		{
			CurrentState = PlayerState::Jump;
		},

		}
	);


	FSM.CreateState(
		{
			.Name = "Fall",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Fall");
		},
			.Update = [this](float _DeltaTime)
		{
			Gravity *= 1.05f;

			if (Gravity >= 950.0f)
			{
				Gravity = 950.0f;
			}

			if (true == PlayerRenderer->IsAnimationEnd())
			{
				PlayerRenderer->ChangeAnimation("FallLoop");
			}

			if (true == IsGround(GetTransform()->GetWorldPosition()))
			{
				FSM.ChangeState("Land");
				return;
			}

			if (true == Dashable && true == GameEngineInput::IsDown("Dash"))
			{
				SetDashState();
				return;
			}

			if (true == GameEngineInput::IsDown("Attack"))
			{
				FSM.ChangeState("Slash");
				return;
			}

			if (true == GameEngineInput::IsUp("Skill") && true == GameEngineInput::IsPress("MoveUp"))
			{
				FSM.ChangeState("Scream");
				return;
			}

			if (true == GameEngineInput::IsUp("Skill"))
			{
				FSM.ChangeState("Fireball");
				return;
			}

			if (true == DoubleJumpable && true == GameEngineInput::IsDown("Jump"))
			{
				FSM.ChangeState("DoubleJump");
				DoubleJumpable = false;
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
			CurrentState = PlayerState::Fall;

		},

		}
	);

	//ToIdleState
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

			if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft") || true == GameEngineInput::IsPress("Skill"))
			{
				FSM.ChangeState("Idle");
				return;
			}

			if (true == GameEngineInput::IsDown("Attack"))
			{
				FSM.ChangeState("Slash");
				return;
			}

			if (true == GameEngineInput::IsDown("Jump"))
			{
				FSM.ChangeState("Jump");
				return;
			}

			if (true == Dashable && true == GameEngineInput::IsDown("Dash"))
			{
				SetDashState();
				return;
			}

		},
			.End = [this]()
		{
			CurrentState = PlayerState::Idle;

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "Dash",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Dash");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				if (true == IsGround(GetTransform()->GetWorldPosition()))
				{
					FSM.ChangeState("DashToIdle");
					return;
				}
				else
				{
					ResetFallValue();

					FSM.ChangeState("Fall");
					return;
				}
			}

			if (float4::Left == PlayerDir)
			{
				GetTransform()->AddWorldPosition(float4::Left* DashSpeed * _DeltaTime);
			}
			else
			{
				GetTransform()->AddWorldPosition(float4::Right* DashSpeed* _DeltaTime);
			}

		},
			.End = [this]()
		{
			CurrentState = PlayerState::Dash;
			Dashable = false;
		},

		}
	);

	FSM.CreateState(
		{
			.Name = "ShadowDash",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("ShadowDash");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				if (true == IsGround(GetTransform()->GetWorldPosition()))
				{
					FSM.ChangeState("DashToIdle");
					return;
				}
				else
				{
					ResetFallValue();

					FSM.ChangeState("Fall");
					return;
				}
			}

			if (float4::Left == PlayerDir)
			{
				GetTransform()->AddWorldPosition(float4::Left * DashSpeed * _DeltaTime);
			}
			else
			{
				GetTransform()->AddWorldPosition(float4::Right * DashSpeed * _DeltaTime);
			}

		},
			.End = [this]()
		{
			CurrentState = PlayerState::Dash;
			ResetShadowDashValue();
			Dashable = false;
		},
		}
	);

	//ToIdleState
	FSM.CreateState(
		{
			.Name = "DashToIdle",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("DashToIdle");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				if (true == IsGround(GetTransform()->GetWorldPosition()))
				{
					FSM.ChangeState("Idle");
					return;
				}
			}

			if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft"))
			{
				FSM.ChangeState("Idle");
				return;
			}

			if (true == GameEngineInput::IsDown("Attack"))
			{
				FSM.ChangeState("Slash");
				return;
			}

			if (true == GameEngineInput::IsDown("Jump"))
			{
				FSM.ChangeState("Jump");
				return;
			}

			if (true == GameEngineInput::IsDown("Dash"))
			{
				FSM.ChangeState("Dash");
				return;
			}
		},
			.End = [this]()
		{
			CurrentState = PlayerState::Idle;
		},

		}
	);

	FSM.ChangeState("Idle");
}