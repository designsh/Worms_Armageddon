#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class BattleAxe
{
private:	// member Var

public:
	BattleAxe(); // default constructer 디폴트 생성자
	~BattleAxe(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	BattleAxe(const BattleAxe& _other) = delete; // default Copy constructer 디폴트 복사생성자
	BattleAxe(BattleAxe&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	BattleAxe& operator=(const BattleAxe& _other) = delete; // default Copy operator 디폴트 대입 연산자
	BattleAxe& operator=(const BattleAxe&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

