#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 보스 방 안 오브젝트인 주황색 구조물 생성하는 액터
class HollowKnightBossOrangeBlob : public GameEngineActor
{
public:
	// constrcuter destructer
	HollowKnightBossOrangeBlob();
	~HollowKnightBossOrangeBlob();

	// delete Function
	HollowKnightBossOrangeBlob(const HollowKnightBossOrangeBlob& _Other) = delete;
	HollowKnightBossOrangeBlob(HollowKnightBossOrangeBlob&& _Other) noexcept = delete;
	HollowKnightBossOrangeBlob& operator=(const HollowKnightBossOrangeBlob& _Other) = delete;
	HollowKnightBossOrangeBlob& operator=(HollowKnightBossOrangeBlob&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> CreateBlobActor(OrangeBlobType _Type);

protected:

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BlobRenderer;
};

