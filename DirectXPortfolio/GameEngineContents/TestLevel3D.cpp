#include "TestLevel3D.h"
#include "TestObject1.h"

TestLevel3D::TestLevel3D() 
{
}

TestLevel3D::~TestLevel3D() 
{
}

void TestLevel3D::Start()
{
	std::shared_ptr<TestObject1> TestObject = CreateActor<TestObject1>();


}

