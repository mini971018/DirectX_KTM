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
			PivotPos = { 0 , 270 };
			SetBossRendererPivot();

			BossRenderer->ChangeAnimation("ChainIdle");

			StateCalTime = 0.0f;

		},
			.Update = [this](float _DeltaTime)
		{
			if (GameEngineInput::IsUp("TestButton"))
			{
				FSM.ChangeState("ChainRoar");
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

			float4 EffectPos = GetTransform()->GetWorldPosition();
			EffectPos += {0, 300};

			CreateRoarEffect(RoarType::Black, EffectPos);
			CreateRoarEffect(RoarType::White, EffectPos);

			StateCalTime = 0.0f;
			StateCalTime2 = 0.0f;
		},
			.Update = [this](float _DeltaTime)
		{
			StateCalTime  += _DeltaTime;
			StateCalTime2 += _DeltaTime;

			if (StateCalTime >= 0.5f)
			{
				float4 EffectPos = GetTransform()->GetWorldPosition();
				EffectPos += {0, 300};

				CreateRoarEffect(RoarType::Black, EffectPos);

				StateCalTime = 0.0f;
			}

			if (StateCalTime2 >= 5.0f)
			{
				FSM.ChangeState("BreakChain");
			}

		},
			.End = [this]()
		{

		},

		}
	);

	FSM.CreateState(
		{
			.Name = "ShakeChain",
			.Start = [this]()
		{
			PivotPos = { 0 , 270, -70 };
			SetBossRendererPivot();

			BossRenderer->ChangeAnimation("ShakeChain");

			StateCalTime = 0.0f;

		},
			.Update = [this](float _DeltaTime)
		{
			StateCalTime += _DeltaTime;

			if (true == BossRenderer->IsAnimationEnd())
			{

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
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("BreakChainLand");
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
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRenderer->IsAnimationEnd())
			{
				FSM.ChangeState("ChainIdle");
			}
		},
			.End = [this]()
		{

		},

		}
	);


	FSM.ChangeState("ChainIdle");
}