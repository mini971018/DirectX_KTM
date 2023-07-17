#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

// 설명 : 공허의 기사 보스 스크립트
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
	std::shared_ptr<class GameEngineComponent> Pivot; //보스 렌더러의 피봇

	void ResetBoss(); //보스를 리셋시킴

	float4 PivotPos = float4::Zero; //보스 렌더러의 애니메이션의 각 중심이 될 위치
	void SetBossRendererPivot();
	
	std::shared_ptr<class GameEngineSpriteRenderer> BossWeaponRenderer; 
	std::shared_ptr<class GameEngineTexture> BossColmapTexture;

	//보스 Init
	void SpriteInit();
	void AnimationInit();
	void CollisionInit();

	//Collision 관련
	std::shared_ptr<class GameEngineCollision> HollowKnightCollision = nullptr;
	const float4 HollowKnightCollisionIdleScale = { 175.0f, 290.0f, 1.0f };
	const float4 HollowKnightCollisionIdlePos = { 0.0f, -110.0f , -70.0f };
	void SetIdleCollision();
	void SetCollisionValue(float4 _Scale , float4 _Pos);

	std::shared_ptr<class GameEngineCollision> AttackCollision = nullptr;
	void SetSlashAttackCollision();
	const float4 SlashCollisionScale = { 265,267,1 };
	const float4 SlashCollisionPos = { 260.0f, -110.0f , 0.0f };

	//const float4 HollowKnightCollisionPos = { 0.0f, 65.0f , -70.0f };
	void SetDamagedColor();
	const float4 DamagedColor = float4{ static_cast<float>((201.0f *0.75f) /255.0f) , static_cast<float>((84.0f * 0.75f) /255.0f), static_cast<float>((16.0f * 0.75f) / 255.0f) , 0};

	//RoarEffect관련
	float4 RoarEffectPos = float4::Zero;
	void CreateRoarEffect(RoarType _Type, float4 _Pos);

	//기본 이동 관련
	float4 MoveDir = float4::Zero; //이동 벡터
	float Gravity = 1000.0f; //중력 크기
    bool IsGround(float4 _Pos); //지면에 닿아있는지 여부
	void SetGravity(float _Delta); //중력 적용

	//PVE 관련
	const float BossHP = 1250.0f;
	float CurrentHp = BossHP;
	void GetDamageCheck();
	void GetDamage(float _Damage, PlayerAttackType _Type, float4 _Pos = float4::Null);
	float DamagedTime = 1.0f; //n초에 한번씩만 공격받을 수 있도록
	const float ConstDamagedTime = 0.3f;
	bool DamageReduceState = false;

	GameEngineFSM FSM;
	void StateInit();  //상태 머신 스테이트들 init
	void AttackStateInit();

	// 스테이트에서 사용되는 변수들
	float StateCalTime  = 0.0f;
	float StateCalTime2 = 0.0f;
	bool StateCalBool = false;
	int StateCalInt = 0;
	float4 StateCalPos = float4::Zero;

	// 랜덤한 패턴이 나오게끔 구현하기 위한 변수들
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
	bool CheckRenderRotationValue();   //플레이어와 보스의 위치에 따라 회전이 필요한지 여부 반환
	void RotationRenderPivotY();	   //보스렌더러 피봇을 Y를 기준으로 회전시킴

	//SelfStab
	int StabCount = 3;

	//SwapPhase
	HollowKnightPatternEnum CurrentPhase = HollowKnightPatternEnum::Phase4; //현재 패턴의 번호
	bool IsNextPhase();

	//StageStart
	bool BossStageStart();
	const float StartDistanceX = 600.0f;

	float4 ReturnPatternDir(); //보스의 방향에 따라 left or right 반환
	float4 ReturnClampBossPos(float4 _Pos); //패턴 중 순간이동 
	std::string_view CurrentState = "";

	
};

