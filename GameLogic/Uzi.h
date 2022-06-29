#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineMath.h>
#include "WeaponBase.h"
// 분류 : 
// 용도 : 
// 설명 : 
class Worm;
class UziBullet;
class Uzi : public WeaponBase
{
private:	// member Var
	std::vector<UziBullet*> bulletList_;

	UziBullet* curBullet_;
	const int CAPACITY = 25;
	int curShot_;

	friend UziBullet;

public:
	Uzi(); // default constructer 디폴트 생성자
	~Uzi(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Uzi(const Uzi& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Uzi(Uzi&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Uzi& operator=(const Uzi& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Uzi& operator=(const Uzi&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* fireCollision_;
	float4 direction_;
	float4 scanPos_;
	float4 parentForward_;

	bool bLeft_;
	bool bGround_;
	bool bBackJump_;

	float degree_;
	float deltaTime_;

public:
	void SetUziBulletShotBox(float4 _forward)
	{
		parentForward_ = _forward;
	}

	void SetParentWorm(Worm* _worm)
	{
		parentWorm_ = _worm;
	}

};

