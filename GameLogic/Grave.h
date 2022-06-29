#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
// 분류 : 
// 용도 : 
// 설명 : 
class Grave : public GameEngineActor
{
private:	// member Var

	GameEngineRenderer* mainSpriteRender_;

	GameEngineCollision* HeadCollision_; // ajfl
	GameEngineCollision* groundCollision_; // 바닥

	GameEngineFSM<Grave> state_;

	float deltaTime_;

	float GravityAcc_;
	float GravitySpeed_;
	float GravityMove_;
	int bound_;

public:
	Grave(); // default constructer 디폴트 생성자
	~Grave(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Grave(const Grave& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Grave(Grave&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	Grave& operator=(const Grave& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Grave& operator=(const Grave&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	StateInfo StartAir(StateInfo);
	StateInfo StartGround(StateInfo);

	StateInfo UpdateAir(StateInfo);
	StateInfo UpdateGround(StateInfo);

private:
	void initCollision();
public:
};

