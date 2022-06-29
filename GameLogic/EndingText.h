#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class EndingText : public GameEngineActor
{
private:	// member Var
	std::vector<GameEngineRenderer*> TextRenderer_;
	int TextRendererSize_;

private:
	std::string Text_;
	int TextSize_;
	float4 TextStartPos_;
	float4 TextScale_;

private:
	bool Move_;
	float MoveSpeed_;

public:
	EndingText(); // default constructer 디폴트 생성자
	~EndingText(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	EndingText(const EndingText& _other) = delete; // default Copy constructer 디폴트 복사생성자
	EndingText(EndingText&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	EndingText& operator=(const EndingText& _other) = delete; // default Copy operator 디폴트 대입 연산자
	EndingText& operator=(const EndingText&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void EndingTextInit(const std::string& _Text, const float4& _Pos);
	void MoveStart();
};

