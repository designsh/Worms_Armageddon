#pragma once
#include <Windows.h>
// #include <chrono>

// 분류 :
// 용도 :
// 설명 :
class GameEngineTime
{

private:
	static GameEngineTime* Inst;

public:
	static GameEngineTime& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:
	LARGE_INTEGER timeCount_;
	LARGE_INTEGER startCheck_;
	LARGE_INTEGER endCheck_;
	float deltaTime_;
	float Second_;
	int F_;
	int FPS_;

public:
	// 여기에 이렇게 헤더에 구현한 이유
	// 리턴하는게 기본자료형이어서

	int GetFPS()
	{
		return FPS_;
	}

	float GetDeltaTime()
	{
		return deltaTime_;
	}
public:
	GameEngineTime(); // default constructer 디폴트 생성자
	~GameEngineTime(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineTime(const GameEngineTime& _Other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineTime(const GameEngineTime&& _Other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineTime& operator=(const GameEngineTime&& _Other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	void TimeCheckReset();
	void TimeCheck();
};

