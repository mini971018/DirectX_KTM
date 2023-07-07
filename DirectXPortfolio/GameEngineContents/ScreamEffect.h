#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : �÷��̾� ��ũ�� ��ų ����Ʈ
class ScreamEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ScreamEffect();
	~ScreamEffect();

	// delete Function
	ScreamEffect(const ScreamEffect& _Other) = delete;
	ScreamEffect(ScreamEffect&& _Other) noexcept = delete;
	ScreamEffect& operator=(const ScreamEffect& _Other) = delete;
	ScreamEffect& operator=(ScreamEffect&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ScreamEffectRenderer;

};

