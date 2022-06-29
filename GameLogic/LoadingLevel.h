#pragma once
#include <GameEngineLevel.h>
// 분류 : 
// 용도 : 
// 설명 : 
class LoadingLevel : public GameEngineLevel
{
private:	// member Var

public:
	LoadingLevel(); // default constructer 디폴트 생성자
	~LoadingLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LoadingLevel(const LoadingLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LoadingLevel(LoadingLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LoadingLevel& operator=(const LoadingLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LoadingLevel& operator=(const LoadingLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Loading() override;
	void LevelUpdate() override;
};

