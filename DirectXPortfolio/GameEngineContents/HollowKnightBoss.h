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

	//이동 관련
	float4 MoveDir = float4::Zero; //이동 벡터
	float Gravity = 1000.0f; //중력 크기
    bool IsGround(float4 _Pos); //지면에 닿아있는지 여부
	void SetGravity(float _Delta); //중력 적용

	GameEngineFSM FSM;
	void StateInit();  //상태 머신 스테이트들 init

	// 스테이트에서 사용되는 변수들
	float StateCalTime  = 0.0f;
	float StateCalTime2 = 0.0f;

	//랜덤한 패턴이 나오게끔 구현하기 위한 변수들
	std::map<int, std::vector<int>> BossPatterns;
	void BossPatternInit();
};

