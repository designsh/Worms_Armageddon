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
	TimerDigit(); // default constructer 디폴트 생성자
	~TimerDigit(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	TimerDigit(const TimerDigit& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TimerDigit(TimerDigit&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	TimerDigit& operator=(const TimerDigit& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TimerDigit& operator=(const TimerDigit&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

