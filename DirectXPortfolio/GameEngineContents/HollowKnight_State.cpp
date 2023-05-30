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
			BossRender->ChangeAnimation("ChainIdle");

			StateCalTime = 0.0f;

		},
			.Update = [this](float _DeltaTime)
		{
			StateCalTime += _DeltaTime;

			if (GameEngineInput::IsUp("TestButton"))
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
			BossRender->ChangeAnimation("BreakChain");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRender->IsAnimationEnd())
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
			BossRender->ChangeAnimation("BreakChainFall");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRender->IsAnimationEnd())
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
			BossRender->ChangeAnimation("BreakChainLand");
		},
			.Update = [this](float _DeltaTime)
		{
			if (true == BossRender->IsAnimationEnd())
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