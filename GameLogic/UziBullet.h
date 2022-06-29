#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineMath.h>
#include "WeaponBase.h"

class Uzi;
class GameEngineRenderer;
class Worm;
class UziBullet : public GameEngineActor
{
public:


public:
	UziBullet(); // default constructer ����Ʈ ������
	~UziBullet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	UziBullet(const UziBullet& _other) = delete; // default Copy constructer ����Ʈ ���������
	UziBullet(UziBullet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	UziBullet& operator=(const UziBullet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UziBullet& operator=(const UziBullet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	const int CAPACITY = 25;
	GameEngineMath::Random randomGenerator_;
	bool isFlying_;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* fireCollision_;
	Uzi* parentUzi_;
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

	void SetParentUzi(Uzi* _uzi)
	{
		parentUzi_ = _uzi;
	}

	void StartFly()
	{
		isFlying_ = true;
	}
};

