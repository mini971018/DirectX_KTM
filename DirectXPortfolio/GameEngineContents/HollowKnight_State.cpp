#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>

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
			StateCalTime += _DeltaTime;

			if (GameEngineInput::IsUp("TestButton"))
			{
				FSM.ChangeState("ShakeChain");
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