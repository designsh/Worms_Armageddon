#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class DrumActor : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;
	GameEngineCollision* BodyCollision_; // ����
	GameEngineCollision* groundCollision_; // �ٴ�

	const float PetroleumSpeed;

	float Phase_; // �巳���� ������ ����, Max = 3.f
	float deltaTime_;
	float WindSpeed_;
	float degree_;
	GameEngineMath::Random random_;

	// �������� ����, Ȥ�� ȭ���� �����ð� ����Ǿ��� ���
	// Phase_ ��ġ�� ���� �巳���� ���ϸ��̼�(������ ����)�� ����ǰ�,
	// ���� �̻��� �Ǹ� ����

public:
	DrumActor(); // default constructer ����Ʈ ������
	~DrumActor(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	DrumActor(const DrumActor& _other) = delete; // default Copy constructer ����Ʈ ���������
	DrumActor(DrumActor&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	DrumActor& operator=(const DrumActor& _other) = delete; // default Copy operator ����Ʈ ���� ������
	DrumActor& operator=(const DrumActor&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	void initCollision();

public:
	void DrumExplode();
};

