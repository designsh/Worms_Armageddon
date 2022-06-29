#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyWinsreQuiredSet : public GameEngineActor
{
private:	// member Var
	int ImageIndex_;
	bool MouseOver_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbyWinsreQuiredSet(); // default constructer ����Ʈ ������
	~LobbyWinsreQuiredSet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyWinsreQuiredSet(const LobbyWinsreQuiredSet& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyWinsreQuiredSet(LobbyWinsreQuiredSet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyWinsreQuiredSet& operator=(const LobbyWinsreQuiredSet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyWinsreQuiredSet& operator=(const LobbyWinsreQuiredSet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

