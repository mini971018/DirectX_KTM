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
			CalSlashAnimation();

			//TO DO : DownSlash Ÿ�� �� �÷��̾� ���� �ߴ°� �߰� (�ݸ��� �߰� ����)

			switch (CurrentSlash)
			{
			case PlayerSlashAnimation::Slash1:
				PlayerRenderer->ChangeAnimation("Slash1");
				break;
			case PlayerSlashAnimation::Slash2:
				PlayerRenderer->ChangeAnimation("Slash2");
				break;
			case PlayerSlashAnimation::UpperSlash:
				PlayerRenderer->ChangeAnimation("UpSlash");
				break;
			case PlayerSlashAnimation::DownSlash:
				PlayerRenderer->ChangeAnimation("DownSlash");
				break;
			default:
				MsgAssert("�߸��� �÷��̾� Slash �ִϸ��̼��� ȣ���߽��ϴ�.");
				break;
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

			if (true == GameEngineInput::IsDown("Jump") && (PlayerState::Idle == CurrentState || PlayerState::Sprint == CurrentState))
			{
				ResetFallValue();
				CurrentState = PlayerState::Jump;
			}
			else if (PlayerState::Jump == CurrentState)
			{
				if (StateCalTime >= 0.1f && false == GameEngineInput::IsPress("Jump"))
				{
					CurrentState = PlayerState::Fall;
				}

				else if (StateCalTime >= 0.35f)
				{
					StateCalFloat *= 0.95f;

					if (StateCalFloat <= 100.0f)
					{
						CurrentState = PlayerState::Fall;
					}

					GetTransform()->AddWorldPosition(float4::Up * StateCalFloat * _DeltaTime);
				}
				else
				{
					GetTransform()->AddWorldPosition(float4::Up * StateCalFloat * _DeltaTime);
				}

				StateCalTime += _DeltaTime;
				
				if (true == PlayerRenderer->IsAnimationEnd())
				{
					FSM.ChangeState("Jump");
					return;
				}

			}
			else if (PlayerState::Fall == CurrentState)
			{
				Gravity *= 1.05f;

				if (Gravity >= 750.0f)
				{
					Gravity = JumpForce;
				}
				
				if (true == IsGround(GetTransform()->GetWorldPosition()))
				{
					CurrentState = PlayerState::Idle;
				}
				else
				{
					SetGravity(_DeltaTime);
				}
				
				if (true == PlayerRenderer->IsAnimationEnd())
				{
					FSM.ChangeState("Fall");
					return;
				}

			}
			else if (PlayerState::Sprint == CurrentState)
			{
				if (true == PlayerRenderer->IsAnimationEnd())
				{
					FSM.ChangeState("Sprint");
					return;
				}
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

	FSM.CreateState(
		{
			.Name = "Healing",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("AnticFocus");
			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			StateCalTime += _DeltaTime;

			if (true == PlayerRenderer->IsAnimationEnd())
			{
				PlayerRenderer->ChangeAnimation("LoopFocus");
			}

			if (StateCalTime >= 1.0f)
			{
				//ü��ȸ��
				PlayerRenderer->ChangeAnimation("GetOnFocus");
				StateCalTime = 0.0f;
			}

			if (true == GameEngineInput::IsUp("Skill"))
			{
				FSM.ChangeState("HealingEnd");
				return;
			}

		},
			.End = [this]()
		{

		},

		}
	);

	//ToIdleState
	FSM.CreateState(
		{
			.Name = "HealingEnd",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("EndFocus");
			StateCalTime = 0.0f;
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

		},

		}
	);

}