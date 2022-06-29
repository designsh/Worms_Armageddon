#include "Weapon.h"

Weapon::Weapon() :
	weapontype_(eItemList::MAX),
	remaincnt_(-1),
	active_(false)
{
}

Weapon::~Weapon() // default destructer ����Ʈ �Ҹ���
{

}

void Weapon::SetItemSpec(const std::string& _Name, eItemList _ItemType, int _Cnt, bool _Active)
{
	// �ش� �������� �ʱ�Ӽ� ����
	weaponname_ = _Name;
	weapontype_ = _ItemType;
	remaincnt_ = _Cnt;
	active_ = _Active;
}

void Weapon::WeaponUse()
{
	// �ش� �������� ���������� üũ
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
	// ���� ī��Ʈ ����
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

