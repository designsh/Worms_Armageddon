#include "WeaponBase.h"

WeaponBase::WeaponBase() // default constructer 디폴트 생성자
{

}

WeaponBase::~WeaponBase() // default destructer 디폴트 소멸자
{

}

void WeaponBase::SetParentWorm(Worm* _parentWorm)
{
	parentWorm_ = _parentWorm;
}

