#pragma once
#include "EffectCircle.h"
#include "EffectElipse.h"
#include "EffectSmklt.h"
#include "EffectSmkdrk.h"
#include "EffectFlame.h"

#include "Explosion.h"
// 분류 : 
// 용도 : 
// 설명 : 

class ExplosionSize25 : public Explosion
{
public:
	ExplosionSize25(); // default constructer 디폴트 생성자
	~ExplosionSize25(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	ExplosionSize25(const ExplosionSize25& _other) = delete; // default Copy constructer 디폴트 복사생성자
	ExplosionSize25(ExplosionSize25&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	ExplosionSize25& operator=(const ExplosionSize25& _other) = delete; // default Copy operator 디폴트 대입 연산자
	ExplosionSize25& operator=(const ExplosionSize25&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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
	ExplosionSize50(); // default constructer 디폴트 생성자
	~ExplosionSize50(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	ExplosionSize50(const ExplosionSize50& _other) = delete; // default Copy constructer 디폴트 복사생성자
	ExplosionSize50(ExplosionSize50&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	ExplosionSize50& operator=(const ExplosionSize50& _other) = delete; // default Copy operator 디폴트 대입 연산자
	ExplosionSize50& operator=(const ExplosionSize50&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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
	ExplosionSize75(); // default constructer 디폴트 생성자
	~ExplosionSize75(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	ExplosionSize75(const ExplosionSize75& _other) = delete; // default Copy constructer 디폴트 복사생성자
	ExplosionSize75(ExplosionSize75&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	ExplosionSize75& operator=(const ExplosionSize75& _other) = delete; // default Copy operator 디폴트 대입 연산자
	ExplosionSize75& operator=(const ExplosionSize75&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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
	ExplosionSize100(); // default constructer 디폴트 생성자
	~ExplosionSize100(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	ExplosionSize100(const ExplosionSize100& _other) = delete; // default Copy constructer 디폴트 복사생성자
	ExplosionSize100(ExplosionSize100&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	ExplosionSize100& operator=(const ExplosionSize100& _other) = delete; // default Copy operator 디폴트 대입 연산자
	ExplosionSize100& operator=(const ExplosionSize100&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() final;
	virtual void UpdateBefore() final;
	virtual void Update() final;
	virtual void UpdateAfter() final;
	virtual void Render() final;
};


