#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HollowKnightBossRoom : public GameEngineActor
{
public:
	// constrcuter destructer
	HollowKnightBossRoom();
	~HollowKnightBossRoom();

	// delete Function
	HollowKnightBossRoom(const HollowKnightBossRoom& _Other) = delete;
	HollowKnightBossRoom(HollowKnightBossRoom&& _Other) noexcept = delete;
	HollowKnightBossRoom& operator=(const HollowKnightBossRoom& _Other) = delete;
	HollowKnightBossRoom& operator=(HollowKnightBossRoom&& _Other) noexcept = delete;

	void ResetBossRoom();

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer>  MainRoomImage;

	std::shared_ptr<class GameEngineSpriteRenderer> BossRoomDoorRenderer;
	std::shared_ptr<class GameEngineCollision> BossRoomDoorCollision;
	std::shared_ptr<class GameEngineCollision> BossRoomOnCollision;

	bool IsDoorOn = false;

	void CreateMap();
};

