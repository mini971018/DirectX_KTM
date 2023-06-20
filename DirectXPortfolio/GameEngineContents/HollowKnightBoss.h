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

	void SpriteInit();
	void AnimationInit();

	//RoarEffect관련
	float4 RoarEffectPos = float4::Zero;
	void CreateRoarEffect(RoarType _Type, float4 _Pos);

	//기본 이동 관련
	float4 MoveDir = float4::Zero; //이동 벡터
	float Gravity = 1000.0f; //중력 크기
    bool IsGround(float4 _Pos); //지면에 닿아있는지 여부
	void SetGravity(float _Delta); //중력 적용

	//
	const float BossHP = 1250.0f;
	float CurrentHp = BossHP;

	GameEngineFSM FSM;
	void StateInit();  //상태 머신 스테이트들 init

	// 스테이트에서 사용되는 변수들
	float StateCalTime  = 0.0f;
	float StateCalTime2 = 0.0f;

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

	//SwapPhase


	HollowKnightPatternEnum CurrentPhase = HollowKnightPatternEnum::Phase1; //현재 패턴의 번호
	bool TurnCheck();
	float4 ReturnPatternDir(); //보스의 방향에 따라 left or right 반환

	float4 ReturnClampBossPos(float4 _Pos); //패턴 중 순간이동 

};

