
#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineSoundPlayer.h>
#include "WeaponBase.h"

class GameEngineCollision;
class GameEngineRenderer;
class Worm;
class Girder : public WeaponBase
{
public:
	Girder();
	~Girder();

	Girder(const Girder& _other) = delete;
	Girder(Girder&& _other) = delete;

	Girder& operator=(const Girder& _other) = delete;
	Girder& operator=(const Girder&& _other) = delete;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void Initialize(Worm* _parentWorm, bool _bLeft);

private:
	Worm* parentWorm_;
	class MouseObject* mouse_;
	GameEngineRenderer* mainRender_[20];
	GameEngineRenderer* ColRender_[20];
	bool bLeft_;
	int index_;

	GameEngineSoundPlayer soundWhoosh_;
};

