#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

// ���� : ������ ��� ���� ��ũ��Ʈ
class HollowKnightBoss : public GameEngineActor
{
public:
	// constrcuter destructer
	HollowKnightBoss();
	~HollowKnightBoss();

	// delete Function
	HollowKnightBoss(const HollowKnightBoss& _Other) = delete;
	HollowKnightBoss(HollowKnightBoss&& _Other) noexcept = delete;
	HollowKnightBoss& operator=(const HollowKnightBoss& _Other) = delete;
	HollowKnightBoss& operator=(HollowKnightBoss&& _Other) noexcept = delete;



protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void LevelChangeStart() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BossRenderer;
	std::shared_ptr<class GameEngineComponent> Pivot; //���� �������� �Ǻ�

	void ResetBoss(); //������ ���½�Ŵ

	float4 PivotPos = float4::Zero; //���� �������� �ִϸ��̼��� �� �߽��� �� ��ġ
	void SetBossRendererPivot();
	
	std::shared_ptr<class GameEngineSpriteRenderer> BossWeaponRenderer; 
	std::shared_ptr<class GameEngineTexture> BossColmapTexture;

	//���� Init
	void SpriteInit();
	void AnimationInit();
	void CollisionInit();
	void EffectInit();

	//Collision ����
	std::shared_ptr<class GameEngineCollision> HollowKnightCollision = nullptr;
	const float4 HollowKnightCollisionIdleScale = { 175.0f, 290.0f, 1.0f };
	const float4 HollowKnightCollisionIdlePos = { 0.0f, -110.0f , -70.0f };
	void SetIdleCollision();
	void SetCollisionValue(float4 _Scale, float4 _Pos);

	std::shared_ptr<class GameEngineCollision> AttackCollision = nullptr;
	void SetSlashAttackCollision();
	const float4 SlashCollisionScale = { 265,267,1 };
	const float4 SlashCollisionPos = { 260.0f, -110.0f , 0.0f };

	std::shared_ptr<class GameEngineCollision> CounterCollision = nullptr;
	const float4 CounterCollisionScale = { 30,280,1 };
	const float4 CounterCollisionPos = { 30, -110 , 0 };

	std::shared_ptr<class GameEngineCollision> CounterCollision2 = nullptr;
	const float4 CounterCollision2Scale = { 200,280,1 };
	const float4 CounterCollision2Pos = { 150, -110 , 0 };

	void SetCounterCollision(bool _Value);

	//������ �޾��� �� ���� ����
	void SetBossColor();
	const float4 DamagedColor = float4{ static_cast<float>((201.0f *0.75f) /255.0f) , static_cast<float>((84.0f * 0.75f) /255.0f), static_cast<float>((16.0f * 0.75f) / 255.0f) , 0};

	//RoarEffect����
	float4 RoarEffectPos = float4::Zero;
	void CreateRoarEffect(RoarType _Type, float4 _Pos);

	//�⺻ �̵� ����
	float4 MoveDir = float4::Zero; //�̵� ����
	float Gravity = 1000.0f; //�߷� ũ��
    bool IsGround(float4 _Pos); //���鿡 ����ִ��� ����
	void SetGravity(float _Delta); //�߷� ����

	//PVE ����
	const float BossHP = 1250.0f;
	float CurrentHp = BossHP;
	void GetDamageCheck();
	void GetDamage(float _Damage, PlayerAttackType _Type, float4 _Pos = float4::Null);
	float DamagedTime = 1.0f; //n�ʿ� �ѹ����� ���ݹ��� �� �ֵ���
	const float ConstDamagedTime = 0.3f;
	bool DamageReduceState = false;
	bool BossNoneDamageState = false;
	bool IsCounter = false;

	//SlamEffect
	void SetSlamEffect();

	//Blasts ����
	void SetBlasts();
	const float MinBlastsPosX = 1475.0f + 100.0f;
	const float MaxBlastsPosX = 4550.0f - 100.0f;
	
	//Shot ����
	void SetBullet(float4 _Dir, float4 _Pos, float _Force);
	void SetRandomBullet();
	std::shared_ptr<class HollowKnightSmallShotEffect> SmallShotEffectActor = nullptr;
	std::shared_ptr<class ChestShotEffect> ChestShotEffectActor = nullptr;

	GameEngineFSM FSM;
	void StateInit();  //���� �ӽ� ������Ʈ�� init
	void AttackStateInit();

	//HitEffect
	void HollowKnightHitEffect();
	void SetHitEffect(float4 _Dir);

	// ������Ʈ���� ���Ǵ� ������
	float StateCalFloat = 0.0f;
	float StateCalTime  = 0.0f;
	float StateCalTime2 = 0.0f;
	bool StateCalBool = false;
	int StateCalInt = 0;
	float4 StateCalPos = float4::Zero;
	float4 StateCalDir = float4::Zero;

	// ������ ������ �����Բ� �����ϱ� ���� ������
	std::map<short, std::vector<short>> BossPatterns;
	void BossPatternInit();

	void SetRandomPattern();
	void SetRandomAttackPattern();
	
	// Dash Attack 
	const float DashSpeed = 2500.0f;
	float CurrentDashSpeed = DashSpeed;

	// Slash Attack
	const float Slash1Speed = 2500.0f;
	const float Slash2Speed = 1100.0f;
	const float Slash3Speed = 900.0f;

	//Counter
	bool CounterAvailability();
	const float CounterSlash2Speed = 4000.0f;
	void SetCounterFlashEffect();
	float CounterTime = 0.0f;
	const float4 CounterColor = float4{ 1, 1, 1 , 0 };

	//Teleport
	const float MinTeleportDistance = 150.0f;
	const float MaxTeleportDistance = 500.0f;
	void SetRandomTeleportPos();

	//Jump
	const float MaxJumpForceX = 1000.0f;
	const float MinJumpForceX = 500.0f;
	const float JumpForce = 4000.0f;

	//Evade
	const float EvadeSpeed = 3000.0f;

	//Turn
	bool CheckRenderRotationValue();   //�÷��̾�� ������ ��ġ�� ���� ȸ���� �ʿ����� ���� ��ȯ
	void RotationRenderPivotY();	   //���������� �Ǻ��� Y�� �������� ȸ����Ŵ

	//SelfStab
	int StabCount = 3;
	void SetStabEffect();

	//SwapPhase
	HollowKnightPatternEnum CurrentPhase = HollowKnightPatternEnum::Phase4; //���� ������ ��ȣ
	bool IsNextPhase();

	//StageStart
	bool BossStageStart();
	const float StartDistanceX = 600.0f;

	float4 ReturnPatternDir(); //������ ���⿡ ���� left or right ��ȯ
	float4 ReturnClampBossPos(float4 _Pos); //���� �� �����̵� 
	std::string_view CurrentState = "";

	
};

