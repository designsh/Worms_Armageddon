#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>

// 분류 :
// 용도 :
// 설명 :
class FadeObject : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	float Alpha_;
	GameEngineFSM<FadeObject> FadeState;

public:
	// 외부에서 사용할때 이함수가 직관적일 것이다.
	void FadeIn();
	void FadeOut();

public:		
	FadeObject(); // default constructer 디폴트 생성자
	~FadeObject(); // default destructer 디폴트 소멸자

public:		// delete constructer
	FadeObject(const FadeObject& _other) = delete; // default Copy constructer 디폴트 복사생성자
	FadeObject(FadeObject&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	FadeObject& operator=(const FadeObject& _other) = delete; // default Copy operator 디폴트 대입 연산자
	FadeObject& operator=(const FadeObject&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Start();
	void Update();
	void Render();

private:		//member Func
	StateInfo FadeInStart(StateInfo _Info);
	StateInfo FadeOutStart(StateInfo _Info);

	StateInfo FadeInUpdate(StateInfo _Info);
	StateInfo FadeOutUpdate(StateInfo _Info);

	StateInfo DefaultStart(StateInfo _Info);
	StateInfo DefaultUpdate(StateInfo _Info);


	// GameEngineActor을(를) 통해 상속됨
	virtual void UpdateBefore() override;

	virtual void UpdateAfter() override;

private:
	float fadeInSpeed_;
	float fadeOutSpeed_;

public:
	void SetFadeInSpeed(float _fadeSpeed);
	void SetFadeOutSpeed(float _fadeSpeed);
};

