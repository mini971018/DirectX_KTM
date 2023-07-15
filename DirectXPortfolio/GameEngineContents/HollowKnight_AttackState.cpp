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
			CurrentDashSpeed -= (DashSpeed * 3.0f * _DeltaTime);
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
			if (CurrentPhase != HollowKnightPatternEnum::Phase4)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash1Speed* _DeltaTime);
			}

			if (true == BossRenderer->IsAnimationEnd())
			{
				if (CurrentPhase == HollowKnightPatternEnum::Phase4)
				{
					FSM.ChangeState("StunLand");
					return;
				}
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
					return;
				}
				else
				{
					FSM.ChangeState("Idle");
					return;

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
				return;
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
				return;
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
					return;
				}
				else
				{
					FSM.ChangeState("EndPuppet");
					return;
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

			PivotPos = { 0 , 290 };
			SetBossRendererPivot();

			StateCalTime = 0.0f;
		},	
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("StunLand");
				return;
			}
		},
			.End = [this]()
		{

		},

		}
	);

	//ChestShot
	FSM.CreateState(
		{
			.Name = "AnticChestShot",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("AnticChestShot");

		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("ShotChest");
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
			.Name = "ShotChest",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("ShotChest");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (StateCalTime <= 0.1f)
			{
				GetTransform()->AddWorldPosition(float4::Up * 2500.0f * _DeltaTime);
			}

			if (StateCalTime >= 8.0f)
			{
				FSM.ChangeState("ChestShotLand");
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
			.Name = "ChestShotLand",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Jump");
			Gravity = 2000.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddWorldPosition(float4::Down * Gravity* _DeltaTime);

			if (true == IsGround(GetTransform()->GetWorldPosition()))
			{
				FSM.ChangeState("StunLand");
				return;
			}
		},
			.End = [this]()
		{

		},

		}
	);


}