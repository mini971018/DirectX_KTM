#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>

#include "RoarEffect.h"
#include "Player.h"
#include "HollowKnightBoss.h"
#include "HollowKnightSmallShotEffect.h"
#include "ChestShotEffect.h"

void HollowKnightBoss::AttackStateInit()
{
	//DashAttack
	FSM.CreateState(
		{
			.Name = "AnticDashAttack",
			.Start = [this]()
		{
			SetSoundPlayOnce("HollowKnightPrepare.wav");
			BossRenderer->ChangeAnimation("AnticDashAttack");
			SetCollisionValue(float4{ 295,290,1 }, float4{ -75.0f, HollowKnightCollisionIdlePos.y - 20.0f , -70.0f });
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
			SetSoundPlayOnce("HollowKnightDashAttack.wav");
			SetIdleCollision();
			SetDashEffect();
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

			if (IsLeftWallCheck() == false && ReturnPatternDir() == float4::Left)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir() * CurrentDashSpeed * _DeltaTime);
			}

			if (IsRightWallCheck() == false && ReturnPatternDir() == float4::Right)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir() * CurrentDashSpeed * _DeltaTime);
			}

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
			SetCollisionValue(float4{ 235,290,1 }, float4{ -30.0f, HollowKnightCollisionIdlePos.y , -70.0f });
		},
			.Update = [this](float _DeltaTime)
		{
			CurrentDashSpeed -= (DashSpeed * 3.0f * _DeltaTime);
			
			if (IsLeftWallCheck() == false && ReturnPatternDir() == float4::Left)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir() * CurrentDashSpeed * _DeltaTime);
			}

			if (IsRightWallCheck() == false && ReturnPatternDir() == float4::Right)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir() * CurrentDashSpeed * _DeltaTime);
			}

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
			SetCollisionValue(HollowKnightCollisionIdleScale, float4{ -110.0f, HollowKnightCollisionIdlePos.y , -70.0f });

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
			SetIdleCollision();
		},

		}
	);

	FSM.CreateState(
		{
			.Name = "Slash1",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Slash1");
			SetSlashAttackCollision();
			SetSoundPlayOnce("HollowKnightSlash.wav");
		},
			.Update = [this](float _DeltaTime)
		{
			if (CurrentPhase != HollowKnightPatternEnum::Phase4)
			{
				if (IsLeftWallCheck() == false && ReturnPatternDir() == float4::Left)
				{
					GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash1Speed* _DeltaTime);
				}

				if (IsRightWallCheck() == false && ReturnPatternDir() == float4::Right)
				{
					GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash1Speed* _DeltaTime);
				}
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
			AttackCollision->Off();
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
			SetSlashAttackCollision();
			SetSoundPlayOnce("HollowKnightSlash.wav");
		},
			.Update = [this](float _DeltaTime)
		{


			if (IsLeftWallCheck() == false && ReturnPatternDir() == float4::Left)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash2Speed* _DeltaTime);
			}

			if (IsRightWallCheck() == false && ReturnPatternDir() == float4::Right)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash2Speed* _DeltaTime);
			}

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("EndSlash2");
				return;
			}
		},
			.End = [this]()
		{
			AttackCollision->Off();
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
			SetSlashAttackCollision();
			SetSoundPlayOnce("HollowKnightSlash.wav");
		},
			.Update = [this](float _DeltaTime)
		{
			if (IsLeftWallCheck() == false && ReturnPatternDir() == float4::Left)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir() * Slash3Speed * _DeltaTime);
			}

			if (IsRightWallCheck() == false && ReturnPatternDir() == float4::Right)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir()* Slash3Speed* _DeltaTime);
			}

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("Recover");
				return;
			}
		},
			.End = [this]()
		{
			AttackCollision->Off();
		},

		}
	);

	//Counter

	FSM.CreateState(
		{
			.Name = "AnticCounter",
			.Start = [this]()
		{
			IsCounter = false;
			BossRenderer->ChangeAnimation("AnticCounter");
			SetCollisionValue(HollowKnightCollisionIdleScale, float4{ -90.0f, HollowKnightCollisionIdlePos.y , -70.0f });
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
			SetCounterCollision(true);
			CurrentState = "ReadyCounter";
			//흰색으로 잠깐 반짝거림
			SetCounterFlashEffect();
			CounterTime = 1.0f;
			SetSoundPlayOnce("HollowKnightParryPrepare.wav");

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			//To do : collision 추가 후, 로직 구현

			if (true == CounterAvailability())
			{
				BossNoneDamageState = true;

				FSM.ChangeState("BlockCounter");
				return;
			}

			if (1.0f <= StateCalTime)
			{
				FSM.ChangeState("NoneBlockCounter");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{
			SetCounterCollision(false);
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
			SetIdleCollision();

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "BlockCounter",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("BlockCounter");
			SetSoundPlayOnce("HollowKnightParry.wav");

			GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(0.2f);

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

			SetIdleCollision();
			BossNoneDamageState = false;
		},

		}
	);

	FSM.CreateState(
		{
			.Name = "CounterSlash2",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("Slash2");
			SetSlashAttackCollision();

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (IsLeftWallCheck() == false && ReturnPatternDir() == float4::Left)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir() * CounterSlash2Speed * _DeltaTime);
			}
			if (IsRightWallCheck() == false && ReturnPatternDir() == float4::Right)
			{
				GetTransform()->AddWorldPosition(ReturnPatternDir()* CounterSlash2Speed* _DeltaTime);
			}

			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("EndCounterSlash2");
				return;
			}

			StateCalTime += _DeltaTime;
		},
			.End = [this]()
		{
			AttackCollision->Off();
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
			SetCollisionValue(float4{ 245,325,1 }, float4{ -80.0f, HollowKnightCollisionIdlePos.y , -70.0f });
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
			SmallShotEffectActor->OnEffect();
			StateCalPos = SmallShotEffectActor->GetTransform()->GetWorldPosition();
			SetSoundPlayOnce("HollowKnightLand.wav");

			if (float4::Left == ReturnPatternDir())
			{
				StateCalPos += {50.0f, 0.0f, 0.0f};
				StateCalDir = float4{ -1.5f, -2.5f, 0.0f };
			}
			else
			{
				StateCalPos += {-50.0f, 0.0f, 0.0f};
				StateCalDir = float4{ 1.5f, -2.5f, 0.0f };
			}
			StateCalTime = 0.0f;
			StateCalTime2 = 2.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			float _Value = 15.0f;

			if (1.5f <= StateCalTime)
			{
				SmallShotEffectActor->OffEffect();
				FSM.ChangeState("EndSmallShot");
				return;
			}

			if (StateCalTime2 >= 1.5f / 8)
			{
				if (float4::Left == ReturnPatternDir())
				{
					SetBullet(StateCalDir, StateCalPos, 1600.0f);
					StateCalDir.RotaitonZDeg(-_Value);
					StateCalTime2 = 0.0f;
				}
				else
				{
					SetBullet(StateCalDir, StateCalPos, 1600.0f);
					StateCalDir.RotaitonZDeg(_Value);
					StateCalTime2 = 0.0f;
				}
			}

			StateCalTime += _DeltaTime;
			StateCalTime2 += _DeltaTime;
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
			SetCollisionValue(float4{ 225,300,1 }, float4{ -70.0f, HollowKnightCollisionIdlePos.y , -70.0f });
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
			SetSoundPlayOnce("HollowKnightPrepare2.wav");
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
			SetBlasts();
			SetSlamEffect();
			BossRenderer->ChangeAnimation("LandBlasts");
			SetSoundPlayOnce("HollowKnightBlastLand.wav");
			Player::CurrentLevelPlayer->SetCameraShakeOnce(20.0f);
			StateCalBool = false;

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (StateCalBool == false && 0.45f <= StateCalTime)
			{
				SetSoundPlayOnce("HollowKnightBlastsSound.wav");
				StateCalBool = true;
			}

			if (0.7f <= StateCalTime)
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
			SetCollisionValue(float4{ 245,317,1 }, float4{ 10.0f, HollowKnightCollisionIdlePos.y + 10, -70.0f });

			StateCalPos = GetTransform()->GetWorldPosition();

			PivotPos = { 0 , 268 };
			SetBossRendererPivot();
			StateCalFloat = 0.0f;
			StateCalTime = 0.0f;

			StateCalDir = float4::Null;
		},
			.Update = [this](float _DeltaTime)
		{
			/*float4 Destination = Player::CurrentLevelPlayer->GetTransform()->GetWorldPosition();
			Destination.y = -850.0f;

			if (Destination.XYDistance(GetTransform()->GetWorldPosition()) > 5.0f)
			{
				float4 Destination = Player::CurrentLevelPlayer->GetTransform()->GetWorldPosition();
				Destination.y = -850.0f;

				if (StateCalFloat >= 1.0f)
				{
					StateCalFloat = 1.0f;
				}

				float4 Pos = float4::Lerp(StateCalPos, Destination, StateCalFloat);
				GetTransform()->SetWorldPosition(float4::Lerp(StateCalPos, Destination, StateCalFloat));
			}
			else
			{
				StateCalTime += _DeltaTime;
			}

			if (StateCalTime > 0.25f)
			{
				FSM.ChangeState("DownPuppet");
				return;
			}
			StateCalFloat += (_DeltaTime * 2.5f);*/


			if (GetTransform()->GetWorldPosition().y <= -850.0f)
			{
				GetTransform()->AddWorldPosition(float4::Up * 1000.0f * _DeltaTime);
			}

			float Speed = 3000.0f;
			float Clamp = 1000.0f;

			float4 BossToPlayerDir = Player::CurrentLevelPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (BossToPlayerDir.x < 0.0f && IsLeftWallCheck() == false )
			{
				StateCalDir += float4::Left * Speed * _DeltaTime;
			}
			
			if (BossToPlayerDir.x < 0.0f && IsLeftWallCheck() == true)
			{
				StateCalDir.x = 0.0f;
			}

			if (BossToPlayerDir.x > 0.0f && IsRightWallCheck() == false)
			{
				StateCalDir += float4::Right * Speed * _DeltaTime;
			}
			
			if (BossToPlayerDir.x > 0.0f && IsRightWallCheck() == true)
			{
				StateCalDir.x = 0.0f;
			}

			if (StateCalDir.x >= Clamp)
			{
				StateCalDir.x = Clamp;
			}
			else if (StateCalDir.x <= -Clamp)
			{
				StateCalDir.x = -Clamp;
			}

			GetTransform()->AddWorldPosition(StateCalDir * _DeltaTime);

			if (StateCalTime >= 0.75f)
			{
				FSM.ChangeState("DownPuppet");
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
			.Name = "DownPuppet",
			.Start = [this]()
		{
			BossRenderer->ChangeAnimation("DownPuppet");
			Gravity = 2750.0f;

			SetCollisionValue(float4{ 282,243,1 }, float4{ 0.0f, HollowKnightCollisionIdlePos.y + 120, -70.0f });

			PivotPos = { 0 , 103 };
			SetBossRendererPivot();

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
				float Speed = 3000.0f;
				float Clamp = 1000.0f;

				float4 BossToPlayerDir = Player::CurrentLevelPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

				if (BossToPlayerDir.x < 0.0f && IsLeftWallCheck() == false)
				{
					StateCalDir += float4::Left * Speed * _DeltaTime;
				}

				if (BossToPlayerDir.x < 0.0f && IsLeftWallCheck() == true)
				{
					StateCalDir.x = 0.0f;
				}

				if (BossToPlayerDir.x > 0.0f && IsRightWallCheck() == false)
				{
					StateCalDir += float4::Right * Speed * _DeltaTime;
				}

				if (BossToPlayerDir.x > 0.0f && IsRightWallCheck() == true)
				{
					StateCalDir.x = 0.0f;
				}

				if (StateCalDir.x >= Clamp)
				{
					StateCalDir.x = Clamp;
				}
				else if (StateCalDir.x <= -Clamp)
				{
					StateCalDir.x = -Clamp;
				}

				GetTransform()->AddWorldPosition(StateCalDir * _DeltaTime);
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
			SetSlamEffect();

			PivotPos = { 0 , 150 };
			SetBossRendererPivot();

			Player::CurrentLevelPlayer->SetCameraShakeOnce(25.0f);

			SetRandomPuppetSlamSound();

			StateCalTime = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (StateCalTime >= 0.07f)
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
			SetCollisionValue(float4{ 257,337,1 }, float4{ -10.0f, HollowKnightCollisionIdlePos.y , -70.0f });
			SetSoundPlayOnce("HollowKnightPrepare.wav");
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

			StateCalBool = false;

			SetSoundPlayOnce("HollowKnightScream.wav");
			SetSoundPlayOnce("HollowKnightChestShotSound.wav");

			StateCalTime = 0.0f;
			StateCalTime2 = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			if (StateCalTime <= 0.1f)
			{
				GetTransform()->AddWorldPosition(float4::Up * 2500.0f * _DeltaTime);
			}

			if (StateCalTime >= 0.5f && StateCalBool == false)
			{
				//총알 쏘기 시작
				StateCalBool = true;
				ChestShotEffectActor->OnEffect();
				Player::CurrentLevelPlayer->SetCameraShakeLoop(25.0f);
			}

			if (true == StateCalBool)
			{
				if (StateCalTime2 > 0.3f)
				{
					//총알 발사
					SetRandomBullet();
					SetRandomBullet();
					SetRandomBullet();
					StateCalTime2 = 0.0f;
				}
			}

			if (StateCalTime >= 8.0f)
			{
				Player::CurrentLevelPlayer->SetCameraShakeOff();

				FSM.ChangeState("ChestShotLand");
				return;
			}

			StateCalTime += _DeltaTime;
			StateCalTime2 += _DeltaTime;
		},
			.End = [this]()
		{
			ChestShotEffectActor->OffEffect();
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
			GetTransform()->AddWorldPosition(float4::Down * Gravity * _DeltaTime);

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