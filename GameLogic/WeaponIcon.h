#pragma once
#include <GameEngineActor.h>
#include "eItemList.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class WeaponSheet;
class WeaponIcon : public GameEngineActor
{
private: // ������ ���� WeaponSheet
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
	WeaponIcon(); // default constructer ����Ʈ ������
	~WeaponIcon(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WeaponIcon(const WeaponIcon& _other) = delete; // default Copy constructer ����Ʈ ���������
	WeaponIcon(WeaponIcon&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WeaponIcon& operator=(const WeaponIcon& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WeaponIcon& operator=(const WeaponIcon&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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
	
public: // �����۾�����Ȱ��ȭ����üũ
	bool IsMainrendererOn();

public: // �Ͻð� �ʰ� �� ���� ����ȯ���� ���� ��Ȱ��ȭ
	void SetTernTimeOff();

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

