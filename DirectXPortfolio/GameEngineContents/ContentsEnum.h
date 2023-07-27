#pragma once

enum class UIRenderOrder
{
	None,
	Background,
	Button,
	Title,
};

enum class PlayRenderOrder
{
	None,
	Background,
	Map,
	//SkillEffect,
	BBPB_Effect,
	Boss,
	BFPB_Effect,
	Player,
	BFPF_Effect,
	UpperLayer,
	UpperEffect,
	Video,
};

enum class OrangeBlobType
{
	LargeBlob01,
	LargeBlob02,
	LargeBlob03,
	SmallBlob01,
	SmallBlob02,
	SmallBlob03
};

enum class RoarType
{
	Black,
	White
};

enum class HollowKnightPatternEnum 
{
	Phase1,
	Phase2,
	Phase3,
	Phase4,
	BeforeAttack,
};

enum class HollowKnightNoneAttackState
{
	Teleport,
	Jump,
	Evade,
	AttackReady,
	SelfStab,
};

enum class HollowKnightAttackState
{
	DashAttack,
	Slash,
	Counter,
	SmallShot,
	Blasts,
	PuppetSlam,
	ChestShot,

	Phase4Suicide,

	None,
};

enum class PlayerState
{
	Idle,
	Sprint,
	Jump,
	Fall,
	Slash,
	Dash,
};

enum class PlayerSlashAnimation
{
	Slash1,
	Slash2,
	UpperSlash,
	DownSlash,
};

enum class HollowKnightCollisionType
{
	Player,
	Boss,
	BossAttack,
	BossHardAttack,
	PlayerAttack,
	PlayerSkill,
	CounterCheck,
	OnBossRoomDoor,
	WallCheck,
	Wall,
};

enum class PlayerAttackType
{
	Slash,
	Skill,
	SelfStab,
	CounterCheck,
};

enum class CameraClampType
{
	HollowKnightBossRoom,
	HollowKnightInBoss,
};

enum class HealthUIType
{
	Idle,
	Break,
};
