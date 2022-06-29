#pragma once
#include <vector>
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineCollision;
class LobbySelectMapImage : public GameEngineActor
{
private:
	int curmapimage_;

private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

private:
	std::vector<std::string> mapimagenamelist_;

public:
	LobbySelectMapImage(); // default constructer 디폴트 생성자
	~LobbySelectMapImage(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbySelectMapImage(const LobbySelectMapImage& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbySelectMapImage(LobbySelectMapImage&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbySelectMapImage& operator=(const LobbySelectMapImage& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbySelectMapImage& operator=(const LobbySelectMapImage&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void CreateSelMapImageNameList(const std::vector<std::string>& _NameList);
	void SetCurMapIndex(int _Index);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

