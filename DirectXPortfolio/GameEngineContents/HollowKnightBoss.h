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

	void SpriteInit();
	void AnimationInit();

	//RoarEffect����
	float4 RoarEffectPos = float4::Zero;
	void CreateRoarEffect(RoarType _Type, float4 _Pos);

	//�⺻ �̵� ����
	float4 MoveDir = float4::Zero; //�̵� ����
	float Gravity = 1000.0f; //�߷� ũ��
    bool IsGround(float4 _Pos); //���鿡 ����ִ��� ����
	void SetGravity(float _Delta); //�߷� ����

	//
	const float BossHP = 1250.0f;
	float CurrentHp = BossHP;

	GameEngineFSM FSM;
	void StateInit();  //���� �ӽ� ������Ʈ�� init

	// ������Ʈ���� ���Ǵ� ������
	float StateCalTime  = 0.0f;
	float StateCalTime2 = 0.0f;

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

	//SwapPhase


	HollowKnightPatternEnum CurrentPhase = HollowKnightPatternEnum::Phase1; //���� ������ ��ȣ
	bool TurnCheck();
	float4 ReturnPatternDir(); //������ ���⿡ ���� left or right ��ȯ

	float4 ReturnClampBossPos(float4 _Pos); //���� �� �����̵� 

};

