#pragma once
#include <GameEngineLevel.h>
// 분류 : 
// 용도 : 
// 설명 : 
class LobbyLevel : public GameEngineLevel
{
private:	// member Var

public:
	LobbyLevel(); // default constructer 디폴트 생성자
	~LobbyLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyLevel(const LobbyLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyLevel(LobbyLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyLevel& operator=(const LobbyLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyLevel& operator=(const LobbyLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Loading() override;
	void LevelUpdate() override;

public:
	void Loading_SJH();
};

