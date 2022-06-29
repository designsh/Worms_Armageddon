#pragma once
#include <GameEngineLevel.h>

// �з� : 
// �뵵 : 
// ���� : 
class MenuSelectLevel : public GameEngineLevel
{
private:	// member Var

public:
	MenuSelectLevel(); // default constructer ����Ʈ ������
	~MenuSelectLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MenuSelectLevel(const MenuSelectLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	MenuSelectLevel(MenuSelectLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MenuSelectLevel& operator=(const MenuSelectLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MenuSelectLevel& operator=(const MenuSelectLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Loading() override;
	void LevelUpdate() override;
};

