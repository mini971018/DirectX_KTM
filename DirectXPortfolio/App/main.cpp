#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>

#pragma comment(lib, "GameEngineBase.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	std::string Str = "aaaaa bbbbb ccccc";
	GameEngineSerializer Data;
	Data.Write(Str);

	GameEngineFile NewFile = GameEngineFile("D:\\AAAA.txt");
	NewFile.Save(Data);
	
}

