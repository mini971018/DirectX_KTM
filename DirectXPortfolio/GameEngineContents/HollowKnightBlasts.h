#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HollowKnightBlasts : public GameEngineActor
{
public:
	// constrcuter destructer
	HollowKnightBlasts();
	~HollowKnightBlasts();

	// delete Function
	HollowKnightBlasts(const HollowKnightBlasts& _Other) = delete;
	HollowKnightBlasts(HollowKnightBlasts&& _Other) noexcept = delete;
	HollowKnightBlasts& operator=(const HollowKnightBlasts& _Other) = delete;
	HollowKnightBlasts& operator=(HollowKnightBlasts&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer>  BlastsRenderer;
	std::shared_ptr<class GameEngineCollision> BlastsCollision = nullptr;

	bool IsBlasts = false;
};

