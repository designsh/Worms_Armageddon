#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class Worm;
class UIController;
class BottomHealthBar : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;

private:
	Worm* parentWorm_;
	UIController* parentUI_;

public:
	BottomHealthBar(); // default constructer 디폴트 생성자
	~BottomHealthBar(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	BottomHealthBar(const BottomHealthBar& _other) = delete; // default Copy constructer 디폴트 복사생성자
	BottomHealthBar(BottomHealthBar&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	BottomHealthBar& operator=(const BottomHealthBar& _other) = delete; // default Copy operator 디폴트 대입 연산자
	BottomHealthBar& operator=(const BottomHealthBar&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void RenderColorInit(int _wormNumber);
	void StartPosInit(int _wormNumber);
	void DamageInit(int _damage);
};

