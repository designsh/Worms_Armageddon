#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class GameController;
class MouseObject : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineRenderer* mouseAimRenderer_;
	GameEngineCollision* maincollision_;
	GameController* gamecontroller_;

private:
	bool weaponsheeton_;
	bool mouseMoveBlock;

private:
	float4 finalpos_;	// 마우스의 마지막위치
	float4 startrange_;	// 마우스 이동제한범위 시작점
	float4 endrange_;		// 마우스 이동제한범위 끝점

private:
	float4 rendersize_;

public:
	MouseObject(); // default constructer 디폴트 생성자
	~MouseObject(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	MouseObject(const MouseObject& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MouseObject(MouseObject&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MouseObject& operator=(const MouseObject& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MouseObject& operator=(const MouseObject&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	GameEngineCollision* GetMouseCol();
	void SetMoveRange(const float4& _Start, const float4& _End);
	void SetFinalPos(const float4& _FinalPos);
	void MoveMousePos(bool _Flag = true);

	float4 GetMousePos() const
	{
		return pos_;
	}

	GameController* GetGameController() const
	{
		return gamecontroller_;
	}

	void MouseBlock(bool _bool);
public:
	void SetGameController(GameController* _MainController);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

