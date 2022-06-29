#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
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
	WormHPNumber(); // default constructer ����Ʈ ������
	~WormHPNumber(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WormHPNumber(const WormHPNumber& _other) = delete; // default Copy constructer ����Ʈ ���������
	WormHPNumber(WormHPNumber&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WormHPNumber& operator=(const WormHPNumber& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WormHPNumber& operator=(const WormHPNumber&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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


	void HPInit(); // ���� �ִ� Worm �� ü���� �����ؼ� ���ڸ� �ٲ��ݴϴ�.


	void UpdateHP(int _hp); // ���� ü�¹��� ü���� ��� �Լ�


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

