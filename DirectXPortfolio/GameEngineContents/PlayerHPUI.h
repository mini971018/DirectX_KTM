#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
class PlayerHPUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerHPUI();
	~PlayerHPUI();

	// delete Function
	PlayerHPUI(const PlayerHPUI& _Other) = delete;
	PlayerHPUI(PlayerHPUI&& _Other) noexcept = delete;
	PlayerHPUI& operator=(const PlayerHPUI& _Other) = delete;
	PlayerHPUI& operator=(PlayerHPUI&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> HPUIRenderer;
};

