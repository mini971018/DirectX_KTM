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
	Layer2 = CreateComponent<GameEngineRenderer>();
	Layer2->SetPipeLine("2DTexture");

	Layer2->GetShaderResHelper().SetTexture("DiffuseTex", "Layer2.png");
	Layer2->GetTransform()->SetLocalScale({ 5000, 1500 });
	Layer2->GetTransform()->AddLocalPosition({ 1540, 210, 30 });  //원본 크기 기준 z -> -70.0f

	Layer1 = CreateComponent<GameEngineRenderer>();
	Layer1->SetPipeLine("2DTexture");

	Layer1->GetShaderResHelper().SetTexture("DiffuseTex", "Layer1.png");
	Layer1->GetTransform()->SetLocalScale({ 5000, 1500 });
	Layer1->GetTransform()->AddLocalPosition({ 1540, 210, -20 });  //원본 크기 기준 z -> -70.0f

	MainRoomImage = CreateComponent<GameEngineRenderer>();
	MainRoomImage->SetPipeLine("2DTexture");

	MainRoomImage->GetShaderResHelper().SetTexture("DiffuseTex", "HollowKnightBossRoomMain.png");
	MainRoomImage->GetTransform()->SetLocalScale({ 5000, 1500 });
	MainRoomImage->GetTransform()->AddLocalPosition({ 1540, 210, -70 });  

}