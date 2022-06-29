#pragma once
#include <GameEngineActor.h>
#include <GameEngineTimeEventer.h>
#include <GameEngineSoundPlayer.h>

// �з� : 
// �뵵 : 
// ���� : 
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
	EndingFade(); // default constructer ����Ʈ ������
	~EndingFade(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	EndingFade(const EndingFade& _other) = delete; // default Copy constructer ����Ʈ ���������
	EndingFade(EndingFade&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	EndingFade& operator=(const EndingFade& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EndingFade& operator=(const EndingFade&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

