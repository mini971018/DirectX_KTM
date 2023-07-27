#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "FadeEffect.h"
#include "MainMenuUIManager.h"
#include "MainMenuUIButton.h"

MainMenuUIManager::MainMenuUIManager() 
{
}

MainMenuUIManager::~MainMenuUIManager() 
{
}

void MainMenuUIManager::Start()
{
	UIButtonVector.reserve(4);

	InitUIButton();
}

void MainMenuUIManager::Update(float _Delta)
{
	if (IsLevelChangeState == false)
	{
		if (true == GameEngineInput::IsDown("MoveDown"))
		{
			int Value = SelectNum - 1;

			SelectNum = ReturnClampNum(Value);
		}

		if (true == GameEngineInput::IsDown("MoveUP"))
		{
			int Value = SelectNum + 1;

			SelectNum = ReturnClampNum(Value);
		}
		if (SelectNum != CurrentSelectNum)
		{
			GameEngineSoundPlayer SoundPlayer = GameEngineSound::Play("UIChange.wav");

			UIButtonVector[SelectNum]->SetSelectState(true);
			UIButtonVector[CurrentSelectNum]->SetSelectState(false);
			CurrentSelectNum = SelectNum;
		}
	}

	if (true == IsLevelChangeState)
	{
		CalStateTime += _Delta;
	}

	if (CalStateTime >= 3.0f)
	{
		GameEngineCore::ChangeLevel("HollowKnightLevel");
	}

	EnterUI();
}

void MainMenuUIManager::InitUIButton()
{
	//시작버튼
	std::shared_ptr<MainMenuUIButton> Button1 = GetLevel()->CreateActor<MainMenuUIButton>();
	Button1->SetButton("GameStart.png");
	Button1->GetTransform()->AddLocalPosition({ -5, -140, -71.0f });
	Button1->GetTransform()->SetLocalScale({ 0.7f, 0.7f, 1.0f });
	UIButtonVector.push_back(Button1);
	Button1->SetSelectState(true);

	//종료 버튼
	std::shared_ptr<MainMenuUIButton> Button2 = GetLevel()->CreateActor<MainMenuUIButton>();
	Button2->SetButton("GameEnd.png");
	Button2->GetTransform()->AddLocalPosition({ -5, -400, -71.0f });
	Button2->GetTransform()->SetLocalScale({ 0.7f, 0.7f, 1.0f });
	UIButtonVector.push_back(Button2);
	Button2->SetSelectState(false);

	ButtonCount = static_cast<int>(UIButtonVector.size());
}	

int MainMenuUIManager::ReturnClampNum(int _Num)
{
	if (_Num < 0)
	{
		return static_cast<int>(ButtonCount) - 1;
	}
	else if (_Num > ButtonCount - 1)
	{
		return 0;
	}
	else
	{
		return _Num;
	}
}

void MainMenuUIManager::EnterUI()
{
	if (GameEngineInput::IsDown("EnterKey"))
	{
		switch (SelectNum)
		{
		case 0:
			IsLevelChangeState = true;
			FEffect->FadeIn();
			BgmPlayer.SoundFadeOut(2.0);
			//페이드아웃 후 다음 레벨로
			break;
		case 1:
			//GameEngineDevice::Release();
			break;
		default:
			break;
		}
	}
}

void MainMenuUIManager::ResetUIManager(std::shared_ptr<class FadeEffect> _FEffect, GameEngineSoundPlayer _BGMPlayer)
{
	FEffect = _FEffect;
	BgmPlayer = _BGMPlayer;

	IsLevelChangeState = false;
	CalStateTime = 0.0f;
}

