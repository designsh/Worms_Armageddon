#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyTernTimeSet : public GameEngineActor
{
private:	// member Var
	int ImageIndex_;
	int PrevInfinityRandom_;
	bool MouseOver_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbyTernTimeSet(); // default constructer 디폴트 생성자
	~LobbyTernTimeSet(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyTernTimeSet(const LobbyTernTimeSet& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyTernTimeSet(LobbyTernTimeSet&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyTernTimeSet& operator=(const LobbyTernTimeSet& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyTernTimeSet& operator=(const LobbyTernTimeSet&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

