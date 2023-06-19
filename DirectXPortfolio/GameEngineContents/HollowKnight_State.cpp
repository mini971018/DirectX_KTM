#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RoarEffect.h"
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
				FSM.ChangeState("RoarAntic");
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
			.Name = "RoarAntic",
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

	FSM.CreateState(
		{
			.Name = "Idle",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Idle");
		},
			.Update = [this](float _DeltaTime)
		{
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
			if (Pivot->GetTransform()->GetLocalScale().x > 0.0f)
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

			if (StateCalTime >= 0.4f)
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
				if (TurnCheck())
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

	FSM.ChangeState("ChainIdle");
}