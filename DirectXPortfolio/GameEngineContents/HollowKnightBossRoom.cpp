#include "PrecompileHeader.h"

#include "HollowKnightBossRoom.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
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

	CreateMap();
}

void HollowKnightBossRoom::CreateMap()
{
	//Chain
	{
		std::shared_ptr<class GameEngineSpriteRenderer> Chain1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain1->SetTexture("Chain.png");
		Chain1->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain1->GetTransform()->SetWorldPosition({ -690, -174, -40 });
		Chain1->GetTransform()->SetWorldRotation({ 0, 0, 30 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
		
		Chain2->SetTexture("Chain.png");
		Chain2->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain2->GetTransform()->SetWorldPosition({ 1260, -174, -40 });
		Chain2->GetTransform()->SetWorldRotation({ 0, 0, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain3->SetTexture("Chain.png");
		Chain3->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain3->GetTransform()->SetWorldPosition({ 0, -135, 20 });
		Chain3->GetTransform()->SetWorldRotation({ 0, 0, -30 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain4 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain4->SetTexture("Chain.png");
		Chain4->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain4->GetTransform()->SetWorldPosition({ -322, -256, 30 });
		Chain4->GetTransform()->SetWorldRotation({ 0, 0, 40 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain5 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain5->SetTexture("Chain.png");
		Chain5->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain5->GetTransform()->SetWorldPosition({ 1585, -292, 30 });
		Chain5->GetTransform()->SetWorldRotation({ 0, 0, -30 });


		//블러 추가
		std::shared_ptr<class GameEngineSpriteRenderer> Chain8 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain8->SetTexture("Chain.png");
		Chain8->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain8->GetTransform()->SetWorldPosition({ -156, -156, 550 });
		Chain8->GetTransform()->SetWorldRotation({ 0, 0, -10 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain9 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain9->SetTexture("Chain.png");
		Chain9->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain9->GetTransform()->SetWorldPosition({ 756, -156, 550 });
		Chain9->GetTransform()->SetWorldRotation({ 0, 0, 10 });


		std::shared_ptr<class GameEngineSpriteRenderer> Chain6 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain6->SetTexture("Chain.png");
		Chain6->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain6->GetTransform()->SetWorldPosition({ 156, -156, 750 });
		Chain6->GetTransform()->SetWorldRotation({ 0, 0, -8 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain7 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain7->SetTexture("Chain.png");
		Chain7->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain7->GetTransform()->SetWorldPosition({ 556, -156, 750 });
		Chain7->GetTransform()->SetWorldRotation({ 0, 0, 8 });



		std::shared_ptr<class GameEngineSpriteRenderer> Chain10 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain10->SetTexture("Chain.png");
		Chain10->GetTransform()->SetLocalScale({ 26, 1448 });    //(190, 256)
		Chain10->GetTransform()->SetWorldPosition({ 1174, -124, 400 });
		Chain10->GetTransform()->SetWorldRotation({ 0, 0, 20 });

	}

	//BG
	{
		//블러 추가
		std::shared_ptr<class GameEngineSpriteRenderer> BG5 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG5->SetTexture( "BG1.png");
		BG5->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG5->GetTransform()->SetWorldPosition({ 300, -52, 950 });

		std::shared_ptr<class GameEngineSpriteRenderer> BG6 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG6->SetTexture("BG1.png");
		BG6->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG6->GetTransform()->SetWorldPosition({ 750, -52, 850 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG3->SetTexture("BG1.png");
		BG3->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG3->GetTransform()->SetWorldPosition({ -122, -52, 800 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG4 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG4->SetTexture( "BG1.png");
		BG4->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG4->GetTransform()->SetWorldPosition({ 1300, -52, 800 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG1->SetTexture("BG1.png");
		BG1->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG1->GetTransform()->SetWorldPosition({ -822, -52, 750 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG2->SetTexture("BG1.png");
		BG2->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG2->GetTransform()->SetWorldPosition({ 1950, -52, 750 });



		std::shared_ptr<class GameEngineSpriteRenderer> BG1_1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG1_1->SetTexture( "BG1.png");
		BG1_1->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG1_1->GetTransform()->SetWorldPosition({ -1422, -52, 550 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG2_1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG2_1->SetTexture("BG1.png");
		BG2_1->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG2_1->GetTransform()->SetWorldPosition({ 2550, -52, 550 });

	}

	// 기둥
	{
		//블러 추가

		std::shared_ptr<class GameEngineSpriteRenderer> Pillar1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Pillar1->SetTexture("Pillar.png");
		Pillar1->GetTransform()->SetLocalScale({ -902, 1140 });
		Pillar1->GetTransform()->SetWorldPosition({ 1971, -120, 60 });



		std::shared_ptr<class GameEngineSpriteRenderer> Pillar2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Pillar2->SetTexture("Pillar.png");
		Pillar2->GetTransform()->SetLocalScale({ 902, 1140 });
		Pillar2->GetTransform()->SetWorldPosition({ -836, -94, 60 });
	}

	//천막
	{
		std::shared_ptr<class GameEngineSpriteRenderer> Rag1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag1->SetTexture( "Rag.png");
		Rag1->GetTransform()->SetLocalScale({ 169, 340 });
		Rag1->GetTransform()->SetWorldPosition({ -701, 200, -20 });
		Rag1->GetTransform()->AddLocalScale({ 0,30 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag2->SetTexture("Rag.png");
		Rag2->GetTransform()->SetLocalScale({ 169, 340 });
		Rag2->GetTransform()->SetWorldPosition({ -480, 270, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
	
		Rag3->SetTexture( "Rag.png");
		Rag3->GetTransform()->SetLocalScale({ 169, 340 });
		Rag3->GetTransform()->SetWorldPosition({ -300, 360, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag4 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag4->SetTexture("Rag.png");
		Rag4->GetTransform()->SetLocalScale({ 169, 340 });
		Rag4->GetTransform()->SetWorldPosition({ 1500, 330, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag5 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag5->SetTexture("Rag.png");
		Rag5->GetTransform()->SetLocalScale({ 169, 340 });
		Rag5->GetTransform()->AddLocalScale({ 0,60 });
		Rag5->GetTransform()->SetWorldPosition({ 1669, 230, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag6 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag6->SetTexture("Rag.png");
		Rag6->GetTransform()->SetLocalScale({ 169, 340 });
		Rag6->GetTransform()->AddLocalScale({ 0,100 });
		Rag6->GetTransform()->SetWorldPosition({ 1838, 130, -20 });

		//블러 추가
		std::shared_ptr<class GameEngineSpriteRenderer> Rag7 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag7->SetTexture("Rag.png");
		Rag7->GetTransform()->SetLocalScale({ 169, 340 });
		Rag7->GetTransform()->AddLocalScale({ 100,100 });
		Rag7->GetTransform()->SetWorldPosition({ -526, 400, 100 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag8 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag8->SetTexture("Rag.png");
		Rag8->GetTransform()->SetLocalScale({ 169, 340 });
		Rag8->GetTransform()->AddLocalScale({ 100,100 });
		Rag8->GetTransform()->SetWorldPosition({ -66, 400, 250 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag9 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag9->SetTexture("Rag.png");
		Rag9->GetTransform()->SetLocalScale({ 169, 340 });
		Rag9->GetTransform()->AddLocalScale({ 100,100 });
		Rag9->GetTransform()->SetWorldPosition({ 1400, 600, 350 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag10 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag10->SetTexture("Rag.png");
		Rag10->GetTransform()->SetLocalScale({ 169, 340 });
		Rag10->GetTransform()->AddLocalScale({ 100,150 });
		Rag10->GetTransform()->SetWorldPosition({ 1700, 380, 370 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag10_1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag10_1->SetTexture("Rag.png");
		Rag10_1->GetTransform()->SetLocalScale({ 169, 340 });
		Rag10_1->GetTransform()->AddLocalScale({ 100,150 });
		Rag10_1->GetTransform()->SetWorldPosition({ 2000, 550, 390 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag11 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag11->SetTexture("Rag.png");
		Rag11->GetTransform()->SetLocalScale({ 169, 340 });
		Rag11->GetTransform()->SetWorldPosition({ -250, 330, 360 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag12 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag12->SetTexture("Rag.png");
		Rag12->GetTransform()->SetLocalScale({ 169, 340 });
		Rag12->GetTransform()->SetWorldPosition({ 800, 400, 300 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag13 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag13->SetTexture("Rag.png");
		Rag13->GetTransform()->SetLocalScale({ 169, 340 });
		Rag13->GetTransform()->AddLocalScale({ 100,100 });
		Rag13->GetTransform()->SetWorldPosition({ 540, 400, 400 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag13_1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag13_1->SetTexture("Rag.png");
		Rag13_1->GetTransform()->SetLocalScale({ 169, 340 });
		Rag13_1->GetTransform()->AddLocalScale({ 100,100 });
		Rag13_1->GetTransform()->SetWorldPosition({ 1300, 450, 400 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag14 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag14->SetTexture( "Rag.png");
		Rag14->GetTransform()->SetLocalScale({ 169, 340 });
		Rag14->GetTransform()->AddLocalScale({ 50,150 });
		Rag14->GetTransform()->SetWorldPosition({ 1100, 450, 550 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag15 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag15->SetTexture("Rag.png");
		Rag15->GetTransform()->SetLocalScale({ 169, 340 });
		Rag15->GetTransform()->AddLocalScale({ 100,150 });
		Rag15->GetTransform()->SetWorldPosition({ 500, 550, 600 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag16 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag16->SetTexture("Rag.png");
		Rag16->GetTransform()->SetLocalScale({ 169, 340 });
		Rag16->GetTransform()->AddLocalScale({ 200,200 });
		Rag16->GetTransform()->SetWorldPosition({ 1000, 750, 600 });


		std::shared_ptr<class GameEngineSpriteRenderer> Rag17 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
		Rag17->SetTexture("Rag.png");

		Rag17->GetTransform()->SetLocalScale({ 169, 340 });
		Rag17->GetTransform()->AddLocalScale({ 100,100 });
		Rag17->GetTransform()->SetWorldPosition({ 200, 500, 550 });
	}

	//바닥
	{
		std::shared_ptr<class GameEngineSpriteRenderer> FloorEmblem = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);
		FloorEmblem->SetTexture("FloorEmblem.png");
		FloorEmblem->GetTransform()->SetLocalScale({ 1024, 256 });
		FloorEmblem->SetScaleRatio(1.5f);
		FloorEmblem->GetTransform()->SetWorldPosition({ 575, -675, -140 });
	}

	MainRoomImage = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Map);
	MainRoomImage->SetTexture("HollowKnightBossRoomMain.png");

	MainRoomImage->GetTransform()->SetLocalScale({ 5000, 1500 });
	MainRoomImage->GetTransform()->SetLocalPosition({ 0, 0, -70 }); //원본 크기 기준 z -> -70.0f

}

void HollowKnightBossRoom::Update(float _Delta)
{

}