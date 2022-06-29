#pragma once
#include <GameEngineActor.h>
#include <GameEngineTimeEventer.h>
#include <GameEngineSoundPlayer.h>

// 분류 : 
// 용도 : 
// 설명 : 
class EndingText;
class EndingFade : public GameEngineActor
{
private:	// member Var
	float alpha_;
	unsigned char castalpha_;
	bool fadestop_;

private:
	GameEngineRenderer* fadeBlackSpriteRender_;

private:
	GameEngineTimeEventer<EndingFade> EndingTimer_;

private:
	std::vector<EndingText*> CreditTextList_;
	int CreditTextListCnt_;

private:
	GameEngineSoundPlayer mainsound_;

public:
	EndingFade(); // default constructer 디폴트 생성자
	~EndingFade(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	EndingFade(const EndingFade& _other) = delete; // default Copy constructer 디폴트 복사생성자
	EndingFade(EndingFade&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	EndingFade& operator=(const EndingFade& _other) = delete; // default Copy operator 디폴트 대입 연산자
	EndingFade& operator=(const EndingFade&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void EndingFadeStart();
	void EndingFadeStay();
	bool EndingFadeEnd();

public:
	void PushCreditText(EndingText* _EndingText);
};

