#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyTeleportinSet : public GameEngineActor
{
private:	// member Var
	int ImageIndex_;
	bool MouseOver_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbyTeleportinSet(); // default constructer 디폴트 생성자
	~LobbyTeleportinSet(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyTeleportinSet(const LobbyTeleportinSet& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyTeleportinSet(LobbyTeleportinSet&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyTeleportinSet& operator=(const LobbyTeleportinSet& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyTeleportinSet& operator=(const LobbyTeleportinSet&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

