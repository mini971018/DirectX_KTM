#include "PrecompileHeader.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Player.h"

void Player::StateInit()
{
	FSM.CreateState(
		{
			.Name = "Idle",
			.Start = [this]()
		{
			PlayerRenderer->ChangeAnimation("Idle");

			PivotPos = { 0, 90.0f };
			SetPlayerRendererPivot();
		},
			.Update = [this](float _DeltaTime)
		{

		},
			.End = [this]()
		{

		},

		}
	);

	FSM.ChangeState("Idle");
}