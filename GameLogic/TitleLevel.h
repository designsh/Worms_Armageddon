#pragma once
#include <GameEngineLevel.h>
// �з� : 
// �뵵 : 
// ���� : 
class TitleLevel : public GameEngineLevel
{
private:	// member Var

public:
	TitleLevel(); // default constructer ����Ʈ ������
	~TitleLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	TitleLevel(const TitleLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleLevel(TitleLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TitleLevel& operator=(const TitleLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleLevel& operator=(const TitleLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Loading() override;
	void LevelUpdate() override;
};

