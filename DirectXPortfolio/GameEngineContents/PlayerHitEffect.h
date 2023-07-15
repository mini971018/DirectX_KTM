#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerHitEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerHitEffect();
	~PlayerHitEffect();

	// delete Function
	PlayerHitEffect(const PlayerHitEffect& _Other) = delete;
	PlayerHitEffect(PlayerHitEffect&& _Other) noexcept = delete;
	PlayerHitEffect& operator=(const PlayerHitEffect& _Other) = delete;
	PlayerHitEffect& operator=(PlayerHitEffect&& _Other) noexcept = delete;

	void SetEnemyHitEffect(float4 _Pos, float4 _Scale, float _Angle);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HitEffectRenderer;
};

