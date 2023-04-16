#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestObject1 : public GameEngineActor
{
public:
	// constrcuter destructer
	TestObject1();
	~TestObject1();

	// delete Function
	TestObject1(const TestObject1& _Other) = delete;
	TestObject1(TestObject1&& _Other) noexcept = delete;
	TestObject1& operator=(const TestObject1& _Other) = delete;
	TestObject1& operator=(TestObject1&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) {}
	void Render(float _Delta) override;

private:
	std::shared_ptr<class GameEngineRenderer> Render0;
	std::shared_ptr<class GameEngineRenderer> Render1;
	std::shared_ptr<class GameEngineRenderer> Render2;


};

