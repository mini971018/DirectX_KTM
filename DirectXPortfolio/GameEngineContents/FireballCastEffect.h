#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 플레이어 스킬 발사 이펙트
class FireballCastEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	FireballCastEffect();
	~FireballCastEffect();

	// delete Function
	FireballCastEffect(const FireballCastEffect& _Other) = delete;
	FireballCastEffect(FireballCastEffect&& _Other) noexcept = delete;
	FireballCastEffect& operator=(const FireballCastEffect& _Other) = delete;
	FireballCastEffect& operator=(FireballCastEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> CastEffect;
};

