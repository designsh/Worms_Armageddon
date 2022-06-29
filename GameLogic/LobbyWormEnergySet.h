#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyWormEnergySet : public GameEngineActor
{
private:	// member Var
	int ImageIndex_;
	bool MouseOver_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbyWormEnergySet(); // default constructer ����Ʈ ������
	~LobbyWormEnergySet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyWormEnergySet(const LobbyWormEnergySet& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyWormEnergySet(LobbyWormEnergySet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyWormEnergySet& operator=(const LobbyWormEnergySet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyWormEnergySet& operator=(const LobbyWormEnergySet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

