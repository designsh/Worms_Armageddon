#pragma once
#include <GameEngineActor.h>
#include <GameEngineMath.h>
// 분류 : 
// 용도 : 
// 설명 : 

class LobbyScatter : public GameEngineActor
{

private:	// member Var
	GameEngineRenderer* mainRender_;

private:
	float4 spawnPos_;
	GameEngineMath::Random randomGenerator_;

	float windSpeed_;
	float fallSpeed_;

public:
	LobbyScatter(); // default constructer 디폴트 생성자
	~LobbyScatter(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyScatter(const LobbyScatter& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyScatter(LobbyScatter&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyScatter& operator=(const LobbyScatter& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyScatter& operator=(const LobbyScatter&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

