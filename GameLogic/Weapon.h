#pragma once
#include <string>
#include "eItemList.h"

// 분류 : 무기 정리
// 용도 : 
// 설명 : 
class Weapon
{
private:	// member Var
	std::string weaponname_;	// 무기 이름
	eItemList weapontype_;			// 무기 타입
	int remaincnt_;				// 무기 남은갯수
	bool active_;					// 무기 활성화/비활성화여부

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

