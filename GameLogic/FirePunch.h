
#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

#include "WeaponBase.h"

class Worm;
class GameEngineRenderer;
class FirePunch : public WeaponBase
{
public:
	FirePunch(); // default constructer 디폴트 생성자
	~FirePunch(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	FirePunch(const FirePunch& _other) = delete; // default Copy constructer 디폴트 복사생성자
	FirePunch(FirePunch&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	FirePunch& operator=(const FirePunch& _other) = delete; // default Copy operator 디폴트 대입 연산자
	FirePunch& operator=(const FirePunch&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	Worm* parent_;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* checkCollision_;

	float deltaTime_;
};

