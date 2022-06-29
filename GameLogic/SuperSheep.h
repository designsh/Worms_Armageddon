#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineSoundPlayer.h>
#include "WeaponBase.h"

class GameEngineCollision;
class GameEngineRenderer;
class Worm;
class SuperSheep : public WeaponBase
{
public:
	SuperSheep();
	~SuperSheep();

	SuperSheep(const SuperSheep& _other) = delete;
	SuperSheep(SuperSheep&& _other) = delete;

	SuperSheep& operator=(const SuperSheep& _other) = delete;
	SuperSheep& operator=(const SuperSheep&& _other) = delete;

public:
	// GameEngineActor을(를) 통해 상속됨
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void Initialize(Worm* _parentWorm, bool _bLeft);

private:
	void addGravity();
	void normalMove();

private:
	const float GRAVITY_POWER = 800.f;
	const float BOTTOM_PIVOT = 12.f;
	const float JUMP_DELAY = 1.0f;
	const float FLY_SPEED = 600.f;
	const float ANIM_DELAY = 0.05f;

private:
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);

	StateInfo startWalk(StateInfo _state);
	StateInfo updateWalk(StateInfo _state);

	StateInfo startFly(StateInfo _state);
	StateInfo updateFly(StateInfo _state);

	StateInfo startExplosion(StateInfo _state);
	StateInfo updateExplosion(StateInfo _state);

private:
	GameEngineFSM<SuperSheep> state_;
	GameEngineRenderer* mainRender_;

	float4 direction_;
	float4 speed_;
	float4 headPivot_;

	GameEngineCollision* topCenterCollision_;
	GameEngineCollision* headCollision_;
	GameEngineCollision* bottomCenterCollision_;
	GameEngineCollision* groundCheckCollision_;

	float deltaTime_;
	float EffectSpawnTime_;;
	float jumpDelay_;
	float explosionDelay_;
	float animDelay_;
	bool bLeft_;
	bool bGround_;

	GameEngineSoundPlayer soundWhoosh_;
};