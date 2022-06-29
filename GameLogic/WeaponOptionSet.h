#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class WeaponOptionSet : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	WeaponOptionSet(); // default constructer ����Ʈ ������
	~WeaponOptionSet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WeaponOptionSet(const WeaponOptionSet& _other) = delete; // default Copy constructer ����Ʈ ���������
	WeaponOptionSet(WeaponOptionSet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WeaponOptionSet& operator=(const WeaponOptionSet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WeaponOptionSet& operator=(const WeaponOptionSet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

