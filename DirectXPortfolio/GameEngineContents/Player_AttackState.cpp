#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "FocusEffect.h"
#include "SlashEffect.h"

#include "Player.h"

void Player::AttackStateInit()
{
	FSM.CreateState(
		{
			.Name = "Slash",
			.Start = [this]()
		{
			CalSlashAnimation();

			//TO DO : DownSlash 타격 후 플레이어 위로 뜨는거 추가 (콜리전 추가 이후)

			switch (CurrentSlash)
			{
			case PlayerSlashAnimation::Slash1:
			{
				GameEngineSoundPlayer SlashSound = GameEngineSound::Play("PlayerSlash1.wav");
				SlashEffectActor->SetSlashEffect(PlayerSlashAnimation::Slash1, NormalSlashPos, PlayerDamage);
				PlayerRenderer->ChangeAnimation("Slash1");
				break;
			}
			case PlayerSlashAnimation::Slash2:
			{
				GameEngineSoundPlayer SlashSound = GameEngineSound::Play("PlayerSlash2.wav");
				SlashEffectActor->SetSlashEffect(PlayerSlashAnimation::Slash2, NormalSlashPos, PlayerDamage);
				PlayerRenderer->ChangeAnimation("Slash2");
				break;
			}
			case PlayerSlashAnimation::UpperSlash:
			{
				GameEngineSoundPlayer SlashSound = GameEngineSound::Play("PlayerUpperSlash.wav");
				SlashEffectActor->SetSlashEffect(PlayerSlashAnimation::UpperSlash, UpperSlashPos, PlayerDamage);
				PlayerRenderer->ChangeAnimation("UpSlash");
				break;
			}
			case PlayerSlashAnimation::DownSlash:
			{
				GameEngineSoundPlayer SlashSound = GameEngineSound::Play("PlayerLowerSlash.wav");
				SlashEffectActor->SetSlashEffect(PlayerSlashAnimation::DownSlash, DownSlashPos, PlayerDamage);
				PlayerRenderer->ChangeAnimation("DownSlash");
				break;
			}
			default:
				MsgAssert("잘못된 플레이어 Slash 애니메이션을 호출했습니다.");
				break;
			}
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == Dashable && true == GameEngineInput::IsDown("Dash"))
			{
				SetDashState();
				return;
			}

			if (true == GameEngineInput::IsPress("MoveLeft") && false == GameEngineInput::IsPress("MoveRight") && false == IsLeftWallCheck())
			{
				if (float4::Right == PlayerDir)
				{
					PlayerDir = float4::Left;
					Pivot->GetTransform()->SetLocalPositiveScaleX();
				}

				GetTransform()->AddWorldPosition(float4::Left * MoveSpeed * _DeltaTime);
			}
			else if (false == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("MoveRight") && false == IsRightWallCheck())
			{
				if (float4::Left == PlayerDir)
				{
					PlayerDir = float4::Right;
					Pivot->GetTransform()->SetLocalNegativeScaleX();
				}

				GetTransform()->AddWorldPosition(float4::Right * MoveSpeed * _DeltaTime);
			}

			if (CurrentSlash == PlayerSlashAnimation::DownSlash && true == SlashEffectActor->GetIsHit())
			{
				if (false == IsUpperWallCheck())
				{
					GetTransform()->AddWorldPosition(float4::Up * 650.0f * _DeltaTime);
				}

				CurrentState = PlayerState::Fall;

				if (true == PlayerRenderer->IsAnimationEnd())
				{
					ResetFallValue();

					FSM.ChangeState("Fall");
					return;
				}
				return;
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
					StateCalFloat = StateCalFloat - (7000.0f * _DeltaTime);
			
					if (StateCalFloat <= 100.0f)
					{
						CurrentState = PlayerState::Fall;
					}

					if (false == IsUpperWallCheck())
					{
						GetTransform()->AddWorldPosition(float4::Up * StateCalFloat * _DeltaTime);
					}
					else
					{
						CurrentState = PlayerState::Fall;
					}
				}
				else
				{
					if (false == IsUpperWallCheck())
					{
						GetTransform()->AddWorldPosition(float4::Up * StateCalFloat * _DeltaTime);
					}
					else
					{
						CurrentState = PlayerState::Fall;
					}
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
				Gravity = Gravity + (2500.0f * _DeltaTime);

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
			HealingFocusSound = GameEngineSound::Play("PlayerHealFocus.wav");
			HealingFocusSound.SetLoop();

			PlayerRenderer->ChangeAnimation("AnticFocus");
			FocusEffectActor->OnFocusEffect();
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
				//체력회복
				GameEngineSoundPlayer HealingSound = GameEngineSound::Play("PlayerHealed.wav");
				PlayerGetHealed();
				PlayerRenderer->ChangeAnimation("GetOnFocus");
				CurrentPlayerMP -= HealingCost;
				SetHealingEffect();
				StateCalTime = 0.0f;
			}

			if (true == GameEngineInput::IsUp("Skill") || SkillStateCheck(HealingCost) == false)
			{
				FSM.ChangeState("HealingEnd");
				return;
			}

		},
			.End = [this]()
		{
			HealingFocusSound.Stop();
			FocusEffectActor->OffFocusEffect();
		},

		}
	);

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

	FSM.CreateState(
		{
			.Name = "Scream",
			.Start = [this]()
		{

			PlayerRenderer->ChangeAnimation("AnticScream");
			SetCameraShakeLoop(20.0f);

			SetScreamSkillEffect();
			StateCalTime = 0.0f;

			GameEngineSoundPlayer SlashSound = GameEngineSound::Play("PlayerScreamSpell.wav");
		},
			.Update = [this](float _DeltaTime)
		{
			StateCalTime += _DeltaTime;

			if (StateCalTime >= 0.4f)
			{
				SetCameraShakeOff();
				CurrentPlayerMP -= HealingCost;
				FSM.ChangeState("EndScream");
				return;
			}

			if (true == PlayerRenderer->IsAnimationEnd())
			{
				PlayerRenderer->ChangeAnimation("LoopScream");
			}

		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "EndScream",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("EndScream");
			StateCalCount = 0;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				if (false == IsGround(GetTransform()->GetWorldPosition()))
				{
					FSM.ChangeState("Fall");
					return;
				}
				else
				{
					FSM.ChangeState("Idle");
					return;
				}
			}

		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "Fireball",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("FireballCast");
			CurrentPlayerMP -= HealingCost;
			GameEngineSoundPlayer FireballSound = GameEngineSound::Play("PlayerFireball.wav");
			SetCameraShakeOnce(20.0f);
			SetFireBallCastEffect();
			SetFireBall();
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == PlayerRenderer->IsAnimationEnd())
			{
				if (false == IsGround(GetTransform()->GetWorldPosition()))
				{
					FSM.ChangeState("Fall");
					return;
				}
				else
				{
					FSM.ChangeState("Idle");
					return;
				}
			}
		},
			.End = [this]()
		{

		},

		}
	);
}