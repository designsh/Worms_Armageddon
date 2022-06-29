#pragma once
#include <GameEngineLevel.h>

// 분류 : 
// 용도 : 
// 설명 : 
class MenuSelectLevel : public GameEngineLevel
{
private:	// member Var

public:
	MenuSelectLevel(); // default constructer 디폴트 생성자
	~MenuSelectLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	MenuSelectLevel(const MenuSelectLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MenuSelectLevel(MenuSelectLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MenuSelectLevel& operator=(const MenuSelectLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MenuSelectLevel& operator=(const MenuSelectLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Loading() override;
	void LevelUpdate() override;
};

