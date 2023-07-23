#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 플레이어 슬래시 이펙트 출력
class SlashEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	SlashEffect();
	~SlashEffect();

	// delete Function
	SlashEffect(const SlashEffect& _Other) = delete;
	SlashEffect(SlashEffect&& _Other) noexcept = delete;
	SlashEffect& operator=(const SlashEffect& _Other) = delete;
	SlashEffect& operator=(SlashEffect&& _Other) noexcept = delete;

	bool GetIsHit()
	{
		return IsHit;
	}

	void SetSlashEffect(PlayerSlashAnimation _SlashType, float4 _Pos, float _Damage);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SlashEffectRenderer;
	std::shared_ptr<class GameEngineCollision> SlashCollision = nullptr;

	const float4 UpperSlashCollisionPos = {0, 110};
	const float4 UpperSlashCollisionScale = {140, 165};
	const float4 DownSlashCollisionPos = {0, 0};
	const float4 DownSlashCollisionScale = {140, 165};
	const float4 SlashCollisionPos = {-87, 62, -70.0f};
	const float4 SlashCollisionScale = {130, 115, 1};

	bool IsHit = false;

	float SlashDamage = 0.0f;
};

