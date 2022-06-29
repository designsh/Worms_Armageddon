#pragma once
#include "EffectActor.h"
#include "GameEngineMath.h"

class Explosion : public GameEngineActor
{

protected:	// member Var
	GameEngineCollision* ExplosionCollision_;
	int Damage_;
	bool DamageToDist_;

	bool Life_;

public:
	Explosion(); // default constructer 디폴트 생성자
	~Explosion(); // default destructer 디폴트 소멸자
protected:		// delete constructer
	Explosion(const Explosion& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Explosion(Explosion&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
private:		//delete operator
	Explosion& operator=(const Explosion& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Explosion& operator=(const Explosion&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

	// DamageAll은 범위내 모든 플레이어에게 동일한 대미지를 입힐것인가 혹은 범위에서 멀어짐에 따라 감소할 것인가
	void SetDamage(int _Damage, bool _DamageToDist)
	{
		Damage_ = _Damage;
		DamageToDist_ = _DamageToDist;
	}
};

