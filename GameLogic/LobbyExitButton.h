#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyExitButton : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

private:
	std::string ExitText_;

private:
	bool mouseover_;

public:
	LobbyExitButton(); // default constructer ����Ʈ ������
	~LobbyExitButton(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyExitButton(const LobbyExitButton& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyExitButton(LobbyExitButton&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyExitButton& operator=(const LobbyExitButton& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyExitButton& operator=(const LobbyExitButton&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

