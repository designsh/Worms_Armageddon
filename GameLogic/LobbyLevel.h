#pragma once
#include <GameEngineLevel.h>
// �з� : 
// �뵵 : 
// ���� : 
class LobbyLevel : public GameEngineLevel
{
private:	// member Var

public:
	LobbyLevel(); // default constructer ����Ʈ ������
	~LobbyLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyLevel(const LobbyLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyLevel(LobbyLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyLevel& operator=(const LobbyLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyLevel& operator=(const LobbyLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Loading() override;
	void LevelUpdate() override;

public:
	void Loading_SJH();
};

