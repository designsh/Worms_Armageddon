#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyTernTimeSet : public GameEngineActor
{
private:	// member Var
	int ImageIndex_;
	int PrevInfinityRandom_;
	bool MouseOver_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbyTernTimeSet(); // default constructer ����Ʈ ������
	~LobbyTernTimeSet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyTernTimeSet(const LobbyTernTimeSet& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyTernTimeSet(LobbyTernTimeSet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyTernTimeSet& operator=(const LobbyTernTimeSet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyTernTimeSet& operator=(const LobbyTernTimeSet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

