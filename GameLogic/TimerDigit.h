#pragma once
#include <GameEngineActor.h>

class Worm;
class TimerManager;
class TimerDigit : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	TimerManager* timerManager_;
	Worm* parent_;
	float curCount_;

	bool isWormLinked_;

public:
	TimerDigit(); // default constructer ����Ʈ ������
	~TimerDigit(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	TimerDigit(const TimerDigit& _other) = delete; // default Copy constructer ����Ʈ ���������
	TimerDigit(TimerDigit&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TimerDigit& operator=(const TimerDigit& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TimerDigit& operator=(const TimerDigit&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void AnimationInit();
	float GetCurTime();

public:
	void SetParentWorm(Worm* _worm)
	{
		parent_ = _worm;
		isWormLinked_ = true;
	}
public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void SetNumber(int _number);
	void SetTenDigitTime(float _time);
	void SetDigitTime(float _time);
};

