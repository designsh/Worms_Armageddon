#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class UIController;
class Worm;
class WormHPNumber : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	Worm* parent_;
	bool isWormLinked_;
	bool isDigitTen_;
	bool isDigitHundred_;

	float deltaTime_;

public:
	WormHPNumber(); // default constructer 디폴트 생성자
	~WormHPNumber(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WormHPNumber(const WormHPNumber& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WormHPNumber(WormHPNumber&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WormHPNumber& operator=(const WormHPNumber& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WormHPNumber& operator=(const WormHPNumber&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void AnimationInit();
	void ColorInit(int _wormNumber);
	void StartPosInit(int _wormNumber);
	void SetParentWorm(Worm* _worm)
	{
		parent_ = _worm;
		isWormLinked_ = true;
	}


	void HPInit(); // 엮여 있는 Worm 의 체력을 연동해서 숫자를 바꿔줍니다.


	void UpdateHP(int _hp); // 메인 체력바의 체력을 깎는 함수


	void SetDigitToTen()
	{
		isDigitTen_ = true;
		isDigitHundred_ = false;
	}

	void SetDigitToHundred()
	{
		isDigitHundred_ = true;
		isDigitTen_ = false;
	}
};

