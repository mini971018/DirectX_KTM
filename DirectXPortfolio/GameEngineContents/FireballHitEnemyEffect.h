#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FireballHitEnemyEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	FireballHitEnemyEffect();
	~FireballHitEnemyEffect();

	// delete Function
	FireballHitEnemyEffect(const FireballHitEnemyEffect& _Other) = delete;
	FireballHitEnemyEffect(FireballHitEnemyEffect&& _Other) noexcept = delete;
	FireballHitEnemyEffect& operator=(const FireballHitEnemyEffect& _Other) = delete;
	FireballHitEnemyEffect& operator=(FireballHitEnemyEffect&& _Other) noexcept = delete;

	void SetFireballHitEffect(float4 _Pos, float4 _Scale);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HitEnemyEffect;
};

