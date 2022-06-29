
#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

#include "WeaponBase.h"

class Worm;
class GameEngineRenderer;
class FirePunch : public WeaponBase
{
public:
	FirePunch(); // default constructer ����Ʈ ������
	~FirePunch(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	FirePunch(const FirePunch& _other) = delete; // default Copy constructer ����Ʈ ���������
	FirePunch(FirePunch&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	FirePunch& operator=(const FirePunch& _other) = delete; // default Copy operator ����Ʈ ���� ������
	FirePunch& operator=(const FirePunch&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	Worm* parent_;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* checkCollision_;

	float deltaTime_;
};

