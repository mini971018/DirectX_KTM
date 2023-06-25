#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RoarEffect.h"
#include "Player.h"
#include "HollowKnightBoss.h"

void HollowKnightBoss::AttackStateInit()
{
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

			GetTransform()->AddWorldPosition(ReturnPatternDir() * CurrentDashSpeed * _DeltaTime);

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
			GetTransform()->AddWorldPosition(ReturnPatternDir() * CurrentDashSpeed * _DeltaTime);

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
			GetTransform()->AddWorldPosition(ReturnPatternDir() * Slash1Speed * _DeltaTime);

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
			GetTransform()->AddWorldPosition(ReturnPatternDir() * Slash2Speed * _DeltaTime);

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
			GetTransform()->AddWorldPosition(ReturnPatternDir() * Slash3Speed * _DeltaTime);

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
			GetTransform()->AddWorldPosition(ReturnPatternDir() * CounterSlash2Speed * _DeltaTime);

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

	//PuppetSlam
	FSM.CreateState(
		{
			.Name = "AnticPuppet",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticPuppet");

			StateCalTime = 0.0f;
			StateCalInt = 0;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("UpPuppet");
			}

		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "UpPuppet",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("UpPuppet");

			PivotPos = { 0 , 268 };
			SetBossRendererPivot();

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (GetTransform()->GetWorldPosition().y <= -800.0f)
			{
				GetTransform()->AddWorldPosition({ 0.0f, 1000.0f * _DeltaTime });
			}
			else
			{
				FSM.ChangeState("DownPuppet");
			}


		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "DownPuppet",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("DownPuppet");
			Gravity = 2000.0f;

			PivotPos = { 0 , 103 };
			SetBossRendererPivot();

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == IsGround(GetTransform()->GetWorldPosition()))
			{
				FSM.ChangeState("SlamPuppet");
			}
			else
			{
				GetTransform()->AddWorldPosition(float4::Down * Gravity * _DeltaTime);
			}


		},
			.End = [this]()
		{
			++StateCalInt;
		},

		}
	);

	FSM.CreateState(
		{
			.Name = "SlamPuppet",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("SlamPuppet");

			PivotPos = { 0 , 150 };
			SetBossRendererPivot();

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (StateCalTime >= 0.1f)
			{
				if (StateCalInt <= 3)
				{
					FSM.ChangeState("UpPuppet");
				}
				else
				{
					FSM.ChangeState("EndPuppet");
				}
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
			.Name = "EndPuppet",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("EndPuppet");

			PivotPos = { 0 , 268 };
			SetBossRendererPivot();

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("StunLand");
			}
		},
			.End = [this]()
		{

		},

		}
	);

}