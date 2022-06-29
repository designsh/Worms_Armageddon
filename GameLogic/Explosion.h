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
	Explosion(); // default constructer ����Ʈ ������
	~Explosion(); // default destructer ����Ʈ �Ҹ���
protected:		// delete constructer
	Explosion(const Explosion& _other) = delete; // default Copy constructer ����Ʈ ���������
	Explosion(Explosion&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
private:		//delete operator
	Explosion& operator=(const Explosion& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Explosion& operator=(const Explosion&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

	// DamageAll�� ������ ��� �÷��̾�� ������ ������� �������ΰ� Ȥ�� �������� �־����� ���� ������ ���ΰ�
	void SetDamage(int _Damage, bool _DamageToDist)
	{
		Damage_ = _Damage;
		DamageToDist_ = _DamageToDist;
	}
};

