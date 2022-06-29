#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyWormSelectSet : public GameEngineActor
{
private:	// member Var
	int ImageIndex_;
	bool MouseOver_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbyWormSelectSet(); // default constructer ����Ʈ ������
	~LobbyWormSelectSet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyWormSelectSet(const LobbyWormSelectSet& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyWormSelectSet(LobbyWormSelectSet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyWormSelectSet& operator=(const LobbyWormSelectSet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyWormSelectSet& operator=(const LobbyWormSelectSet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

