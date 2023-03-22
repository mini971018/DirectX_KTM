#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
class TestLevel3D : public GameEngineLevel
{
public:
	// constrcuter destructer
	TestLevel3D();
	~TestLevel3D();

	// delete Function
	TestLevel3D(const TestLevel3D& _Other) = delete;
	TestLevel3D(TestLevel3D&& _Other) noexcept = delete;
	TestLevel3D& operator=(const TestLevel3D& _Other) = delete;
	TestLevel3D& operator=(TestLevel3D&& _Other) noexcept = delete;

protected:
	void Loading() override;

private:

};

