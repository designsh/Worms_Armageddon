#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class BattleAxe
{
private:	// member Var

public:
	BattleAxe(); // default constructer ����Ʈ ������
	~BattleAxe(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	BattleAxe(const BattleAxe& _other) = delete; // default Copy constructer ����Ʈ ���������
	BattleAxe(BattleAxe&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	BattleAxe& operator=(const BattleAxe& _other) = delete; // default Copy operator ����Ʈ ���� ������
	BattleAxe& operator=(const BattleAxe&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

