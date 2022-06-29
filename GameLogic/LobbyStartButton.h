#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyStartButton : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

private:
	std::string GameStartText_;

private:
	bool mouseover_;

public:
	LobbyStartButton(); // default constructer ����Ʈ ������
	~LobbyStartButton(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyStartButton(const LobbyStartButton& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyStartButton(LobbyStartButton&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyStartButton& operator=(const LobbyStartButton& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyStartButton& operator=(const LobbyStartButton&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

