#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "BindBreakEffect.h"


BindBreakEffect::BindBreakEffect() 
{
}

BindBreakEffect::~BindBreakEffect() 
{
}

void BindBreakEffect::Start()
{
	BindBreakRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Effect);
	BindBreakRenderer->CreateAnimation({ .AnimationName = "ShieldBreak", .SpriteName = "99.ShieldBreakEffect", .FrameInter = 0.02f, .Loop = false, .ScaleToTexture = true });
	BindBreakRenderer->Off();
}

void BindBreakEffect::Update(float _Delta)
{
	if (nullptr != BindBreakRenderer && BindBreakRenderer->IsUpdate())
	{
		if (true == BindBreakRenderer->IsAnimationEnd())
		{
			BindBreakRenderer->Death();
			BindBreakRenderer = nullptr;
			Death();
		}
	}
}

void BindBreakEffect::SetBindBreakRenderer(float4 _Pos)
{
	BindBreakRenderer->GetTransform()->SetLocalPosition({ _Pos.x, _Pos.y, -72.0f });
	BindBreakRenderer->On();
	BindBreakRenderer->ChangeAnimation("ShieldBreak");
}