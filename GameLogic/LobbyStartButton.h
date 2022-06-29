#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyStartButton : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

private:
	std::string GameStartText_;

private:
	bool mouseover_;

public:
	LobbyStartButton(); // default constructer 디폴트 생성자
	~LobbyStartButton(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyStartButton(const LobbyStartButton& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyStartButton(LobbyStartButton&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyStartButton& operator=(const LobbyStartButton& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyStartButton& operator=(const LobbyStartButton&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

