#include "TestObject1.h"
#include <GameEnginePlatform/GameEngineWindow.h>

TestObject1::TestObject1() 
{
}

TestObject1::~TestObject1() 
{
}

float Angle = 0.0f;

void TestObject1::Render(float _DeltaTime)
{
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	float4 Pos = GameEngineWindow::GetScreenSize().half();
	const int VertexCount = 4;
	const int VertexLength = 150;

	Angle -= _DeltaTime * 360.0f;

	float4 VertexArray[VertexCount] =
	{
		{-VertexLength / 2, -VertexLength / 2},
		{ VertexLength / 2, -VertexLength / 2},
		{ VertexLength / 2, VertexLength / 2},
		{-VertexLength / 2, VertexLength / 2 }
	};

	POINT ArrPoint[VertexCount];

	for (size_t i = 0; i < VertexCount; ++i)
	{
		VertexArray[i].RotaitonZDeg(Angle); // Z축 회전
		VertexArray[i] += Pos;

		////순서 바뀌면 가운데로 이동하는 벡터도 포함되어 회전해서 주변을 도는것처럼 보인다.
		//VertexArray[i] += Pos;
		//VertexArray[i].RotaitonZDeg(Angle); // Z축 회전


		ArrPoint[i] = VertexArray[i].ToWindowPOINT();
	}

	Polygon(Dc, ArrPoint, VertexCount);
}