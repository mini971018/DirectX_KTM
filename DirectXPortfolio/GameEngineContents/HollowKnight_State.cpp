#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RoarEffect.h"
#include "Player.h"
#include "HollowKnightBoss.h"

void HollowKnightBoss::StateInit()
{
	FSM.CreateState(
		{
			.Name = "ChainIdle",
			.Start = [this]()
		{
			StateCalTime = 0.0f;

		},
			.Update = [this](float _DeltaTime)
		{
			if (GameEngineInput::IsUp("TestButton"))
			{
				FSM.ChangeState("ChainRoar");
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
			.Name = "ChainRoar",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("ChainIdle");

			//float4 EffectPos = GetTransform()->GetWorldPosition();
			//EffectPos += {-10, 300};
			//RoarEffectPos = EffectPos;

			RoarEffectPos = Pivot->GetTransform()->GetWorldPosition();

			CreateRoarEffect(RoarType::White, RoarEffectPos);

			StateCalTime = 0.0f; //Roar Effect 주기
			StateCalTime2 = 0.0f;//다음 스테이트로 넘어가는 시간
		},
			.Update = [this](float _DeltaTime)
		{
			StateCalTime  += _DeltaTime;
			StateCalTime2 += _DeltaTime;

			if (StateCalTime >= 0.2f)
			{
				CreateRoarEffect(RoarType::Black, RoarEffectPos);

				StateCalTime = 0.0f;
			}

			if (StateCalTime2 >= 1.0f)
			{
				FSM.ChangeState("BreakChain");
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
			.Name = "BreakChain",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("BreakChain");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("BreakChainFall");
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
			.Name = "BreakChainFall",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("BreakChainFall");
			Gravity = 2000.0f;

			PivotPos = { 0 , 290 };
			SetBossRendererPivot();
		},
			.Update = [this](float _DeltaTime)
		{

			if (true == IsGround(GetTransform()->GetWorldPosition()))
			{
				//이후 먼지구름 이펙트 및 시간 이후 스테이트 변경되게끔 변경

				FSM.ChangeState("BreakChainLand");
				return;
			}
			else
			{
				SetGravity(_DeltaTime);
			}
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "BreakChainLand",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("BreakChainLand");
			BossWeaponRenderer->Off();
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("AnticRoar");
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
			.Name = "AnticRoar",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("RoarAntic");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Roar");
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
			.Name = "Roar",
			.Start = [this]()
		{
			StateCalTime = 0.0f; //로어이펙트 주기
			StateCalTime2 = 0.0f;  //다음 스테이트로 넘어가는 시간
			
			//float4 EffectPos = GetTransform()->GetWorldPosition();
			//EffectPos += { 125, 365 };
			//RoarEffectPos = EffectPos;
			RoarEffectPos = Pivot->GetTransform()->GetWorldPosition();

			CreateRoarEffect(RoarType::White, RoarEffectPos);

			BossRenderer->ChangeAnimation("Roar");
		},
			.Update = [this](float _DeltaTime)
		{
			StateCalTime += _DeltaTime;
			StateCalTime2 += _DeltaTime;

			if (StateCalTime >= 0.2f)
			{
				CreateRoarEffect(RoarType::Black, RoarEffectPos);

				StateCalTime = 0.0f;
			}

			if (StateCalTime2 >= 2.0f)
			{
				FSM.ChangeState("RoarToIdle");
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
			.Name = "RoarToIdle",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("RoarToIdle");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
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

	//Idle
	FSM.CreateState(
		{
			.Name = "Idle",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Idle");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == IsNextPhase())
			{
				FSM.ChangeState("AnticRoar");
				return;
			}

			if ("Evade" == CurrentState)
			{
				SetRandomAttackPattern();
			}

			if (true == BossRenderer->IsAnimationEnd())
			{
				SetRandomPattern();
				return;
			}
		},
			.End = [this]()
		{

		},

		}
	);

	//Turn
	FSM.CreateState(
		{
			.Name = "Turn",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Turn");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Idle");
				return;
			}
		},
			.End = [this]()
		{
			RotationRenderPivotY();
		},

		}
	);

	//Recover
	FSM.CreateState(
		{
			.Name = "Recover",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Recover");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				if (CheckRenderRotationValue())
				{
					FSM.ChangeState("Turn");
				}
				else
				{
					FSM.ChangeState("Idle");
				}
				return;
			}
		},
			.End = [this]()
		{

		},

		}
	);

	//DashAttack
	FSM.CreateState(
		{
			.Name = "AnticDashAttack",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticDashAttack");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (StateCalTime >= 0.5f)
			{
				FSM.ChangeState("DashAttack");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "DashAttack",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("DashAttack");

			StateCalTime = 0.0f;
			CurrentDashSpeed = DashSpeed;
		},
			.Update = [this](float _DeltaTime)
		{
			//if (true == BossRenderer->IsAnimationEnd())
			//{
			//	FSM.ChangeState("EndDashAttack");
			//	return;
			//}

			GetTransform()->AddWorldPosition(ReturnPatternDir()* CurrentDashSpeed* _DeltaTime);

			if (StateCalTime >= 0.3f)
			{
				FSM.ChangeState("EndDashAttack");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);


	FSM.CreateState(
		{
			.Name = "EndDashAttack",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("EndDashAttack");
		},
			.Update = [this](float _DeltaTime)
		{
			CurrentDashSpeed = CurrentDashSpeed * 0.9f;
			GetTransform()->AddWorldPosition(ReturnPatternDir()* CurrentDashSpeed* _DeltaTime);

			if (CurrentDashSpeed <= 300.0f)
			{
				if (CheckRenderRotationValue())
				{
					FSM.ChangeState("Turn");
				}
				else
				{
					FSM.ChangeState("Idle");
				}
				return;

			}
		},
			.End = [this]()
		{

		},

		}
	);


	//Slash(Normal)
	FSM.CreateState(
		{
			.Name = "AnticSlash1",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticSlash1");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Slash1");
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
			.Name = "Slash1",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Slash1");
		},
			.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash1Speed * _DeltaTime);

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("EndSlash1");
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
			.Name = "EndSlash1",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("EndSlash1");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Slash2");
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
			.Name = "Slash2",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Slash2");
		},
			.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash2Speed* _DeltaTime);

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("EndSlash2");
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
			.Name = "EndSlash2",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("EndSlash2");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Slash3");
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
			.Name = "Slash3",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Slash3");
		},
			.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash3Speed* _DeltaTime);

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Recover");
				return;
			}
		},
			.End = [this]()
		{

		},

		}
	);

	//Counter

	FSM.CreateState(
		{
			.Name = "AnticCounter",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticCounter");
		},
			.Update = [this](float _DeltaTime)
		{

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("ReadyCounter");
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
			.Name = "ReadyCounter",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("ReadyCounter");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			//To do : collision 추가 후, 로직 구현

			if (true == CounterAvailability())
			{
				FSM.ChangeState("BlockCounter");
			}

			if (0.7f <= StateCalTime)
			{
				FSM.ChangeState("NoneBlockCounter");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "NoneBlockCounter",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("NoneBlockCounter");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			//To do : collision 추가 후, 카운터 가능 여부 로직 구현

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Idle");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "BlockCounter",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("BlockCounter");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("CounterSlash2");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "CounterSlash2",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Slash2");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddWorldPosition(ReturnPatternDir()* CounterSlash2Speed * _DeltaTime);

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("EndCounterSlash2");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "EndCounterSlash2",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("EndSlash2");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Recover");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	//SmallShot
	FSM.CreateState(
		{
			.Name = "AnticSmallShot",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticSmallShot");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("SmallShot");
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
			.Name = "SmallShot",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("SmallShot");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (2.0f <= StateCalTime)
			{
				FSM.ChangeState("EndSmallShot");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "EndSmallShot",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("EndSmallShot");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				if (CheckRenderRotationValue())
				{
					FSM.ChangeState("Turn");
				}
				else
				{
					FSM.ChangeState("Idle");
				}
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
			.Name = "AnticBlasts",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticBlasts");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("SmashBlasts");
			}

		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "SmashBlasts",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("SmashBlasts");
			Gravity = 3500.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == IsGround(GetTransform()->GetWorldPosition()))
			{
				FSM.ChangeState("LandBlasts");
			}
			else
			{
				SetGravity(_DeltaTime);
			}
		},
			.End = [this]()
		{

		},

		}
	);



	FSM.CreateState(
		{
			.Name = "LandBlasts",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("LandBlasts");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (1.0f <= StateCalTime)
			{
				FSM.ChangeState("Recover");
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	//Teleport
	FSM.CreateState(
		{
			.Name = "AnticTeleport",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticTeleport");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("EndTeleport");
				return;
			}

		},
			.End = [this]()
		{
			if (CurrentState == "AnticBlasts")
			{
				float4 PlayerPos = Player::CurrentLevelPlayer->GetTransform()->GetWorldPosition();

				GetTransform()->SetWorldPosition({ PlayerPos.x, -1000.0f}); 
			}
			else
			{
				SetRandomTeleportPos();
			}

			BossRenderer->Off();
		},

		}
	);

	FSM.CreateState(
		{
			.Name = "EndTeleport",
			.Start = [this]()
		{
			BossRenderer->On();
			BossRenderer->ChangeAnimation("EndTeleport");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				if (CurrentState == "AnticBlasts")
				{
					FSM.ChangeState(CurrentState);
					return;
				}
				else
				{
					SetRandomAttackPattern();
					return;
				}

				//FSM.ChangeState("Idle");
				//return;
			}

		},
			.End = [this]()
		{

		},

		}
	);

	//Jump
	FSM.CreateState(
		{
			.Name = "Jump",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Jump");
			MoveDir = float4::Zero;
			MoveDir += float4::Up.NormalizeReturn() * JumpForce;
			MoveDir += float4::Left.NormalizeReturn() * MinJumpForceX;

			Gravity = 14000.0f;
			StateCalBool = false;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == IsGround(GetTransform()->GetWorldPosition()) && true == StateCalBool)
			{
				FSM.ChangeState("Recover");
				return;
			}

			if (false == IsGround(GetTransform()->GetWorldPosition()))
			{
				MoveDir += float4::Down.NormalizeReturn() * Gravity * _DeltaTime;
				StateCalBool = true;
			}

			GetTransform()->AddWorldPosition(MoveDir * _DeltaTime);
		},
			.End = [this]()
		{

		},

		}
	);

	//Evade
	FSM.CreateState(
		{
			.Name = "Evade",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Evade");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (0.15f <= StateCalTime)
			{
				FSM.ChangeState("Recover");
			}
			
			GetTransform()->AddWorldPosition( -ReturnPatternDir()* EvadeSpeed* _DeltaTime);

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
	{
		.Name = "Antic",
		.Start = [this]()
	{
		BossRenderer->ChangeAnimation("Antic");

	},
		.Update = [this](float _DeltaTime)
	{
		if (true == BossRenderer->IsAnimationEnd())
		{
			FSM.ChangeState(CurrentState);
			return;
		}

	},
		.End = [this]()
	{

	},

	}
);

	FSM.ChangeState("ChainIdle");
}

//FSM.CreateState(
//	{
//		.Name = "Evade",
//		.Start = [this]()
//	{
//		BossRenderer->ChangeAnimation("Evade");
//
//	},
//		.Update = [this](float _DeltaTime)
//	{
//
//	},
//		.End = [this]()
//	{
//
//	},
//
//	}
//);