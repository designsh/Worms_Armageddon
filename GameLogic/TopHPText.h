#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : WormTopStateUI에 의해서 생성하며 WormTopStateUI의 HPBox가 세팅될때 생성한다.
class WormTopStateUI;
class GameEngineRenderer;
class TopHPText : public GameEngineActor
{
private:	// member Var
	WormTopStateUI* ParentHPBoxUI_;

private:
	int WormIndex_;
	int PlayerColorIndex_;
	int ImageStartIndex_;
	int PrevHP_;
	int CurHP_;

private:
	bool HPUpdateStart_;
	bool HPUpdateEnd_;
	int UpdateHundredNum;
	int UpdateTenNum;
	int UpdateNum;

private:
	const float NUMBER_CHANGE_TIME = 0.01f;
	float deltaTime_;

private:
	bool HundredFlag_;
	bool TenFlag_;
	bool NumFlag_;

private:
	GameEngineRenderer* HPHundredNumRenderer_;
	GameEngineRenderer* HPTenNumRenderer_;
	GameEngineRenderer* HPNumRenderer_;

public:
	TopHPText(); // default constructer 디폴트 생성자
	~TopHPText(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	TopHPText(const TopHPText& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TopHPText(TopHPText&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	TopHPText& operator=(const TopHPText& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TopHPText& operator=(const TopHPText&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void CreateHPText(WormTopStateUI* _Parent, int _WormIndex);
	void SetTextColor();
	void HPTextInit();

public:
	void ChangeHPText();
	void CheckHPTextZero();

	void ChangeTextAnimation(int _prevHp);
};

