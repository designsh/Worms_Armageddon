
#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineSoundPlayer.h>

#include "WeaponBase.h"

class GameEngineRenderer;
class HomingMissile : public WeaponBase
{
public:
	HomingMissile();
	~HomingMissile();

	HomingMissile(const HomingMissile& _other) = delete; // default Copy constructer 디폴트 복사생성자
	HomingMissile(HomingMissile&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

	HomingMissile& operator=(const HomingMissile& _other) = delete; // default Copy operator 디폴트 대입 연산자
	HomingMissile& operator=(const HomingMissile&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	const float MOVE_SPEED = 100.f;
	const float GRAVITY_POWER = 600.f;
	const float BOTTOM_PIVOT = 14.f;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* groundCheckCollision_;

	float4 accelation_;
	float4 direction_;
	float4 speed_;
	float4 prevPos_;
	float4 startPos_;
	float4 homingPos_;
	float4 wormPos_;
	float4 rotPos_;
	float4 targetPos_;

	bool bLeft_;
	bool bGround_;
	bool bBackJump_;
	bool bHomingSound_;
	bool bExplosionWait_;

	float degree_;
	float deltaTime_;
	float launchTime_;
	float rotAngle_;
	float endTime_;
	float homingTime;
	float explosionDelay_;

	GameEngineSoundPlayer soundWhoosh_;

public:
	void SetPower(float4 _direction, float _firePower)
	{
		direction_ = _direction;
		speed_ = _direction * _firePower;
	}

	void SetHomingPoint(float4 _pos)
	{
		homingPos_ = _pos;
	}
};

