#include "WeaponBase.h"

WeaponBase::WeaponBase() // default constructer ����Ʈ ������
{

}

WeaponBase::~WeaponBase() // default destructer ����Ʈ �Ҹ���
{

}

void WeaponBase::SetParentWorm(Worm* _parentWorm)
{
	parentWorm_ = _parentWorm;
}

