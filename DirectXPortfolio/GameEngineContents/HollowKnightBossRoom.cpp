#include "PrecompileHeader.h"

#include "HollowKnightBossRoom.h"

#include <GameEngineCore/GameEngineRenderer.h>


HollowKnightBossRoom::HollowKnightBossRoom() 
{
}

HollowKnightBossRoom::~HollowKnightBossRoom() 
{
}

void HollowKnightBossRoom::Start()
{
	MainRoomImage = CreateComponent<GameEngineRenderer>();
	MainRoomImage->SetPipeLine("2DTexture");

	MainRoomImage->GetShaderResHelper().SetTexture("DiffuseTex", "HollowKnightBossRoomMain.png");
	MainRoomImage->GetTransform()->SetLocalScale({ 5000, 1500 });
	MainRoomImage->GetTransform()->AddLocalPosition({ 1540, 210, -70 });  //���� ũ�� ���� z -> -70.0f
}