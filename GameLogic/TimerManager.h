#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class TimerManager
{
private:	// member Var

public:
	TimerManager(); // default constructer 디폴트 생성자
	~TimerManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	TimerManager(const TimerManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TimerManager(TimerManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	TimerManager& operator=(const TimerManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TimerManager& operator=(const TimerManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

