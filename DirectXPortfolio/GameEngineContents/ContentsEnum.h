#pragma once

enum class UIRenderOrder
{
	None,
	Background,
	Title,
};

enum class PlayRenderOrder
{
	None,
	Background,
	Map,
	Boss,
	Player,
	UpperLayer,
	Effect,
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
	Phase4BeforeAttack
};

enum class HollowKnightNoneAttackState
{
	Teleport,
	BackJump,
	Jump,
	Evade,
	AttackReady,
};

enum class HollowKnightAttackState
{
	DashAttack,
	Slash,
	Counter,
	SmallShot,
	Blasts,
	Suicide,
	PuppetSlam,
	ChestShot,

	//후반 약화된 패턴
	Phase4Slash,
	Phase4PuppetSlam,
	Phase4Suicide,
};