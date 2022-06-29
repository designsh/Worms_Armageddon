#pragma once
#include <GameEngineActor.h>
#include "eItemList.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class WeaponSheet;
class WeaponIcon : public GameEngineActor
{
private: // 본인이 속한 WeaponSheet
	WeaponSheet* parentsheet_;

private:
	int indexX_;
	int indexY_;

private:
	bool active_;
	bool prevstate_;

private:	// member Var
	std::string weaponname_;
	eItemList weapontype_;

private:
	float4 activetargetpos_;
	float4 disabletargetpos_;

private:
	bool moving_;
	float movingspeed;
	float4 movepos_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineRenderer* selectrenderer_;
	GameEngineCollision* maincollision_;

public:
	WeaponIcon(); // default constructer 디폴트 생성자
	~WeaponIcon(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WeaponIcon(const WeaponIcon& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WeaponIcon(WeaponIcon&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WeaponIcon& operator=(const WeaponIcon& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WeaponIcon& operator=(const WeaponIcon&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SetWeaponName(const std::string& _Name);
	void SetWeaponType(eItemList _Type);
	void SetWeaponRenderPos(const float4& _DisableRenderPos, const float4& _ActiveRenderPos);
	void SetWeaponIndex(int _X, int _Y);

public:
	GameEngineCollision* GetCurIconCol() const;
	eItemList GetWeaponType() const;
	const std::string& GetWeaponName() const;
	WeaponSheet* GetParentSheet() const;

public:
	void SetParentSheet(WeaponSheet* _Sheet);
	void SetActive(bool _Active);
	void SelWeapon();
	void SetMainRendererOn();
	void SetMainRendererOff();
	
public: // 아이템아이콘활성화여부체크
	bool IsMainrendererOn();

public: // 턴시간 초과 및 강제 턴전환으로 인한 비활성화
	void SetTernTimeOff();

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

