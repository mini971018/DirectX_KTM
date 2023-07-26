#include "PrecompileHeader.h"

#include "TestObject1.h"
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

TestObject1::TestObject1() 
{
}

TestObject1::~TestObject1() 
{
}

void TestObject1::Start()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");

	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".avi", });

	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineVideo::Load(File[i].GetFullPath());
	}

	std::shared_ptr<GameEngineVideo> Video = GameEngineVideo::Find("Ending-1_-The-Hollow-Knight-FinalA.avi");
	Video->Play();
}

void TestObject1::Render(float _DeltaTime)
{
	//HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	//float4 Pos = GameEngineWindow::GetScreenSize().half();
	//const int VertexCount = 4;
	//const int VertexLength = 150;

	//Angle -= _DeltaTime * 360.0f;

	//float4 VertexArray[VertexCount] =
	//{
	//	{-VertexLength / 2, -VertexLength / 2},
	//	{ VertexLength / 2, -VertexLength / 2},
	//	{ VertexLength / 2, VertexLength / 2},
	//	{-VertexLength / 2, VertexLength / 2 }
	//};

	//POINT ArrPoint[VertexCount];

	//for (size_t i = 0; i < VertexCount; ++i)
	//{
	//	VertexArray[i].RotaitonZDeg(Angle); // Z�� ȸ��
	//	VertexArray[i] += Pos;

	//	////���� �ٲ�� ����� �̵��ϴ� ���͵� ���ԵǾ� ȸ���ؼ� �ֺ��� ���°�ó�� ���δ�.
	//	//VertexArray[i] += Pos;
	//	//VertexArray[i].RotaitonZDeg(Angle); // Z�� ȸ��


	//	ArrPoint[i] = VertexArray[i].ToWindowPOINT();
	//}

	//Polygon(Dc, ArrPoint, VertexCount);
}