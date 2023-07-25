#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 플레이어 hp, mp등 UI를 출력하는 매니저
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

	void SetUIManager(int _PlayerHP, int _PlayerMaxMP, int _PlayerCurrentMP);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> UIHud;
	std::vector<std::shared_ptr<class PlayerHPUI>> HPUIVector;
	std::shared_ptr<GameEngineUIRenderer> MPUIRenderer;

	float4 HPUIStartPos = { 55, 15, 0 };
	const float HPUIInterval = 60.0f;

	int PlayerMaxHP = 0;
	int CurrentPlayerHP = 0;

	int PlayerMaxMP = 0;
	int CurrentPlayerMP = 0;
};

