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
		Pillar1->GetTransform()->SetWorldPosition({ 2021, -120, 90 });

		std::shared_ptr<class GameEngineSpriteRenderer> Pillar2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
		Pillar2->SetScaleToTexture("Pillar.png");
		Pillar2->GetTransform()->SetWorldPosition({ -936, -104, 90 });
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
		Floor1->SetScaleToTexture("BlankFloor.png");
		Floor1->GetTransform()->SetWorldPosition({ 167, -633, -80 });

		std::shared_ptr<class GameEngineSpriteRenderer> Floor2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);
		Floor2->SetScaleToTexture("Floor.png");
		Floor2->GetTransform()->SetWorldPosition({ 127, -653, -100 });
	}

	//Blob , Vine
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

		// 덩굴과 함께있는 Blob
		{
			{
				std::shared_ptr<GameEngineActor> Vine01_1 = GetLevel()->CreateActor<GameEngineActor>();
				std::shared_ptr<class GameEngineSpriteRenderer> Vine01_1Render = Vine01_1->CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
				Vine01_1Render->SetScaleToTexture("Vine01.png");

				//Blob들
				{
					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_1Blob01 = Vine01_1->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_1Blob01->GetTransform()->SetParent(Vine01_1->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_1Blob01Render = Vine01_1Blob01->CreateBlobActor(OrangeBlobType::SmallBlob02);
					Vine01_1Blob01Render->GetTransform()->SetLocalPosition({ -34, 73, 1 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_1Blob02 = Vine01_1->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_1Blob02->GetTransform()->SetParent(Vine01_1->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_1Blob02Render = Vine01_1Blob02->CreateBlobActor(OrangeBlobType::SmallBlob03);
					Vine01_1Blob02Render->GetTransform()->SetLocalPosition({ -26, 125, 1 });
					Vine01_1Blob02Render->GetTransform()->SetLocalRotation({ 0, 0, -135 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_1Blob03 = Vine01_1->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_1Blob03->GetTransform()->SetParent(Vine01_1->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_1Blob03Render = Vine01_1Blob03->CreateBlobActor(OrangeBlobType::SmallBlob03);
					Vine01_1Blob03Render->GetTransform()->SetLocalPosition({ 1, 163, -5 });
					Vine01_1Blob03Render->GetTransform()->SetLocalRotation({ 0, 0, -135 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_1Blob04 = Vine01_1->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_1Blob04->GetTransform()->SetParent(Vine01_1->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_1Blob04Render = Vine01_1Blob04->CreateBlobActor(OrangeBlobType::SmallBlob02);
					Vine01_1Blob04Render->GetTransform()->SetLocalPosition({ -60, -60, 1 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_1Blob05 = Vine01_1->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_1Blob05->GetTransform()->SetParent(Vine01_1->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_1Blob05Render = Vine01_1Blob05->CreateBlobActor(OrangeBlobType::SmallBlob03);
					Vine01_1Blob05Render->GetTransform()->SetLocalPosition({ 63, -133, -1 });
					Vine01_1Blob05Render->GetTransform()->SetLocalRotation({ 0, 0, -110 });
				}

				Vine01_1->GetTransform()->SetWorldPosition({ -1100, -490, 80 });
				Vine01_1->GetTransform()->SetWorldRotation({ 0, 0, 35 });
			}

			{
				std::shared_ptr<GameEngineActor> Vine01_2 = GetLevel()->CreateActor<GameEngineActor>();
				std::shared_ptr<class GameEngineSpriteRenderer> Vine01_2Render = Vine01_2->CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
				Vine01_2Render->SetScaleToTexture("Vine01.png");

				//Blob들
				{
					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_2Blob01 = Vine01_2->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_2Blob01->GetTransform()->SetParent(Vine01_2->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_2Blob01Render = Vine01_2Blob01->CreateBlobActor(OrangeBlobType::SmallBlob02);
					Vine01_2Blob01Render->GetTransform()->SetLocalPosition({ -34, 73, 1 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_2Blob02 = Vine01_2->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_2Blob02->GetTransform()->SetParent(Vine01_2->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_2Blob02Render = Vine01_2Blob02->CreateBlobActor(OrangeBlobType::SmallBlob03);
					Vine01_2Blob02Render->GetTransform()->SetLocalPosition({ -26, 125, 1 });
					Vine01_2Blob02Render->GetTransform()->SetLocalRotation({ 0, 0, -135 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_2Blob03 = Vine01_2->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_2Blob03->GetTransform()->SetParent(Vine01_2->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_2Blob03Render = Vine01_2Blob03->CreateBlobActor(OrangeBlobType::SmallBlob03);
					Vine01_2Blob03Render->GetTransform()->SetLocalPosition({ 1, 163, -5 });
					Vine01_2Blob03Render->GetTransform()->SetLocalRotation({ 0, 0, -135 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_2Blob04 = Vine01_2->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_2Blob04->GetTransform()->SetParent(Vine01_2->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_2Blob04Render = Vine01_2Blob04->CreateBlobActor(OrangeBlobType::SmallBlob02);
					Vine01_2Blob04Render->GetTransform()->SetLocalPosition({ -60, -60, 1 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine01_2Blob05 = Vine01_2->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine01_2Blob05->GetTransform()->SetParent(Vine01_2->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine01_2Blob05Render = Vine01_2Blob05->CreateBlobActor(OrangeBlobType::SmallBlob03);
					Vine01_2Blob05Render->GetTransform()->SetLocalPosition({ 63, -133, -1 });
					Vine01_2Blob05Render->GetTransform()->SetLocalRotation({ 0, 0, -110 });
				}

				Vine01_2->GetTransform()->SetWorldPosition({ 2093,-498, 80 });
				Vine01_2->GetTransform()->SetWorldRotation({ 0, 0, 130 });
			}

			{
				std::shared_ptr<GameEngineActor> Vine02 = GetLevel()->CreateActor<GameEngineActor>();
				std::shared_ptr<class GameEngineSpriteRenderer> Vine02Render = Vine02->CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
				Vine02Render->SetScaleToTexture("Vine02.png");

				//Blob들
				{
					std::shared_ptr<HollowKnightBossOrangeBlob> Vine02Blob01 = Vine02->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine02Blob01->GetTransform()->SetParent(Vine02->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine02Blob01Render = Vine02Blob01->CreateBlobActor(OrangeBlobType::SmallBlob01);
					Vine02Blob01Render->GetTransform()->SetLocalPosition({ -154, 36, 1 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine02Blob02 = Vine02->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine02Blob02->GetTransform()->SetParent(Vine02->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine02Blob02Render = Vine02Blob02->CreateBlobActor(OrangeBlobType::SmallBlob01);
					Vine02Blob02Render->GetTransform()->SetLocalPosition({ -100, 94, -1 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine02Blob03 = Vine02->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine02Blob03->GetTransform()->SetParent(Vine02->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine02Blob03Render = Vine02Blob03->CreateBlobActor(OrangeBlobType::SmallBlob01);
					Vine02Blob03Render->GetTransform()->SetLocalPosition({ -70, 75, 1 });
					Vine02Blob03Render->GetTransform()->SetLocalRotation({ 0, 0, 90 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine02Blob04 = Vine02->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine02Blob04->GetTransform()->SetParent(Vine02->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine02Blob04Render = Vine02Blob04->CreateBlobActor(OrangeBlobType::SmallBlob03);
					Vine02Blob04Render->GetTransform()->SetLocalPosition({ -10, 65, -1 });
					Vine02Blob04Render->GetTransform()->SetLocalRotation({ 0, 0, -80 });

					std::shared_ptr<HollowKnightBossOrangeBlob> Vine02Blob05 = Vine02->GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
					Vine02Blob05->GetTransform()->SetParent(Vine02->GetTransform());
					std::shared_ptr<class GameEngineSpriteRenderer> Vine02Blob05Render = Vine02Blob05->CreateBlobActor(OrangeBlobType::SmallBlob01);
					Vine02Blob05Render->GetTransform()->SetLocalPosition({ 70, 35, -1 });
				}

				Vine02->GetTransform()->SetWorldPosition({ -250,-680, 200 });
			}

		}


		//blur
		std::shared_ptr<HollowKnightBossOrangeBlob> BlurBlob01 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
		std::shared_ptr<class GameEngineSpriteRenderer> BlurBlob01Renderer = BlurBlob01->CreateBlobActor(OrangeBlobType::LargeBlob03);
		BlurBlob01Renderer->SetFlipX();
		BlurBlob01Renderer->SetScaleRatio(2.5f);
		BlurBlob01->GetTransform()->SetWorldPosition({ -1050, -700, 89 });
	}


	//UpperLayer 최상단 카메라 앞 레이어 (계단 기준 -120)
	{
		std::shared_ptr<class GameEngineSpriteRenderer> EnterUpperLayer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

		EnterUpperLayer->SetScaleToTexture("EnterUpperLayer.png");
		EnterUpperLayer->GetTransform()->SetLocalScale({ 1384, 1480 });
		EnterUpperLayer->GetTransform()->SetLocalPosition({ -1900, -326, -121 });


		//Rag
		{
			//왼쪽 끝 부터
			std::shared_ptr<class GameEngineSpriteRenderer> Rag1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag1->SetScaleToTexture("Rag.png");
			Rag1->ColorOptionValue.MulColor = float4::Black;
			Rag1->GetTransform()->SetWorldPosition({ -1822, -304, -190 });
			Rag1->GetTransform()->AddLocalScale({ 0,150 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag2->SetScaleToTexture("Rag.png");
			Rag2->ColorOptionValue.MulColor = float4::Black;
			Rag2->GetTransform()->SetWorldPosition({ -1592, -305, -190 });
			Rag2->GetTransform()->AddLocalScale({ 50,150 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag3->SetScaleToTexture("Rag.png");
			Rag3->ColorOptionValue.MulColor = float4::Black;
			Rag3->GetTransform()->SetWorldPosition({ -1178, -50, -400 });
			Rag3->GetTransform()->AddLocalScale({ 50,350 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag4 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag4->SetScaleToTexture("Rag.png");
			Rag4->ColorOptionValue.MulColor = float4::Black;
			Rag4->GetTransform()->SetWorldPosition({ -928, 150, -300 });
			Rag4->GetTransform()->AddLocalScale({ 50,150 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag5 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag5->SetScaleToTexture("Rag.png");
			Rag5->ColorOptionValue.MulColor = float4::Black;
			Rag5->GetTransform()->SetWorldPosition({ -808, 250, -300 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag6 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag6->SetScaleToTexture("Rag.png");
			Rag6->ColorOptionValue.MulColor = float4::Black;
			Rag6->GetTransform()->SetWorldPosition({ -578, 220, -400 });
			Rag6->GetTransform()->AddLocalScale({ 50,450 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag7 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag7->SetScaleToTexture("Rag.png");
			Rag7->ColorOptionValue.MulColor = float4::Black;
			Rag7->GetTransform()->SetWorldPosition({ -578, 370, -400 });
			Rag7->GetTransform()->AddLocalScale({ 50,450 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag8 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag8->SetScaleToTexture("Rag.png");
			Rag8->ColorOptionValue.MulColor = float4::Black;
			Rag8->GetTransform()->SetWorldPosition({ -150, 230, -400 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag9 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag9->SetScaleToTexture("Rag.png");
			Rag9->ColorOptionValue.MulColor = float4::Black;
			Rag9->GetTransform()->SetWorldPosition({ -250, 270, -300 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag10 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag9->SetScaleToTexture("Rag.png");
			Rag9->ColorOptionValue.MulColor = float4::Black;
			Rag9->GetTransform()->SetWorldPosition({ -450, 300, -250 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag11 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag11->SetScaleToTexture("Rag.png");
			Rag11->ColorOptionValue.MulColor = float4::Black;
			Rag11->GetTransform()->SetWorldPosition({ 100, 250, -400 });

			//오른쪽 끝 부터

			std::shared_ptr<class GameEngineSpriteRenderer> Rag12 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag12->SetScaleToTexture("Rag.png");
			Rag12->ColorOptionValue.MulColor = float4::Black;
			Rag12->GetTransform()->SetWorldPosition({ 1900, 104, -400 });
			Rag12->GetTransform()->AddLocalScale({ 50,450 });
			Rag12->SetFlipX();

			std::shared_ptr<class GameEngineSpriteRenderer> Rag13 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag13->SetScaleToTexture("Rag.png");
			Rag13->ColorOptionValue.MulColor = float4::Black;
			Rag13->GetTransform()->SetWorldPosition({ 1700, 174, -400 });;
			Rag13->GetTransform()->AddLocalScale({ 0,100 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag14 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag14->SetScaleToTexture("Rag.png");
			Rag14->ColorOptionValue.MulColor = float4::Black;
			Rag14->GetTransform()->SetWorldPosition({ 1550, 224, -400 });;

			std::shared_ptr<class GameEngineSpriteRenderer> Rag15 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag15->SetScaleToTexture("Rag.png");
			Rag15->ColorOptionValue.MulColor = float4::Black;
			Rag15->GetTransform()->SetWorldPosition({ 1350, 154, -400 });;
			Rag15->GetTransform()->AddLocalScale({ 0,100 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag16 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag16->SetScaleToTexture("Rag.png");
			Rag16->ColorOptionValue.MulColor = float4::Black;
			Rag16->GetTransform()->SetWorldPosition({ 1000, 254, -400 });
			Rag16->GetTransform()->AddLocalScale({ 50,350 });
			Rag16->SetFlipX();

			std::shared_ptr<class GameEngineSpriteRenderer> Rag17 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag17->SetScaleToTexture("Rag.png");
			Rag17->ColorOptionValue.MulColor = float4::Black;
			Rag17->GetTransform()->SetWorldPosition({ 1650, 254, -300 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag18 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag18->SetScaleToTexture("Rag.png");
			Rag18->ColorOptionValue.MulColor = float4::Black;
			Rag18->GetTransform()->SetWorldPosition({ 1800, 254, -300 });

			std::shared_ptr<class GameEngineSpriteRenderer> Rag19 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rag19->SetScaleToTexture("Rag.png");
			Rag19->ColorOptionValue.MulColor = float4::Black;
			Rag19->GetTransform()->SetWorldPosition({ 1100, 254, -300 });

		}

		//Vine
		{
			
		}

		//Blob
		{
			std::shared_ptr<HollowKnightBossOrangeBlob> Blob01 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
			std::shared_ptr<class GameEngineSpriteRenderer> Blob01Renderer = Blob01->CreateBlobActor(OrangeBlobType::LargeBlob03, PlayRenderOrder::UpperLayer);
			Blob01->GetTransform()->SetWorldPosition({ -1826, -610, -200 });
			Blob01->GetTransform()->SetWorldRotation({ 0, 0, -30});
			Blob01Renderer->ColorOptionValue.MulColor = float4::Black;

			std::shared_ptr<HollowKnightBossOrangeBlob> Blob02 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
			std::shared_ptr<class GameEngineSpriteRenderer> Blob02Renderer = Blob02->CreateBlobActor(OrangeBlobType::LargeBlob03, PlayRenderOrder::UpperLayer);
			Blob02->GetTransform()->SetWorldPosition({ -1026, -630, -200 });
			Blob02->GetTransform()->SetWorldRotation({ 0, 0, -30 });
			Blob02Renderer->ColorOptionValue.MulColor = float4::Black;

			std::shared_ptr<HollowKnightBossOrangeBlob> Blob03 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
			std::shared_ptr<class GameEngineSpriteRenderer> Blob03Renderer = Blob03->CreateBlobActor(OrangeBlobType::LargeBlob03, PlayRenderOrder::UpperLayer);
			Blob03->GetTransform()->SetWorldPosition({ -400, -630, -200 });
			Blob03->GetTransform()->SetWorldRotation({ 0, 0, -30 });
			Blob03Renderer->ColorOptionValue.MulColor = float4::Black;

			std::shared_ptr<HollowKnightBossOrangeBlob> Blob04 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
			std::shared_ptr<class GameEngineSpriteRenderer> Blob04Renderer = Blob04->CreateBlobActor(OrangeBlobType::LargeBlob03, PlayRenderOrder::UpperLayer);
			Blob04->GetTransform()->SetWorldPosition({ 400, -610, -240 });
			Blob04->GetTransform()->SetWorldRotation({ 0, 0, -30 });
			Blob04Renderer->ColorOptionValue.MulColor = float4::Black;

			std::shared_ptr<HollowKnightBossOrangeBlob> Blob05 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
			std::shared_ptr<class GameEngineSpriteRenderer> Blob05Renderer = Blob05->CreateBlobActor(OrangeBlobType::LargeBlob03, PlayRenderOrder::UpperLayer);
			Blob05->GetTransform()->SetWorldPosition({ 1200, -610, -240 });
			Blob05->GetTransform()->SetWorldRotation({ 0, 0, -30 });
			Blob05Renderer->ColorOptionValue.MulColor = float4::Black;


			std::shared_ptr<HollowKnightBossOrangeBlob> Blob06 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
			std::shared_ptr<class GameEngineSpriteRenderer> Blob06Renderer = Blob06->CreateBlobActor(OrangeBlobType::LargeBlob03, PlayRenderOrder::UpperLayer);
			Blob06->GetTransform()->SetWorldPosition({ 1625, -630, -240 });
			Blob06->GetTransform()->SetWorldRotation({ 0, 0, -30 });
			Blob06Renderer->ColorOptionValue.MulColor = float4::Black;
			

			std::shared_ptr<HollowKnightBossOrangeBlob> Blob07 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
			std::shared_ptr<class GameEngineSpriteRenderer> Blob07Renderer = Blob07->CreateBlobActor(OrangeBlobType::LargeBlob03, PlayRenderOrder::UpperLayer);
			Blob07->GetTransform()->SetWorldPosition({ 1800, -610, -200 });
			Blob07->GetTransform()->SetWorldRotation({ 0, 0, -30 });
			Blob07Renderer->ColorOptionValue.MulColor = float4::Black;

			std::shared_ptr<HollowKnightBossOrangeBlob> Blob08 = GetLevel()->CreateActor<HollowKnightBossOrangeBlob>();
			std::shared_ptr<class GameEngineSpriteRenderer> Blob08Renderer = Blob08->CreateBlobActor(OrangeBlobType::LargeBlob03, PlayRenderOrder::UpperLayer);
			Blob08->GetTransform()->SetWorldPosition({ -1320, -244, -200 });
			Blob08->GetTransform()->SetWorldRotation({ 0, 0, 150 });
			Blob08Renderer->ColorOptionValue.MulColor = float4::Black;
		}

		//Rock
		{
			float RockScaleRatio = 1.2f; // 곱해줄 RockScale비율
			float4 RockScale = float4::Zero; //현재 RockScale 저장해두는 변수

			std::shared_ptr<class GameEngineSpriteRenderer> Rock1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rock1->SetScaleToTexture("HollowKnightBossRoomRock.png");
			RockScale = Rock1->GetTransform()->GetWorldScale();

			Rock1->GetTransform()->SetWorldPosition({ -1416, -615, -170 });
			Rock1->GetTransform()->SetWorldScale({ RockScale.x * RockScaleRatio, RockScale.y * RockScaleRatio, 1 });
			Rock1->SetFlipX();


			std::shared_ptr<class GameEngineSpriteRenderer> Rock2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rock2->SetScaleToTexture("HollowKnightBossRoomRock.png");
			Rock2->GetTransform()->SetWorldPosition({ 65, -615, -170 });
			Rock2->GetTransform()->SetWorldScale({RockScale.x * RockScaleRatio, RockScale.y * RockScaleRatio, 1});
			Rock2->SetFlipX();

			std::shared_ptr<class GameEngineSpriteRenderer> Rock3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			Rock3->SetScaleToTexture("HollowKnightBossRoomRock.png");
			Rock3->GetTransform()->SetWorldPosition({ 1065, -605, -170 });
			Rock3->GetTransform()->SetWorldScale({ RockScale.x * RockScaleRatio, RockScale.y * RockScaleRatio, 1 });
		}

		//UpperLayerChain
		{
			std::shared_ptr<class GameEngineSpriteRenderer> UpperLayerChain1 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			UpperLayerChain1->SetScaleToTexture("UpperLayerChain.png");
			UpperLayerChain1->GetTransform()->SetWorldPosition({ -1150, -250, -250 });
			UpperLayerChain1->GetTransform()->SetWorldRotation({ 0, 0, -15 });

			std::shared_ptr<class GameEngineSpriteRenderer> UpperLayerChain2 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			UpperLayerChain2->SetScaleToTexture("UpperLayerChain.png");
			UpperLayerChain2->GetTransform()->SetWorldPosition({ -876, -275, -200 });
			UpperLayerChain2->GetTransform()->SetWorldRotation({ 0, 0, 45 });

			std::shared_ptr<class GameEngineSpriteRenderer> UpperLayerChain3 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			UpperLayerChain3->SetScaleToTexture("UpperLayerChain.png");
			UpperLayerChain3->GetTransform()->SetWorldPosition({ -100, -250, -250 });
			UpperLayerChain3->GetTransform()->SetWorldRotation({ 0, 0, -15 });

			std::shared_ptr<class GameEngineSpriteRenderer> UpperLayerChain4 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			UpperLayerChain4->SetScaleToTexture("UpperLayerChain.png");
			UpperLayerChain4->GetTransform()->SetWorldPosition({ 1354, -250, -250 });
			UpperLayerChain4->GetTransform()->SetWorldRotation({ 0, 0, -15 });

			std::shared_ptr<class GameEngineSpriteRenderer> UpperLayerChain5 = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::UpperLayer);

			UpperLayerChain5->SetScaleToTexture("UpperLayerChain.png");
			UpperLayerChain5->GetTransform()->SetWorldPosition({ 1930, -250, -200 });
			UpperLayerChain5->GetTransform()->SetWorldRotation({ 0, 0, -30 });
		}

	}

	//MainLayer (플레이어 이펙트 맵 등)
	{
		MainRoomImage = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Map);
		MainRoomImage->SetTexture("HollowKnightBossRoomMain.png");

		MainRoomImage->GetTransform()->SetLocalScale({ 5000, 1500 });
		MainRoomImage->GetTransform()->SetLocalPosition({ 0, 0, -70 }); //원본 크기 기준 z -> -70.0f
	}


}

void HollowKnightBossRoom::Update(float _Delta)
{

}