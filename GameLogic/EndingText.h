#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
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
	EndingText(); // default constructer ����Ʈ ������
	~EndingText(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	EndingText(const EndingText& _other) = delete; // default Copy constructer ����Ʈ ���������
	EndingText(EndingText&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	EndingText& operator=(const EndingText& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EndingText& operator=(const EndingText&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

