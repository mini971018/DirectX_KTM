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

	void InitPlayer(std::string_view ColMap);

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	void CreateKey();
	void Test();

	std::shared_ptr<class GameEngineSpriteRenderer> PlayerRenderer;
	std::shared_ptr<class GameEngineComponent> Pivot; //�÷��̾� �������� �Ǻ�
	std::shared_ptr<class GameEngineTexture> PlayerColmapTexture;

	float4 PivotPos = float4::Zero;
	float4 PlayerDir = float4::Right;

	//�̵� ����
	const float MoveSpeed = 400.0f;
	const float JumpForce = 1200.0f;
	float Gravity = 750.0f; //�߷� ũ��
	bool IsGround(float4 _Pos); //���鿡 ����ִ��� ����
	void SetGravity(float _Delta); //�߷� ����

	void SetPlayerRendererPivot();
	
	void SpriteInit();
	void AnimationInit();

	//ī�޶� �̵�
	float CamDeltaTime = 0.0f;
	void CameraMoveLerp();
	void CameraDeltaClamp();

	GameEngineFSM FSM;
	void StateInit();

	//������Ʈ ���� ����ϴ� ����
	float StateCalTime = 0.0f;
	float StateCalFloat = 0.0f;
};

