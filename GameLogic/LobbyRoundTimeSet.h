#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyRoundTimeSet : public GameEngineActor
{
private:	// member Var
	int ImageIndex_;
	bool MouseOver_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbyRoundTimeSet(); // default constructer ����Ʈ ������
	~LobbyRoundTimeSet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyRoundTimeSet(const LobbyRoundTimeSet& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyRoundTimeSet(LobbyRoundTimeSet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyRoundTimeSet& operator=(const LobbyRoundTimeSet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyRoundTimeSet& operator=(const LobbyRoundTimeSet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

