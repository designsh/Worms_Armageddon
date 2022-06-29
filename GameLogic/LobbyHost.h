#pragma once
#include <GameEngineActor.h>

class GameEngineRenderer;
class LobbyHost : public GameEngineActor
{
private:
	static bool curhostready_;

public:
	static void SetCurHostReady(bool _Flag);
	static bool SetCurHostReady();

private:	// member Var
	GameEngineRenderer* hostnationSpriteRender_;
	GameEngineRenderer* hostreadystateSpriteRender_;
	std::string hostName_;

public:
	LobbyHost(); // default constructer ����Ʈ ������
	~LobbyHost(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyHost(const LobbyHost& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyHost(LobbyHost&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyHost& operator=(const LobbyHost& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyHost& operator=(const LobbyHost&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

