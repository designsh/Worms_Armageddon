#pragma once
#include <GameEngineLevel.h>

// �з� : 
// �뵵 : 
// ���� : 
class EndingLevel : public GameEngineLevel
{
private:	// member Var

public:
	EndingLevel(); // default constructer ����Ʈ ������
	~EndingLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	EndingLevel(const EndingLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	EndingLevel(EndingLevel&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	EndingLevel& operator=(const EndingLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EndingLevel& operator=(const EndingLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Loading() override;
	void LevelUpdate() override;
};

