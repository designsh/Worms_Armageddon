#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineRenderer;
class GameEngineCollision;
class GameEngineSoundPlayer;
class TestActor : public GameEngineActor
{
public:
	TestActor(); 
	~TestActor();

	TestActor(const TestActor& _other) = delete; 
	TestActor(TestActor&& _other) = delete; 

	TestActor& operator=(const TestActor& _other) = delete;
	TestActor& operator=(const TestActor&& _other) = delete;

	// GameEngineActor을(를) 통해 상속됨
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

protected:
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);

	StateInfo startTest(StateInfo _state);
	StateInfo updateTest(StateInfo _state);
private:
	GameEngineFSM<TestActor>	state_;
	GameEngineRenderer*			mainRenderer_;
	GameEngineCollision*		bodyCollision_;
	GameEngineSoundPlayer*		testSoundPlayer_;
};

