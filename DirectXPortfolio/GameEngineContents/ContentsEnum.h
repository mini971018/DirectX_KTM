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
	Test,
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