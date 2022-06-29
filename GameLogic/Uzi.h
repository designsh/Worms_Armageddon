#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineMath.h>
#include "WeaponBase.h"
// �з� : 
// �뵵 : 
// ���� : 
class Worm;
class UziBullet;
class Uzi : public WeaponBase
{
private:	// member Var
	std::vector<UziBullet*> bulletList_;

	UziBullet* curBullet_;
	const int CAPACITY = 25;
	int curShot_;

	friend UziBullet;

public:
	Uzi(); // default constructer ����Ʈ ������
	~Uzi(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Uzi(const Uzi& _other) = delete; // default Copy constructer ����Ʈ ���������
	Uzi(Uzi&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Uzi& operator=(const Uzi& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Uzi& operator=(const Uzi&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* fireCollision_;
	float4 direction_;
	float4 scanPos_;
	float4 parentForward_;

	bool bLeft_;
	bool bGround_;
	bool bBackJump_;

	float degree_;
	float deltaTime_;

public:
	void SetUziBulletShotBox(float4 _forward)
	{
		parentForward_ = _forward;
	}

	void SetParentWorm(Worm* _worm)
	{
		parentWorm_ = _worm;
	}

};

