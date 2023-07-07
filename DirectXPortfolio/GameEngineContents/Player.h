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
	const float DashSpeed = 1100.0f;
	const float JumpForce = 850.0f;
	
	float Gravity = 450.0f; //�߷� ũ��
	bool IsGround(float4 _Pos); //���鿡 ����ִ��� ����
	void SetGravity(float _Delta); //�߷� ����
	
	//�뽬 ����
	bool Dashable = true; //�뽬�� ��������
	bool ShadowDashable = true;;
	const float ShadowDashCooltime = 1.5f;
	float ShadowDashCalTime = ShadowDashCooltime;
	void SetStateAbleValue();
	void SetDashState();
	void ResetShadowDashValue();
	bool ShadowDashEffectIsOn = false;

	//Skill ����
	float SkillCalTime = 0.0f;


	//���� ����
	bool DoubleJumpable = true;

	void ResetFallValue();

	void SetPlayerRendererPivot();
	
	void SpriteInit();
	void StateInit();
	void AttackStateInit();
	void AnimationInit();
	void EffectInit();

	//ī�޶� �̵�
	float CamDeltaTime = 0.0f;
	void CameraMoveLerp();
	void CameraDeltaClamp();

	GameEngineFSM FSM;
	PlayerState CurrentState = PlayerState::Idle;

	//������Ʈ ���� ����ϴ� ����
	float StateCalTime = 0.0f;
	float StateCalFloat = 0.0f;
	int StateCalCount = 0;

	//���� �ִϸ��̼� ó��
	void CalSlashAnimation();
	PlayerSlashAnimation CalAttackAnimation();
	PlayerSlashAnimation CurrentSlash = PlayerSlashAnimation::Slash1;
	float SlashCalTime = 1.0f;

	//����Ʈ ����
	std::shared_ptr<class ShadowDashRechargedEffect> ShadowDashRechargedEffectActor = nullptr;

	void SetScreamSkillEffect();

};

