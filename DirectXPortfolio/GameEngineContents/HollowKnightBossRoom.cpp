#include "PrecompileHeader.h"

#include "HollowKnightBossRoom.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "HollowKnightBossOrangeBlob.h"
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

		Chain1->SetScaleToTexture("Chain.png");
		Chain1->GetTransform()->SetWorldPosition({ -690, -174, -40 });
		Chain1->GetTransform()->SetWorldRotation({ 0, 0, 30 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
		
		Chain2->SetScaleToTexture("Chain.png");
		Chain2->GetTransform()->SetWorldPosition({ 1260, -174, -40 });
		Chain2->GetTransform()->SetWorldRotation({ 0, 0, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain3->SetScaleToTexture("Chain.png");
		Chain3->GetTransform()->SetWorldPosition({ 0, -135, 20 });
		Chain3->GetTransform()->SetWorldRotation({ 0, 0, -30 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain4 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain4->SetScaleToTexture("Chain.png");
		Chain4->GetTransform()->SetWorldPosition({ -322, -256, 30 });
		Chain4->GetTransform()->SetWorldRotation({ 0, 0, 40 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain5 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain5->SetScaleToTexture("Chain.png");
		Chain5->GetTransform()->SetWorldPosition({ 1585, -292, 30 });
		Chain5->GetTransform()->SetWorldRotation({ 0, 0, -30 });


		//블러 추가
		std::shared_ptr<class GameEngineSpriteRenderer> Chain8 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain8->SetScaleToTexture("Chain.png");
		Chain8->GetTransform()->SetWorldPosition({ -156, -156, 550 });
		Chain8->GetTransform()->SetWorldRotation({ 0, 0, -10 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain9 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain9->SetScaleToTexture("Chain.png");
		Chain9->GetTransform()->SetWorldPosition({ 806, -156, 550 });
		Chain9->GetTransform()->SetWorldRotation({ 0, 0, 10 });


		std::shared_ptr<class GameEngineSpriteRenderer> Chain6 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain6->SetScaleToTexture("Chain.png");
		Chain6->GetTransform()->SetWorldPosition({ 56, -216, 750 });
		Chain6->GetTransform()->SetWorldRotation({ 0, 0, -8 });

		std::shared_ptr<class GameEngineSpriteRenderer> Chain7 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain7->SetScaleToTexture("Chain.png");
		Chain7->GetTransform()->SetWorldPosition({ 606, -216, 750 });
		Chain7->GetTransform()->SetWorldRotation({ 0, 0, 8 });


		std::shared_ptr<class GameEngineSpriteRenderer> Chain10 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Chain10->SetScaleToTexture("Chain.png");
		Chain10->GetTransform()->SetWorldPosition({ 1174, -124, 400 });
		Chain10->GetTransform()->SetWorldRotation({ 0, 0, 20 });

	}

	//BG
	{
		//블러 추가
		std::shared_ptr<class GameEngineSpriteRenderer> BG5 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG5->SetTexture( "BG1.png");
		BG5->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG5->GetTransform()->SetWorldPosition({ 300, -142, 950 });

		std::shared_ptr<class GameEngineSpriteRenderer> BG6 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG6->SetTexture("BG1.png");
		BG6->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG6->GetTransform()->SetWorldPosition({ 750, -142, 850 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG3->SetTexture("BG1.png");
		BG3->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG3->GetTransform()->SetWorldPosition({ -122, -112, 800 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG4 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG4->SetTexture( "BG1.png");
		BG4->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG4->GetTransform()->SetWorldPosition({ 1300, -112, 800 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG1->SetTexture("BG1.png");
		BG1->GetTransform()->SetLocalScale({ -1024, 2048 });    //(190, 256)
		BG1->GetTransform()->SetWorldPosition({ -822, -82, 750 });


		std::shared_ptr<class GameEngineSpriteRenderer> BG2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		BG2->SetTexture("BG1.png");
		BG2->GetTransform()->SetLocalScale({ 1024, 2048 });    //(190, 256)
		BG2->GetTransform()->SetWorldPosition({ 1950, -82, 750 });



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
		Pillar1->SetScaleToTexture("Pillar.png");
		Pillar1->SetFlipX();
		Pillar1->GetTransform()->SetWorldPosition({ 1971, -120, 60 });

		std::shared_ptr<class GameEngineSpriteRenderer> Pillar2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
		Pillar2->SetScaleToTexture("Pillar.png");
		Pillar2->GetTransform()->SetWorldPosition({ -836, -94, 60 });
	}

	//천막
	{
		std::shared_ptr<class GameEngineSpriteRenderer> Rag1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag1->SetScaleToTexture("Rag.png");
		Rag1->GetTransform()->SetWorldPosition({ -701, 200, -20 });
		Rag1->GetTransform()->AddLocalScale({ 0,30 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag2->SetScaleToTexture("Rag.png");
		Rag2->GetTransform()->SetWorldPosition({ -480, 270, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
	
		Rag3->SetScaleToTexture( "Rag.png");
		Rag3->GetTransform()->SetWorldPosition({ -300, 360, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag4 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag4->SetScaleToTexture("Rag.png");
		Rag4->GetTransform()->SetWorldPosition({ 1500, 330, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag5 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag5->SetScaleToTexture("Rag.png");
		Rag5->GetTransform()->AddLocalScale({ 0,60 });
		Rag5->GetTransform()->SetWorldPosition({ 1669, 230, -20 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag6 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag6->SetScaleToTexture("Rag.png");
		Rag6->GetTransform()->AddLocalScale({ 0,100 });
		Rag6->GetTransform()->SetWorldPosition({ 1838, 130, -20 });

		//블러 추가
		std::shared_ptr<class GameEngineSpriteRenderer> Rag7 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag7->SetScaleToTexture("Rag.png");
		Rag7->GetTransform()->AddLocalScale({ 100,100 });
		Rag7->GetTransform()->SetWorldPosition({ -526, 400, 100 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag8 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag8->SetScaleToTexture("Rag.png");
		Rag8->GetTransform()->AddLocalScale({ 100,100 });
		Rag8->GetTransform()->SetWorldPosition({ -66, 400, 250 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag9 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag9->SetScaleToTexture("Rag.png");
		Rag9->GetTransform()->AddLocalScale({ 100,100 });
		Rag9->GetTransform()->SetWorldPosition({ 1400, 600, 350 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag10 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag10->SetScaleToTexture("Rag.png");
		Rag10->GetTransform()->AddLocalScale({ 100,150 });
		Rag10->GetTransform()->SetWorldPosition({ 1700, 380, 370 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag10_1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag10_1->SetScaleToTexture("Rag.png");
		Rag10_1->GetTransform()->AddLocalScale({ 100,150 });
		Rag10_1->GetTransform()->SetWorldPosition({ 2000, 550, 390 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag11 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag11->SetScaleToTexture("Rag.png");
		Rag11->GetTransform()->SetWorldPosition({ -250, 330, 360 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag12 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag12->SetScaleToTexture("Rag.png");
		Rag12->GetTransform()->SetWorldPosition({ 800, 400, 300 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag13 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag13->SetScaleToTexture("Rag.png");
		Rag13->GetTransform()->AddLocalScale({ 100,100 });
		Rag13->GetTransform()->SetWorldPosition({ 540, 400, 400 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag13_1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag13_1->SetScaleToTexture("Rag.png");
		Rag13_1->GetTransform()->AddLocalScale({ 100,100 });
		Rag13_1->GetTransform()->SetWorldPosition({ 1300, 450, 400 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag14 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag14->SetScaleToTexture( "Rag.png");
		Rag14->GetTransform()->AddLocalScale({ 50,150 });
		Rag14->GetTransform()->SetWorldPosition({ 1100, 450, 550 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag15 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag15->SetScaleToTexture("Rag.png");
		Rag15->GetTransform()->AddLocalScale({ 100,150 });
		Rag15->GetTransform()->SetWorldPosition({ 500, 550, 600 });

		std::shared_ptr<class GameEngineSpriteRenderer> Rag16 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);

		Rag16->SetScaleToTexture("Rag.png");
		Rag16->GetTransform()->AddLocalScale({ 200,200 });
		Rag16->GetTransform()->SetWorldPosition({ 1000, 750, 600 });


		std::shared_ptr<class GameEngineSpriteRenderer> Rag17 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
		Rag17->SetScaleToTexture("Rag.png");
		Rag17->GetTransform()->AddLocalScale({ 100,100 });
		Rag17->GetTransform()->SetWorldPosition({ 200, 500, 550 });
	}

	//바닥
	{
		std::shared_ptr<class GameEngineSpriteRenderer> FloorEmblem = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);
		FloorEmblem->SetScaleToTexture("FloorEmblem.png");
		FloorEmblem->GetTransform()->SetWorldPosition({ 570, -670, -120 });

		std::shared_ptr<class GameEngineSpriteRenderer> Floor1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);
		Floor1->SetScaleToTexture("Floor.png");
		Floor1->GetTransform()->SetWorldPosition({ 167, -633, -80 });

		std::shared_ptr<class GameEngineSpriteRenderer> Floor2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);
		Floor2->SetScaleToTexture("Floor.png");
		Floor2->GetTransform()->SetWorldPosition({ 127, -653, -100 });
	}

	//Blob
	{
		std::shared_ptr<HollowKnightBossOrangeBlob> Blob01 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
		std::shared_ptr<class GameEngineSpriteRenderer> Blob01Renderer = Blob01->CreateBlobActor(OrangeBlobType::LargeBlob01);
		Blob01->GetTransform()->SetWorldPosition({ -591, -593, -69 });

		std::shared_ptr<HollowKnightBossOrangeBlob> Blob02 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
		std::shared_ptr<class GameEngineSpriteRenderer> Blob02Renderer = Blob02->CreateBlobActor(OrangeBlobType::LargeBlob03);
		Blob02->GetTransform()->SetWorldPosition({ -494, -585, -68 });

		std::shared_ptr<HollowKnightBossOrangeBlob> Blob03 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
		std::shared_ptr<class GameEngineSpriteRenderer> Blob03Renderer = Blob03->CreateBlobActor(OrangeBlobType::LargeBlob03);
		Blob03->GetTransform()->SetWorldPosition({ -717, -585, -68 });

		std::shared_ptr<HollowKnightBossOrangeBlob> Blob04 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
		std::shared_ptr<class GameEngineSpriteRenderer> Blob04Renderer = Blob04->CreateBlobActor(OrangeBlobType::LargeBlob03);
		Blob04->GetTransform()->SetWorldPosition({ 1553, -575, -68 });

		std::shared_ptr<HollowKnightBossOrangeBlob> Blob05 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
		std::shared_ptr<class GameEngineSpriteRenderer> Blob05Renderer = Blob05->CreateBlobActor(OrangeBlobType::LargeBlob03);
		Blob05->GetTransform()->SetWorldPosition({ 2100, -597, -68 });


		//blur
		std::shared_ptr<HollowKnightBossOrangeBlob> BlurBlob01 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
		std::shared_ptr<class GameEngineSpriteRenderer> BlurBlob01Renderer = BlurBlob01->CreateBlobActor(OrangeBlobType::LargeBlob03);
		BlurBlob01Renderer->SetScaleRatio(3.0f);
		BlurBlob01->GetTransform()->SetWorldPosition({ -850, -700, 0 });
	}

	MainRoomImage = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Map);
	MainRoomImage->SetTexture("HollowKnightBossRoomMain.png");

	MainRoomImage->GetTransform()->SetLocalScale({ 5000, 1500 });
	MainRoomImage->GetTransform()->SetLocalPosition({ 0, 0, -70 }); //원본 크기 기준 z -> -70.0f

}

void HollowKnightBossRoom::Update(float _Delta)
{

}