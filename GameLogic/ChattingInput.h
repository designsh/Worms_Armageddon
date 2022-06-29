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
	ChattingInput(); // default constructer 디폴트 생성자
	~ChattingInput(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	ChattingInput(const ChattingInput& _other) = delete; // default Copy constructer 디폴트 복사생성자
	ChattingInput(ChattingInput&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	ChattingInput& operator=(const ChattingInput& _other) = delete; // default Copy operator 디폴트 대입 연산자
	ChattingInput& operator=(const ChattingInput&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void AddText(const std::string& _Text);
};

