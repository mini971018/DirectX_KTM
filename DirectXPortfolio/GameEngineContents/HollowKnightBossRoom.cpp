#include "PrecompileHeader.h"

#include "HollowKnightBossRoom.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "ContentsEnum.h"

HollowKnightBossRoom::HollowKnightBossRoom() 
{
}

HollowKnightBossRoom::~HollowKnightBossRoom() 
{
}

void HollowKnightBossRoom::Start()
{
	//{
	//std::shared_ptr<class GameEngineRenderer> Pillar1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
	//Pillar1->SetPipeLine("2DTexture");

	//Pillar1->GetShaderResHelper().SetTexture("DiffuseTex", "Layer1.png");
	//Pillar1->GetTransform()->SetLocalScale({ 5000, 1500 });
	//Pillar1->GetTransform()->AddLocalPosition({ 1540, 210, -20 });


	//std::shared_ptr<class GameEngineRenderer> Pillar2 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
	//Pillar2->SetPipeLine("2DTexture");

	//Pillar2->GetShaderResHelper().SetTexture("DiffuseTex", "Layer2.png");
	//Pillar2->GetTransform()->SetLocalScale({ 5000, 1500 });
	//Pillar2->GetTransform()->AddLocalPosition({ 1540, 210, 30 });
	//}



	CreateMap();
}

void HollowKnightBossRoom::CreateMap()
{
	//Chain
	{
		std::shared_ptr<class GameEngineRenderer> Chain1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain1->SetPipeLine("2DTexture");

		Chain1->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain1->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain1->GetTransform()->SetWorldPosition({ -690, -174, -40 });
		Chain1->GetTransform()->SetWorldRotation({ 0, 0, 30 });

		std::shared_ptr<class GameEngineRenderer> Chain2 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain2->SetPipeLine("2DTexture");

		Chain2->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain2->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain2->GetTransform()->SetWorldPosition({ 1260, -174, -40 });
		Chain2->GetTransform()->SetWorldRotation({ 0, 0, -20 });
	}

	//BG
	{
		std::shared_ptr<class GameEngineRenderer> BG5 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG5->SetPipeLine("2DTexture");

		BG5->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG5->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG5->GetTransform()->SetWorldPosition({ 500, -52, 350 });

		std::shared_ptr<class GameEngineRenderer> BG3 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG3->SetPipeLine("2DTexture");

		BG3->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG3->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG3->GetTransform()->SetWorldPosition({ -122, -52, 350 });


		std::shared_ptr<class GameEngineRenderer> BG4 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG4->SetPipeLine("2DTexture");

		BG4->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG4->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG4->GetTransform()->SetWorldPosition({ 1200, -52, 350 });


		std::shared_ptr<class GameEngineRenderer> BG1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG1->SetPipeLine("2DTexture");

		BG1->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG1->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG1->GetTransform()->SetWorldPosition({ -622, -52, 180 });


		std::shared_ptr<class GameEngineRenderer> BG2 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG2->SetPipeLine("2DTexture");

		BG2->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG2->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG2->GetTransform()->SetWorldPosition({ 1700, -52, 180 });
	}

	// 기둥
	{
		std::shared_ptr<class GameEngineRenderer> Pillar1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Pillar1->SetPipeLine("2DTexture");

		Pillar1->GetShaderResHelper().SetTexture("DiffuseTex", "Pillar.png");
		Pillar1->GetTransform()->SetLocalScale({ -902, 1140 });
		Pillar1->GetTransform()->SetWorldPosition({ 1971, -100, 30 });



		std::shared_ptr<class GameEngineRenderer> Pillar2 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Pillar2->SetPipeLine("2DTexture");

		Pillar2->GetShaderResHelper().SetTexture("DiffuseTex", "Pillar.png");
		Pillar2->GetTransform()->SetLocalScale({ 902, 1140 });
		Pillar2->GetTransform()->SetWorldPosition({ -836, -94, 30 });
	}

	//천막
	{
		std::shared_ptr<class GameEngineRenderer> Rag1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag1->SetPipeLine("2DTexture");

		Rag1->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag1->GetTransform()->SetLocalScale({ 169, 340 });
		Rag1->GetTransform()->SetWorldPosition({ -701, 200, -20 });
		Rag1->GetTransform()->AddLocalScale({ 0,30 });

		std::shared_ptr<class GameEngineRenderer> Rag2 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag2->SetPipeLine("2DTexture");

		Rag2->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag2->GetTransform()->SetLocalScale({ 169, 340 });
		Rag2->GetTransform()->SetWorldPosition({ -480, 270, -20 });

		std::shared_ptr<class GameEngineRenderer> Rag3 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag3->SetPipeLine("2DTexture");

		Rag3->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag3->GetTransform()->SetLocalScale({ 169, 340 });
		Rag3->GetTransform()->SetWorldPosition({ -300, 360, -20 });

		std::shared_ptr<class GameEngineRenderer> Rag4 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag4->SetPipeLine("2DTexture");

		Rag4->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag4->GetTransform()->SetLocalScale({ 169, 340 });
		Rag4->GetTransform()->SetWorldPosition({ 1500, 330, -20 });

		std::shared_ptr<class GameEngineRenderer> Rag5 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag5->SetPipeLine("2DTexture");

		Rag5->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag5->GetTransform()->SetLocalScale({ 169, 340 });
		Rag5->GetTransform()->AddLocalScale({ 0,60 });
		Rag5->GetTransform()->SetWorldPosition({ 1669, 230, -20 });

		std::shared_ptr<class GameEngineRenderer> Rag6 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag6->SetPipeLine("2DTexture");

		Rag6->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag6->GetTransform()->SetLocalScale({ 169, 340 });
		Rag6->GetTransform()->AddLocalScale({ 0,100 });
		Rag6->GetTransform()->SetWorldPosition({ 1838, 130, -20 });
	}

	MainRoomImage = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Map);
	MainRoomImage->SetPipeLine("2DTexture");

	MainRoomImage->GetShaderResHelper().SetTexture("DiffuseTex", "HollowKnightBossRoomMain.png");
	MainRoomImage->GetTransform()->SetLocalScale({ 5000, 1500 });
	MainRoomImage->GetTransform()->SetLocalPosition({ 0, 0, -70 }); //원본 크기 기준 z -> -70.0f

}

void HollowKnightBossRoom::Update(float _Delta)
{

}