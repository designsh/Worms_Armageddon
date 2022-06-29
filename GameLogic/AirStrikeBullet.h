#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineSoundPlayer.h>

#include "WeaponBase.h"

class GameEngineRenderer;
class AirStrikeBullet : public WeaponBase
{
public:
	AirStrikeBullet();
	~AirStrikeBullet();

	AirStrikeBullet(const AirStrikeBullet& _other) = delete; // default Copy constructer ����Ʈ ���������
	AirStrikeBullet(AirStrikeBullet&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

	AirStrikeBullet& operator=(const AirStrikeBullet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	AirStrikeBullet& operator=(const AirStrikeBullet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

	bool bLeft_;
	bool bGround_;
	bool bBackJump_;

	float degree_;
	float deltaTime_;
};

