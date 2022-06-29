#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyImage : public GameEngineActor
{
private:
	bool hostready_;
	bool mouseover_;

private:	// member Var
	GameEngineRenderer* backdropSpriteRender_;

private:
	GameEngineRenderer* hostboxSpriteRender_;	// host(컴퓨터명)
	GameEngineRenderer* hostreadySpriteRender_;	// host ready button

private:
	GameEngineCollision* hostreadyCollision_;

public:
	LobbyImage(); // default constructer 디폴트 생성자
	~LobbyImage(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyImage(const LobbyImage& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyImage(LobbyImage&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyImage& operator=(const LobbyImage& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyImage& operator=(const LobbyImage&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

