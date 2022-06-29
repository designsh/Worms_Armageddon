#pragma once
#include <map>
#include <vector>
#include <GameEngineActor.h>

#include "eItemList.h"

class Worm;
class WeaponSheet;
class BottomStateUI;
class WormTopStateUI;
class TimerBlankWindow;
class TimerDigit;
class Weapon;
class WormName;
class WormArrow;
class WormHPNumber;
class WormHPBlankWindow;
class UIController : public GameEngineActor
{
private:	// member Var
	Worm* curplayer_;	// 현재 해당 제어관리자를 사용하는 객체

private:	// 관리하는 모든 UI
	// Weapon Sheet 관련
	WeaponSheet* weaponsheet_;

	// 화면하단 웜 스테이터스 관련
	BottomStateUI* bottomstate_;

	// 플레이어상단 웜 스테이터스 관련
	WormTopStateUI* wormtopstate_;

	// 플레이어 턴타임 관련
	TimerBlankWindow* curTimerWindow_;
	TimerDigit* curTimerDigitTen_;
	TimerDigit* curTimerDigit_;

public:
	UIController(); // default constructer 디폴트 생성자
	~UIController(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	UIController(const UIController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	UIController(UIController&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	UIController& operator=(const UIController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	UIController& operator=(const UIController&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public: // 플레이어가 객체 생성시 반드시 설정해야하는 항목
	void SetCurPlayer(Worm* _curplayer);																	// 플레이어설정
	void CreateWeaponList(const std::vector<eItemList>& _weaponlist);			// 가지고있는 무기목록설정(최초설정시)
	
public: // 플레이어가 기믹오브젝트 획득 또는 아이템사용시 설정해야하는 항목
	void AddWeapon(eItemList _Weapon);																// 기믹오브젝트에 의해 무기를 획득했을때
	void UseWeapon(eItemList _Weapon);																// 무기를 사용했을때

public:
	Worm* GetCurPlayer() const;
	WeaponSheet* GetCurWeaponSheet() const;

public:
	BottomStateUI* GetCurBottomState() const;

public:
	WormTopStateUI* GetCurTopState() const;

public:
	TimerBlankWindow* GetCurTimerWindow();
	TimerDigit* GetCurTimerDigitTen();
	TimerDigit* GetCurTimerDigit();

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void CurWormUIControllerDeath();
};

