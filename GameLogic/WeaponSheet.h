#pragma once
#include <map>
#include <GameEngineActor.h>

#include "eItemList.h"

class GameEngineRenderer;
class GameEngineCollision;
class MouseObject;
class UIController;
class WeaponIcon;
class Weapon;
class WeaponSheet : public GameEngineActor
{
private:
	static bool weaponsheetactive_;

public:
	static bool isweaponsheet();

private:
	UIController* parentcontroller_;

private:
	bool active_;							// 현재 활성/비활성
	bool prevstate_;						// 이전 활성/비활성
	bool forceternoff_;				// 강제 턴전환 또는 시간초과로인한 턴전환

private:	// member Var
	GameEngineRenderer* mainrenderer;		// WeaponSheet(Temp) 렌더러
	
private: // 마우스충돌 관련
	MouseObject* mouseobject_;

private: // 무기아이콘 목록
	std::vector<std::string> weaponnamelist_;								// 무기이름(렌더러생성용)
	std::map<std::string, WeaponIcon*> weaponiconlist_;		// 무기아이콘목록(최초생성시 모두 Off상태)

private: // 실질적인 무기관리
	std::map<eItemList, Weapon*> weaponlist_;						// 실질적인무기관리목록
	
private:
	float4 activetargetpos_;
	float4 disabletargetpos_;

private:
	bool moving_;
	float movingspeed;
	float4 movepos_;

public:
	WeaponSheet(); // default constructer 디폴트 생성자
	~WeaponSheet(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WeaponSheet(const WeaponSheet& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WeaponSheet(WeaponSheet&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WeaponSheet& operator=(const WeaponSheet& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WeaponSheet& operator=(const WeaponSheet&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	bool IsActive()
	{
		if (active_ == true)
		{
			return true;
		}

		return false;
	}

	void WeaponSheetActive();
	void WeaponSheetTernOff();
	void SetRenderPos(const float4& _Active, const float4& _Disable);

public:
	UIController* GetParentController() const;

public:
	void SetParentController(UIController* _controller);
	void SetMouseObject();
	void SetIconName();
	void CreateIconDefaultPos();

public: // 플레이어가 들고있는 무기소유목록을 받아와서 무기아이콘목록생성(최초생성)
	void CreateWeaponIconList(const std::vector<eItemList>& _WeaponList);

public: // 플레이어가 기믹오브젝트 획득 또는 아이템사용시 설정해야하는 항목
	void AddWeapon(eItemList _Weapon);
	void UseWeapon(eItemList _Weapon);

public: // 실질적인 무기목록(관리용)관련
	Weapon* GetCurWeapon(eItemList _SearchWeapon);

public: // 멤버변수 Get
	float4 GetSheetActivePos();
	float4 GetSheetDisablePos();
};

