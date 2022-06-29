
#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineSoundPlayer.h>

#include "WeaponBase.h"

class GameEngineRenderer;
class Aim : public WeaponBase
{
public:
	Aim();
	~Aim();

	Aim(const Aim& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Aim(Aim&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

	Aim& operator=(const Aim& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Aim& operator=(const Aim&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

	void NextAimRender();
	void AimClear();

	void PowerEnd()
	{
		power_ = false;
	}

	void SetMaxTime(float _MaxTime)
	{
		maxTime_ = _MaxTime;
	}

	void SetAim(float _MaxTime, float4 _EndPos, float4 _Pos);
	void SetChildAim(float4 _Pos, int _ImageIndex);

private:
	std::vector<Aim*> childAim_;

	GameEngineRenderer* mainRender_;
	float4 startPos_;
	float4 endPos_;
	float4 nextPos_;
	bool power_;
	bool parentAim_;
	bool renderOn;
	float maxTime_;
	float tickTime_;
	float tickTimeBase_;
	float deltaTime_;
	int imageIndex_;
};

