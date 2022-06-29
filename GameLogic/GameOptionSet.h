#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class GameOptionSet : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	GameOptionSet(); // default constructer ����Ʈ ������
	~GameOptionSet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameOptionSet(const GameOptionSet& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameOptionSet(GameOptionSet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameOptionSet& operator=(const GameOptionSet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameOptionSet& operator=(const GameOptionSet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

