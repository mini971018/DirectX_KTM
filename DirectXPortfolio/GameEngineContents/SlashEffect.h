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

	void SetSlashEffect(PlayerSlashAnimation _SlashType, float4 _Pos);

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SlashEffectRenderer;
};

