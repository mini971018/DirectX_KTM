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
			PivotPos = { 0 , 268 };
			SetBossRendererPivot();

			BossRenderer->ChangeAnimation("Idle");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == IsNextPhase())
			{
				return;
			}

			if ("Evade" == CurrentState)
			{
				SetRandomAttackPattern();
			}

			if ("AnticSelfStab" == CurrentState)
			{
				FSM.ChangeState("AnticSelfStab");
				return;
			}

			if ("StunLand" == CurrentState)
			{
				FSM.ChangeState("StunLand");
				return;
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

	//Antic
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

	//SelfStab
	FSM.CreateState(
		{
			.Name = "AnticSelfStab",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticSelfStab");
			StateCalInt = 0;
			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				BossRenderer->ChangeAnimation("AnticLoopSelfStab");
			}

			if (1.5f <= StateCalTime)
			{
				FSM.ChangeState("SelfStab");
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
			.Name = "SelfStab",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("SelfStab");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				BossRenderer->ChangeAnimation("LoopSelfStab");
			}

			if (1.3f <= StateCalTime)
			{
				FSM.ChangeState("ReAnticSelfStab");
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
			.Name = "ReAnticSelfStab",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("ReAnticSelfStab");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("ReSelfStab");
			}
		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "ReSelfStab",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("ReSelfStab");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				++StateCalInt;

				if (Phase3StabCount == StateCalInt)
				{
					FSM.ChangeState("ReSelfStabLoop");
					return;
				}
				else
				{
					FSM.ChangeState("ReAnticSelfStab");
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
			.Name = "ReSelfStabLoop",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("LoopSelfStab");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (0.75f <= StateCalTime)
			{
				FSM.ChangeState("StunLand");
				return;
			}

			StateCalTime += _DeltaTime;

		},
			.End = [this]()
		{

		},

		}
	);

	//StunLand
	FSM.CreateState(
		{
			.Name = "StunLand",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("StunLand");
			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (1.5f <= StateCalTime)
			{
				FSM.ChangeState("StunToIdle");
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
			.Name = "StunToIdle",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("StunToIdle");
			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Idle");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{
			CurrentState = "Idle";
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