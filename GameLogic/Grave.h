#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
// �з� : 
// �뵵 : 
// ���� : 
class Grave : public GameEngineActor
{
private:	// member Var

	GameEngineRenderer* mainSpriteRender_;

	GameEngineCollision* HeadCollision_; // ajfl
	GameEngineCollision* groundCollision_; // �ٴ�

	GameEngineFSM<Grave> state_;

	float deltaTime_;

	float GravityAcc_;
	float GravitySpeed_;
	float GravityMove_;
	int bound_;

public:
	Grave(); // default constructer ����Ʈ ������
	~Grave(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Grave(const Grave& _other) = delete; // default Copy constructer ����Ʈ ���������
	Grave(Grave&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	Grave& operator=(const Grave& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Grave& operator=(const Grave&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	StateInfo StartAir(StateInfo);
	StateInfo StartGround(StateInfo);

	StateInfo UpdateAir(StateInfo);
	StateInfo UpdateGround(StateInfo);

private:
	void initCollision();
public:
};

