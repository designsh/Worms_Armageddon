#pragma once
#include "Worm.h"
#include <GameEngineActor.h>

class Worm;
class WeaponBase : public GameEngineActor
{
private:

public:
	WeaponBase();
	~WeaponBase();

	WeaponBase(const WeaponBase& _other) = delete;
	WeaponBase(WeaponBase&& _other) = delete;
		
	WeaponBase& operator=(const WeaponBase& _other) = delete;
	WeaponBase& operator=(const WeaponBase&& _other) = delete;

public:
	void SetParentWorm(Worm* _parentWorm);

protected:
	Worm* parentWorm_;
};

