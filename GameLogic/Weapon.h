#pragma once
#include <string>
#include "eItemList.h"

// �з� : ���� ����
// �뵵 : 
// ���� : 
class Weapon
{
private:	// member Var
	std::string weaponname_;	// ���� �̸�
	eItemList weapontype_;			// ���� Ÿ��
	int remaincnt_;				// ���� ��������
	bool active_;					// ���� Ȱ��ȭ/��Ȱ��ȭ����

public:
	Weapon();
	~Weapon();

public:
	void SetItemSpec(const std::string& _Name, eItemList _ItemType, int _Cnt, bool _Active);
	void WeaponUse();
	void WeaponAdd();

public:
	std::string GetWeaponName() const;
	eItemList GetWeaponType() const;
	int GetWeaponRemainCount() const;
	bool GetWeaponActive() const;
};

