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

		std::shared_ptr<class GameEngineRenderer> Chain3 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain3->SetPipeLine("2DTexture");

		Chain3->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain3->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain3->GetTransform()->SetWorldPosition({ 0, -135, 20 });
		Chain3->GetTransform()->SetWorldRotation({ 0, 0, -30 });

		std::shared_ptr<class GameEngineRenderer> Chain4 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain4->SetPipeLine("2DTexture");

		Chain4->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain4->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain4->GetTransform()->SetWorldPosition({ -322, -256, 30 });
		Chain4->GetTransform()->SetWorldRotation({ 0, 0, 40 });

		std::shared_ptr<class GameEngineRenderer> Chain5 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain5->SetPipeLine("2DTexture");

		Chain5->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain5->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain5->GetTransform()->SetWorldPosition({ 1585, -292, 30 });
		Chain5->GetTransform()->SetWorldRotation({ 0, 0, -30 });


		//블러 추가
		std::shared_ptr<class GameEngineRenderer> Chain6 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain6->SetPipeLine("2DTexture");

		Chain6->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain6->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain6->GetTransform()->SetWorldPosition({ 156, -156, 250 });
		Chain6->GetTransform()->SetWorldRotation({ 0, 0, -15 });

		std::shared_ptr<class GameEngineRenderer> Chain7 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain7->SetPipeLine("2DTexture");

		Chain7->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain7->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain7->GetTransform()->SetWorldPosition({ 756, -156, 250 });
		Chain7->GetTransform()->SetWorldRotation({ 0, 0, 15 });

		std::shared_ptr<class GameEngineRenderer> Chain8 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain8->SetPipeLine("2DTexture");

		Chain8->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain8->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain8->GetTransform()->SetWorldPosition({ -156, -156, 350 });
		Chain8->GetTransform()->SetWorldRotation({ 0, 0, -15 });

		std::shared_ptr<class GameEngineRenderer> Chain9 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain9->SetPipeLine("2DTexture");

		Chain9->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain9->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain9->GetTransform()->SetWorldPosition({ 556, -156, 350 });
		Chain9->GetTransform()->SetWorldRotation({ 0, 0, 15 });


		std::shared_ptr<class GameEngineRenderer> Chain10 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Chain10->SetPipeLine("2DTexture");

		Chain10->GetShaderResHelper().SetTexture("DiffuseTex", "Chain.png");
		Chain10->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain10->GetTransform()->SetWorldPosition({ 1174, -124, 400 });
		Chain10->GetTransform()->SetWorldRotation({ 0, 0, 20 });

	}

	//BG
	{
		//블러 추가
		std::shared_ptr<class GameEngineRenderer> BG5 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG5->SetPipeLine("2DTexture");

		BG5->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG5->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG5->GetTransform()->SetWorldPosition({ 300, -52, 750 });

		std::shared_ptr<class GameEngineRenderer> BG6 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG6->SetPipeLine("2DTexture");

		BG6->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG6->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG6->GetTransform()->SetWorldPosition({ 750, -52, 650 });


		std::shared_ptr<class GameEngineRenderer> BG3 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);  
		BG3->SetPipeLine("2DTexture");

		BG3->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG3->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG3->GetTransform()->SetWorldPosition({ -122, -52, 550 });


		std::shared_ptr<class GameEngineRenderer> BG4 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG4->SetPipeLine("2DTexture");

		BG4->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG4->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG4->GetTransform()->SetWorldPosition({ 1300, -52, 550 });


		std::shared_ptr<class GameEngineRenderer> BG1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG1->SetPipeLine("2DTexture");

		BG1->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG1->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG1->GetTransform()->SetWorldPosition({ -822, -52, 400 });


		std::shared_ptr<class GameEngineRenderer> BG2 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		BG2->SetPipeLine("2DTexture");

		BG2->GetShaderResHelper().SetTexture("DiffuseTex", "BG1.png");
		BG2->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG2->GetTransform()->SetWorldPosition({ 1950, -52, 400 });
	}

	// 기둥
	{
		//블러 추가

		std::shared_ptr<class GameEngineRenderer> Pillar1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Pillar1->SetPipeLine("2DTexture");

		Pillar1->GetShaderResHelper().SetTexture("DiffuseTex", "Pillar.png");
		Pillar1->GetTransform()->SetLocalScale({ -902, 1140 });
		Pillar1->GetTransform()->SetWorldPosition({ 1971, -120, 60 });



		std::shared_ptr<class GameEngineRenderer> Pillar2 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Pillar2->SetPipeLine("2DTexture");

		Pillar2->GetShaderResHelper().SetTexture("DiffuseTex", "Pillar.png");
		Pillar2->GetTransform()->SetLocalScale({ 902, 1140 });
		Pillar2->GetTransform()->SetWorldPosition({ -836, -94, 60 });
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

		//블러 추가
		std::shared_ptr<class GameEngineRenderer> Rag7 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag7->SetPipeLine("2DTexture");

		Rag7->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag7->GetTransform()->SetLocalScale({ 169, 340 });
		Rag7->GetTransform()->AddLocalScale({ 100,100 });
		Rag7->GetTransform()->SetWorldPosition({ -526, 400, 100 });

		std::shared_ptr<class GameEngineRenderer> Rag8 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag8->SetPipeLine("2DTexture");

		Rag8->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag8->GetTransform()->SetLocalScale({ 169, 340 });
		Rag8->GetTransform()->AddLocalScale({ 100,100 });
		Rag8->GetTransform()->SetWorldPosition({ -66, 400, 250 });

		std::shared_ptr<class GameEngineRenderer> Rag9 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag9->SetPipeLine("2DTexture");

		Rag9->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag9->GetTransform()->SetLocalScale({ 169, 340 });
		Rag9->GetTransform()->AddLocalScale({ 100,100 });
		Rag9->GetTransform()->SetWorldPosition({ 1400, 600, 350 });

		std::shared_ptr<class GameEngineRenderer> Rag10 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag10->SetPipeLine("2DTexture");

		Rag10->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag10->GetTransform()->SetLocalScale({ 169, 340 });
		Rag10->GetTransform()->AddLocalScale({ 100,150 });
		Rag10->GetTransform()->SetWorldPosition({ 1700, 380, 370 });

		std::shared_ptr<class GameEngineRenderer> Rag10_1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag10_1->SetPipeLine("2DTexture");

		Rag10_1->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag10_1->GetTransform()->SetLocalScale({ 169, 340 });
		Rag10_1->GetTransform()->AddLocalScale({ 100,150 });
		Rag10_1->GetTransform()->SetWorldPosition({ 2000, 550, 390 });

		std::shared_ptr<class GameEngineRenderer> Rag11 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag11->SetPipeLine("2DTexture");

		Rag11->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag11->GetTransform()->SetLocalScale({ 169, 340 });
		Rag11->GetTransform()->SetWorldPosition({ -250, 330, 360 });

		std::shared_ptr<class GameEngineRenderer> Rag12 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag12->SetPipeLine("2DTexture");

		Rag12->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag12->GetTransform()->SetLocalScale({ 169, 340 });
		Rag12->GetTransform()->SetWorldPosition({ 800, 400, 300 });

		std::shared_ptr<class GameEngineRenderer> Rag13 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag13->SetPipeLine("2DTexture");

		Rag13->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag13->GetTransform()->SetLocalScale({ 169, 340 });
		Rag13->GetTransform()->AddLocalScale({ 100,100 });
		Rag13->GetTransform()->SetWorldPosition({ 540, 400, 400 });

		std::shared_ptr<class GameEngineRenderer> Rag13_1 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag13_1->SetPipeLine("2DTexture");

		Rag13_1->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag13_1->GetTransform()->SetLocalScale({ 169, 340 });
		Rag13_1->GetTransform()->AddLocalScale({ 100,100 });
		Rag13_1->GetTransform()->SetWorldPosition({ 1300, 450, 400 });

		std::shared_ptr<class GameEngineRenderer> Rag14 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag14->SetPipeLine("2DTexture");

		Rag14->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag14->GetTransform()->SetLocalScale({ 169, 340 });
		Rag14->GetTransform()->AddLocalScale({ 50,150 });
		Rag14->GetTransform()->SetWorldPosition({ 1100, 450, 550 });

		std::shared_ptr<class GameEngineRenderer> Rag15 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag15->SetPipeLine("2DTexture");

		Rag15->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag15->GetTransform()->SetLocalScale({ 169, 340 });
		Rag15->GetTransform()->AddLocalScale({ 100,150 });
		Rag15->GetTransform()->SetWorldPosition({ 500, 550, 600 });

		std::shared_ptr<class GameEngineRenderer> Rag16 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag16->SetPipeLine("2DTexture");

		Rag16->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag16->GetTransform()->SetLocalScale({ 169, 340 });
		Rag16->GetTransform()->AddLocalScale({ 200,200 });
		Rag16->GetTransform()->SetWorldPosition({ 1000, 750, 600 });


		std::shared_ptr<class GameEngineRenderer> Rag17 = CreateComponent<GameEngineRenderer>(PlayRenderOrder::Background);
		Rag17->SetPipeLine("2DTexture");

		Rag17->GetShaderResHelper().SetTexture("DiffuseTex", "Rag.png");
		Rag17->GetTransform()->SetLocalScale({ 169, 340 });
		Rag17->GetTransform()->AddLocalScale({ 100,100 });
		Rag17->GetTransform()->SetWorldPosition({ 200, 500, 550 });
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