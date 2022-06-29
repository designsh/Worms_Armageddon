#pragma once
#include "EffectCircle.h"
#include "EffectElipse.h"
#include "EffectSmklt.h"
#include "EffectSmkdrk.h"
#include "EffectFlame.h"

#include "Explosion.h"
// �з� : 
// �뵵 : 
// ���� : 

class ExplosionSize25 : public Explosion
{
public:
	ExplosionSize25(); // default constructer ����Ʈ ������
	~ExplosionSize25(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	ExplosionSize25(const ExplosionSize25& _other) = delete; // default Copy constructer ����Ʈ ���������
	ExplosionSize25(ExplosionSize25&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	ExplosionSize25& operator=(const ExplosionSize25& _other) = delete; // default Copy operator ����Ʈ ���� ������
	ExplosionSize25& operator=(const ExplosionSize25&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() final;
	virtual void UpdateBefore() final;
	virtual void Update() final;
	virtual void UpdateAfter() final;
	virtual void Render() final;
};

//size 50

class ExplosionSize50 : public Explosion
{
public:
	ExplosionSize50(); // default constructer ����Ʈ ������
	~ExplosionSize50(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	ExplosionSize50(const ExplosionSize50& _other) = delete; // default Copy constructer ����Ʈ ���������
	ExplosionSize50(ExplosionSize50&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	ExplosionSize50& operator=(const ExplosionSize50& _other) = delete; // default Copy operator ����Ʈ ���� ������
	ExplosionSize50& operator=(const ExplosionSize50&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() final;
	virtual void UpdateBefore() final;
	virtual void Update() final;
	virtual void UpdateAfter() final;
	virtual void Render() final;
};

//size 75

class ExplosionSize75 : public Explosion
{
public:
	ExplosionSize75(); // default constructer ����Ʈ ������
	~ExplosionSize75(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	ExplosionSize75(const ExplosionSize75& _other) = delete; // default Copy constructer ����Ʈ ���������
	ExplosionSize75(ExplosionSize75&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	ExplosionSize75& operator=(const ExplosionSize75& _other) = delete; // default Copy operator ����Ʈ ���� ������
	ExplosionSize75& operator=(const ExplosionSize75&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() final;
	virtual void UpdateBefore() final;
	virtual void Update() final;
	virtual void UpdateAfter() final;
	virtual void Render() final;
};

//size 100

class ExplosionSize100 : public Explosion
{
public:
	ExplosionSize100(); // default constructer ����Ʈ ������
	~ExplosionSize100(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	ExplosionSize100(const ExplosionSize100& _other) = delete; // default Copy constructer ����Ʈ ���������
	ExplosionSize100(ExplosionSize100&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	ExplosionSize100& operator=(const ExplosionSize100& _other) = delete; // default Copy operator ����Ʈ ���� ������
	ExplosionSize100& operator=(const ExplosionSize100&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() final;
	virtual void UpdateBefore() final;
	virtual void Update() final;
	virtual void UpdateAfter() final;
	virtual void Render() final;
};


