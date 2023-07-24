#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : �÷��̾� hp, mp�� UI�� ����ϴ� �Ŵ���
class GameEngineUIRenderer;
class PlayerUIManager : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerUIManager();
	~PlayerUIManager();

	// delete Function
	PlayerUIManager(const PlayerUIManager& _Other) = delete;
	PlayerUIManager(PlayerUIManager&& _Other) noexcept = delete;
	PlayerUIManager& operator=(const PlayerUIManager& _Other) = delete;
	PlayerUIManager& operator=(PlayerUIManager&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> UIHud;

	int CurrentPlayerHP = 0;
};

