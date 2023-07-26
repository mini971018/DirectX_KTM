#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "EndingVideo.h"

EndingVideo::EndingVideo() 
{
}

EndingVideo::~EndingVideo() 
{
}

void EndingVideo::Start()
{
	EndingVideoRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Video);
	EndingVideoRenderer->CreateAnimation({ .AnimationName = "EndingVideo", .SpriteName = "EndingVideo", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	EndingVideoRenderer->Off();
}

void EndingVideo::Update(float _Delta)
{
	CalTime += _Delta;

	if (CalTime >= 34.0f)
	{
		GameEngineCore::ChangeLevel("MainMenuLevel");
	}
}

void EndingVideo::StartVideo()
{
	CalTime = 0.0f;

	BgmPlayer = GameEngineSound::Play("Ending.mp3");

	EndingVideoRenderer->ChangeAnimation("EndingVideo");
	EndingVideoRenderer->On();
}