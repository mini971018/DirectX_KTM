#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class DustColorType
{
	DustColor1,
	DustColor2,
	DustColor3,
};

// Ό³Έν :
class HitDustEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	HitDustEffect();
	~HitDustEffect();

	// delete Function
	HitDustEffect(const HitDustEffect& _Other) = delete;
	HitDustEffect(HitDustEffect&& _Other) noexcept = delete;
	HitDustEffect& operator=(const HitDustEffect& _Other) = delete;
	HitDustEffect& operator=(HitDustEffect&& _Other) noexcept = delete;

	void SetHitDust(float4 _Dir);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DustEffectRenderer = nullptr;

	const float4 DustColor1 = float4{ static_cast<float>((201.0f * 0.75f) / 255.0f) , static_cast<float>((84.0f * 0.75f) / 255.0f), static_cast<float>((16.0f * 0.75f) / 255.0f) , 0 };
	const float4 DustColor2 = float4{ static_cast<float>((192.0f * 0.75f) / 255.0f) , static_cast<float>((86.0f * 0.75f) / 255.0f), static_cast<float>((34.0f * 0.75f) / 255.0f) , 0 };
	const float4 DustColor3 = float4{ static_cast<float>((213.0f * 0.75f) / 255.0f) , static_cast<float>((107.0f * 0.75f) / 255.0f), static_cast<float>((48.0f * 0.75f) / 255.0f) , 0 };

	float4 Dir = float4::Null;
};

