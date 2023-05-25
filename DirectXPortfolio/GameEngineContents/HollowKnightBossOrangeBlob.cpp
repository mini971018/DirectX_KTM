#include "PrecompileHeader.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "HollowKnightBossOrangeBlob.h"

HollowKnightBossOrangeBlob::HollowKnightBossOrangeBlob() 
{
}

HollowKnightBossOrangeBlob::~HollowKnightBossOrangeBlob() 
{
}

std::shared_ptr<class GameEngineSpriteRenderer> HollowKnightBossOrangeBlob::CreateBlobActor(OrangeBlobType _Type)
{
	if (nullptr == GameEngineSprite::Find("LargeBlob01"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("HollowKnight");
		NewDir.Move("Blob");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LargeBlob01").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LargeBlob02").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LargeBlob03").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallBlob01").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallBlob02").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallBlob03").GetFullPath());
	}

	BlobRenderer = CreateComponent<GameEngineSpriteRenderer>(PlayRenderOrder::Background);
	std::string_view SpriteString;

	switch (_Type)
	{
	case OrangeBlobType::LargeBlob01:
		SpriteString = "LargeBlob01";
		break;
	case OrangeBlobType::LargeBlob02:
		SpriteString = "LargeBlob02";
		break;
	case OrangeBlobType::LargeBlob03:
		SpriteString = "LargeBlob03";
		break;
	case OrangeBlobType::SmallBlob01:
		SpriteString = "SmallBlob01";
		break;
	case OrangeBlobType::SmallBlob02:
		SpriteString = "SmallBlob02";
		break;
	case OrangeBlobType::SmallBlob03:
		SpriteString = "SmallBlob03";
		break;
	default:
		break;
	}

	BlobRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = SpriteString, .ScaleToTexture = true});
	BlobRenderer->ChangeAnimation("Idle");

	return BlobRenderer;
}
