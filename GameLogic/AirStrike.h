#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineMath.h>
#include "WeaponBase.h"

class GameEngineRenderer;
class AirStrike : public WeaponBase
{
public:
	AirStrike();
	~AirStrike();

	AirStrike(const AirStrike& _other) = delete; // default Copy constructer 디폴트 복사생성자
	AirStrike(AirStrike&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

	AirStrike& operator=(const AirStrike& _other) = delete; // default Copy operator 디폴트 대입 연산자
	AirStrike& operator=(const AirStrike&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

	void SetAirStrike(bool _Left, float4 _Pos);

private:
	GameEngineRenderer* mainRender_;

	float4 direction_;
	float4 firePoint_;
	float deltaTime_;
	float destroyTime_;
	float fireTime_;
	bool fire_;
	int fireCount_;
};

