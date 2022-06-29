#pragma once
#include <GameEngineActor.h>

class GameEngineRenderer;
class LobbyHost : public GameEngineActor
{
private:
	static bool curhostready_;

public:
	static void SetCurHostReady(bool _Flag);
	static bool SetCurHostReady();

private:	// member Var
	GameEngineRenderer* hostnationSpriteRender_;
	GameEngineRenderer* hostreadystateSpriteRender_;
	std::string hostName_;

public:
	LobbyHost(); // default constructer 디폴트 생성자
	~LobbyHost(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyHost(const LobbyHost& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyHost(LobbyHost&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyHost& operator=(const LobbyHost& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyHost& operator=(const LobbyHost&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

