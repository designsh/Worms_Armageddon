#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyTeleportinSet : public GameEngineActor
{
private:	// member Var
	int ImageIndex_;
	bool MouseOver_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbyTeleportinSet(); // default constructer ����Ʈ ������
	~LobbyTeleportinSet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyTeleportinSet(const LobbyTeleportinSet& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyTeleportinSet(LobbyTeleportinSet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyTeleportinSet& operator=(const LobbyTeleportinSet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyTeleportinSet& operator=(const LobbyTeleportinSet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

