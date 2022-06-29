#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : WormTopStateUI�� ���ؼ� �����ϸ� WormTopStateUI�� HPBox�� ���õɶ� �����Ѵ�.
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
	TopHPText(); // default constructer ����Ʈ ������
	~TopHPText(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	TopHPText(const TopHPText& _other) = delete; // default Copy constructer ����Ʈ ���������
	TopHPText(TopHPText&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TopHPText& operator=(const TopHPText& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TopHPText& operator=(const TopHPText&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

