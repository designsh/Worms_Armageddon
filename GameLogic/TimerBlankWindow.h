#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class Worm;
class TimerBlankWindow : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	Worm* parent_;
	bool isWormLinked_;

public:
	TimerBlankWindow(); // default constructer 디폴트 생성자
	~TimerBlankWindow(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	TimerBlankWindow(const TimerBlankWindow& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TimerBlankWindow(TimerBlankWindow&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	TimerBlankWindow& operator=(const TimerBlankWindow& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TimerBlankWindow& operator=(const TimerBlankWindow&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void RenderColorInit(int _wormNumber);
	void SetParentWorm(Worm* _worm)
	{
		parent_ = _worm;
		isWormLinked_ = true;
	}
};

