#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class EndingVideo : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingVideo();
	~EndingVideo();

	// delete Function
	EndingVideo(const EndingVideo& _Other) = delete;
	EndingVideo(EndingVideo&& _Other) noexcept = delete;
	EndingVideo& operator=(const EndingVideo& _Other) = delete;
	EndingVideo& operator=(EndingVideo&& _Other) noexcept = delete;

	void StartVideo();

protected:
	void Start();
	void Update(float _Delta) override;

private:
	float CalTime = 0.0f;

	GameEngineSoundPlayer BgmPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> EndingVideoRenderer;
};

