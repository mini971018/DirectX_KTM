#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	static std::shared_ptr<Player> CurrentLevelPlayer;
	// ���� ���� ��, ������ ���� �÷��̾ �־� ��.
	static void SetCurrentLevelPlayer(std::shared_ptr<Player> _Player);

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	void CreateKey();
	void Test();

	std::shared_ptr<class GameEngineSpriteRenderer> PlayerRenderer;
	std::shared_ptr<class GameEngineComponent> Pivot; //�÷��̾� �������� �Ǻ�
	float4 PivotPos = float4::Zero;
	void SetPlayerRendererPivot();

	void SpriteInit();
	void AnimationInit();

	//ī�޶� �̵�
	float CamDeltaTime = 0.0f;
	void CameraMoveLerp();
	void CameraDeltaClamp();

	GameEngineFSM FSM;
	void StateInit();
};

