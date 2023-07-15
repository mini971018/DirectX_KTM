#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerHitSlashEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerHitSlashEffect();
	~PlayerHitSlashEffect();

	// delete Function
	PlayerHitSlashEffect(const PlayerHitSlashEffect& _Other) = delete;
	PlayerHitSlashEffect(PlayerHitSlashEffect&& _Other) noexcept = delete;
	PlayerHitSlashEffect& operator=(const PlayerHitSlashEffect& _Other) = delete;
	PlayerHitSlashEffect& operator=(PlayerHitSlashEffect&& _Other) noexcept = delete;

	void SetEnemyHitSlashEffect(float4 _Pos, float4 _Scale, PlayerSlashAnimation _Type);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HitSlashEffectRenderer;

};

