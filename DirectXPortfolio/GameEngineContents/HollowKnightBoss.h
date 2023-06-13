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

	//�̵� ����
	float4 MoveDir = float4::Zero; //�̵� ����
	float Gravity = 1000.0f; //�߷� ũ��
    bool IsGround(float4 _Pos); //���鿡 ����ִ��� ����
	void SetGravity(float _Delta); //�߷� ����

	GameEngineFSM FSM;
	void StateInit();  //���� �ӽ� ������Ʈ�� init

	// ������Ʈ���� ���Ǵ� ������
	float StateCalTime  = 0.0f;
	float StateCalTime2 = 0.0f;

	//������ ������ �����Բ� �����ϱ� ���� ������
	std::map<int, std::vector<int>> BossPatterns;
	void BossPatternInit();
};

