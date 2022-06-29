#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRendererManager
{
private:	// member Var

public:
	GameEngineRendererManager(); // default constructer 디폴트 생성자
	~GameEngineRendererManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRendererManager(const GameEngineRendererManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRendererManager(GameEngineRendererManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRendererManager& operator=(const GameEngineRendererManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRendererManager& operator=(const GameEngineRendererManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

