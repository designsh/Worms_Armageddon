#pragma once
#include <GameEngineLevel.h>
// �з� : 
// �뵵 : 
// ���� : 
class LoadingLevel : public GameEngineLevel
{
private:	// member Var

public:
	LoadingLevel(); // default constructer ����Ʈ ������
	~LoadingLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LoadingLevel(const LoadingLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	LoadingLevel(LoadingLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LoadingLevel& operator=(const LoadingLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LoadingLevel& operator=(const LoadingLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Loading() override;
	void LevelUpdate() override;
};

