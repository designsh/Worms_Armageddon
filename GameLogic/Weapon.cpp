#include "Weapon.h"

Weapon::Weapon() :
	weapontype_(eItemList::MAX),
	remaincnt_(-1),
	active_(false)
{
}

Weapon::~Weapon() // default destructer 디폴트 소멸자
{

}

void Weapon::SetItemSpec(const std::string& _Name, eItemList _ItemType, int _Cnt, bool _Active)
{
	// 해당 아이템의 초기속성 설정
	weaponname_ = _Name;
	weapontype_ = _ItemType;
	remaincnt_ = _Cnt;
	active_ = _Active;
}

void Weapon::WeaponUse()
{
	// 해당 아이템의 남은개수를 체크
	if (0 >= remaincnt_)
	{
		active_ = false;
		remaincnt_ = 0;
		return;
	}

	remaincnt_ -= 1;
}

void Weapon::WeaponAdd()
{
	// 현재 카운트 증가
	remaincnt_ += 1;
}

std::string Weapon::GetWeaponName() const
{
	return weaponname_;
}

eItemList Weapon::GetWeaponType() const
{
	return weapontype_;
}

int Weapon::GetWeaponRemainCount() const
{
	return remaincnt_;
}

bool Weapon::GetWeaponActive() const
{
	return active_;
}

