#pragma once
#include <GameEngineActor.h>

#define MAX_INPUTCOUNT 116

class GameEngineRenderer;
class ChattingInput : public GameEngineActor
{
private:
	static bool caretshow_;

public:
	static void SetCurCaretState(bool _Flag);

private:	// member Var
	bool ChattingInputOK_;
	std::string InputText_;
	int curcaretpos_;
	int prevcaretpos_;

private:
	GameEngineRenderer* chattingInputBoxSpriteRender_;

	GameEngineCollision* chattinInputBoxCollision_;

public:
	ChattingInput(); // default constructer ����Ʈ ������
	~ChattingInput(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	ChattingInput(const ChattingInput& _other) = delete; // default Copy constructer ����Ʈ ���������
	ChattingInput(ChattingInput&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	ChattingInput& operator=(const ChattingInput& _other) = delete; // default Copy operator ����Ʈ ���� ������
	ChattingInput& operator=(const ChattingInput&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void AddText(const std::string& _Text);
};

