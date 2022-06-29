#pragma once
#include <GameEngineActor.h>
#include <GameEngineSoundPlayer.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class MenuSelImage : public GameEngineActor
{
private:
	bool menusel_;
	float alpha_;
	unsigned char castalpha_;

private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollider_;
	GameEngineCollision* curcollider_;

private:
	GameEngineRenderer* faderenderer_;
	GameEngineSoundPlayer colmousesound_;

public:
	MenuSelImage(); // default constructer 디폴트 생성자
	~MenuSelImage(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	MenuSelImage(const MenuSelImage& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MenuSelImage(MenuSelImage&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MenuSelImage& operator=(const MenuSelImage& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MenuSelImage& operator=(const MenuSelImage&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void ChangeLevel();
};

