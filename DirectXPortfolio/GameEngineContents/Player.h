#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEnginePlatform/GameEngineSound.h>

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
	// 레벨 변경 시, 레벨의 메인 플레이어를 넣어 줌.
	static void SetCurrentLevelPlayer(std::shared_ptr<Player> _Player);

	int GetPlayerMaxHp()
	{
		return PlayerMaxHP;
	}

	int GetCurrentPlayerHP()
	{
		return CurrentPlayerHP;
	}

	int GetCurrentPlayerMP()
	{
		return CurrentPlayerMP;
	}

	void PlayerDrainMana()
	{
		CurrentPlayerMP += 10;

		if (CurrentPlayerMP > PlayerMaxMP)
		{
			CurrentPlayerMP = PlayerMaxMP;
		}
	}

	void SetCameraShakeOnce(float _Force);
	void SetCameraShakeOff();
	void SetCameraShakeLoop(float _Force);
	void SetCameraShakeValue(float _Value, float _Force)
	{
		CameraShakeTime = _Value;
		CameraShakeForce = _Force;
	}

	void InitPlayer(std::string_view ColMap, CameraClampType _ClampType);
	void SetPlayerCanMoveState(bool _State)
	{
		CanMoveState = _State;
	}
	void OnRoarLockState(float4 _PlayerDir);
	void OffRoarLockState();

	float GetPlayerDamage()
	{
		return PlayerDamage;
	}

	float GetPlayerSkillDamage()
	{
		return PlayerSkillDamage;
	}

	float4 GetPlayerCollisionPos();

	void SetFireballHitEffect(float4 _Pos, float4 _Scale);
	void SetEnemyHitSlashEffect(float4 _Pos, float4 _Scale);
	void SetEnemyHitEffect(float4 _Pos, float4 _Scale);
	void ResetPlayer();

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	void CreateKey();
	void Test();

	std::shared_ptr<class GameEngineSpriteRenderer> PlayerRenderer;
	std::shared_ptr<class GameEngineComponent> Pivot; //플레이어 렌더러의 피봇
	std::shared_ptr<class GameEngineTexture> PlayerColmapTexture;

	float4 PivotPos = float4::Zero;
	float4 PlayerDir = float4::Right;

	void SetPlayerRendererPivot();

	//UI
	std::shared_ptr<class PlayerUIManager> PlayerUIManagerActor = nullptr;

	//전투 관련
	const int PlayerMaxHP = 7;
	int CurrentPlayerHP = PlayerMaxHP;

	const int PlayerMaxMP = 100;
	int CurrentPlayerMP = 0;

	const float PlayerDamage = 13.0f;
	const float PlayerSkillDamage = 20.0f;

	float PlayerDamagedTime = 0.0f;
	const float PlayerConstDamagedTime = 1.5f; //n초에 한번씩만 공격받음

	void PlayerGetDamagedCheck();
	void PlayerGetDamage(int _Damage, float4 _Dir);
	void PlayerGetHealed();

	//이동 관련
	const float MoveSpeed = 400.0f;
	const float DashSpeed = 1100.0f;
	const float JumpForce = 950.0f;
	const float MaxGravity = 1050.0f;

	float Gravity = 450.0f; //중력 크기
	bool IsGround(float4 _Pos); //지면에 닿아있는지 여부
	void SetGravity(float _Delta); //중력 적용

	bool CanMoveState = true;

	//대쉬 관련
	bool Dashable = true; //대쉬가 가능한지
	bool ShadowDashable = true;;
	const float ShadowDashCooltime = 1.5f;
	float ShadowDashCalTime = ShadowDashCooltime;
	void SetStateAbleValue();
	void SetDashState();
	void ResetShadowDashValue();
	bool ShadowDashEffectIsOn = false;

	//공격 애니메이션 처리
	void CalSlashAnimation();
	PlayerSlashAnimation CalAttackAnimation();
	PlayerSlashAnimation CurrentSlash = PlayerSlashAnimation::Slash1;
	float SlashCalTime = 1.0f;

	//Skill 관련
	float SkillCalTime = 0.0f;
	void SetFireBall();
	void SetFireBallCastEffect();
	void SetShadowDashEffect();
	bool SkillStateCheck(int cost);

	const int SkillCost = 33;
	const int HealingCost = 30;

	//이펙트 관련
	std::shared_ptr<class ShadowDashRechargedEffect> ShadowDashRechargedEffectActor = nullptr;
	std::shared_ptr<class FocusEffect> FocusEffectActor = nullptr;
	std::shared_ptr<class DoubleJumpEffect> JumpEffectActor = nullptr;
	std::shared_ptr<class SlashEffect> SlashEffectActor = nullptr;
	std::shared_ptr<class DashEffect> DashEffectActor = nullptr;

	const float4 NormalSlashPos = { -30, 70 };
	const float4 UpperSlashPos = { 0, 100 };
	const float4 DownSlashPos = { 0, 0 };

	void SetScreamSkillEffect();
	void SetHealingEffect();
	void SetGetDamagedEffect();

	void SetPlayerColor(float _Delta);
	const float4 PlayerDamagedColor = { 0, 0, 0, 0 };

	float DamagedColorAlpha = 0.0f;
	float DamagedColorValue = 1.0f;

	//Collision관련
	std::shared_ptr<class GameEngineCollision> PlayerCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> LeftWallCheck = nullptr;
	std::shared_ptr<class GameEngineCollision> RightWallCheck = nullptr;
	std::shared_ptr<class GameEngineCollision> UpperWallCheck = nullptr;
	
	bool IsLeftWallCheck();
	bool IsRightWallCheck();
	bool IsUpperWallCheck();

	const float4 PlayerCollisionPos = { 0.0f, 65.0f , -70.0f };

	void SetPlayerCollisionPos(float _Value = 0.0f);

	//점프 관련
	bool DoubleJumpable = true;

	void ResetFallValue();

	//플레이어 Init
	void SpriteInit();
	void StateInit();
	void AttackStateInit();
	void AnimationInit();
	void EffectInit();
	void CollisionInit();
	void UIInit();
	//void LoopSoundInit();

	//카메라 관련
	float CamDeltaTime = 0.0f;
	void CameraMoveLerp(float _Delta);

	void SetIsCameraShake();

	bool IsCameraShake = false;
	float CameraShakeForce = 20.0f;
	float CameraShakeTime = 0.0f;
	float4 CamTarget = float4::Null;
	std::shared_ptr<class GameEngineTransform> CamTargetTransform = nullptr;

	float4 SetCameraTarget(float4 _Pos);
	float4 SetCameraClamp(float4 _Pos);
	float4 SetCameraShake(float4 _Pos);

	CameraClampType ClampType = CameraClampType::HollowKnightBossRoom;

	//스테이트 관련
	GameEngineFSM FSM;
	PlayerState CurrentState = PlayerState::Idle;

	//스테이트 에서 사용하는 변수
	float StateCalTime = 0.0f;
	float StateCalFloat = 0.0f;
	int StateCalCount = 0;
	float4 StateCalDir = float4::Null;

	GameEngineSoundPlayer SprintSoundPlayer;
	GameEngineSoundPlayer HealingFocusSound;
};

