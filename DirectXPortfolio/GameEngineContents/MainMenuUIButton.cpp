#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "MainMenuUIButton.h"


MainMenuUIButton::MainMenuUIButton() 
{

}

MainMenuUIButton::~MainMenuUIButton() 
{

}

void MainMenuUIButton::Start()
{
	LeftArrowRenderer = CreateComponent<GameEngineUIRenderer>();
	LeftArrowRenderer->CreateAnimation({ .AnimationName = "UISelect", .SpriteName = "UISelect", .FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });
	LeftArrowRenderer->CreateAnimation({ .AnimationName = "UIUnSelect", .SpriteName = "UIUnSelect", .FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });

	LeftArrowRenderer->ChangeAnimation("UISelect");
	LeftArrowRenderer->GetTransform()->SetLocalPosition({ -160.0f, 5.0f, 0.0f });
	LeftArrowRenderer->Off();

	LeftArrowRenderer->GetTransform()->SetLocalRotation({ 0, 180, 0 });

	RightArrowRenderer = CreateComponent<GameEngineUIRenderer>();
	RightArrowRenderer->CreateAnimation({ .AnimationName = "UISelect", .SpriteName = "UISelect", .FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });
	RightArrowRenderer->CreateAnimation({ .AnimationName = "UIUnSelect", .SpriteName = "UIUnSelect", .FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });

	RightArrowRenderer->GetTransform()->SetLocalPosition({ 160.0f, 5.0f, 0.0f });
	RightArrowRenderer->ChangeAnimation("UISelect");
	RightArrowRenderer->Off();

	ButtonRenderer = CreateComponent<GameEngineUIRenderer>();
}

void MainMenuUIButton::Update(float _Delta)
{
	if (false == SelectState && true == LeftArrowRenderer->IsAnimationEnd())
	{
		LeftArrowRenderer->Off();
		RightArrowRenderer->Off();
	}
}

void MainMenuUIButton::SetButton(std::string_view _Name)
{
	ButtonRenderer->SetScaleToTexture(_Name);
}

void MainMenuUIButton::SetSelectState(bool _IsSelect)
{
	if (true == _IsSelect)
	{
		LeftArrowRenderer->ChangeAnimation("UISelect");
		RightArrowRenderer->ChangeAnimation("UISelect");

		LeftArrowRenderer->On();
		RightArrowRenderer->On();
	}
	else
	{
		LeftArrowRenderer->ChangeAnimation("UIUnSelect");
		RightArrowRenderer->ChangeAnimation("UIUnSelect");
	}

	SelectState = _IsSelect;
}