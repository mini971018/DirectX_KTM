#include "TestLevel3D.h"

#include "PrecompileHeader.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "TestObject1.h"


TestLevel3D::TestLevel3D() 
{
}

TestLevel3D::~TestLevel3D() 
{
}

void TestLevel3D::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	std::shared_ptr<TestObject1> TestObject = CreateActor<TestObject1>();

}

