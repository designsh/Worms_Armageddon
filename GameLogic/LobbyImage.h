#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyImage : public GameEngineActor
{
private:
	bool hostready_;
	bool mouseover_;

private:	// member Var
	GameEngineRenderer* backdropSpriteRender_;

private:
	GameEngineRenderer* hostboxSpriteRender_;	// host(��ǻ�͸�)
	GameEngineRenderer* hostreadySpriteRender_;	// host ready button

private:
	GameEngineCollision* hostreadyCollision_;

public:
	LobbyImage(); // default constructer ����Ʈ ������
	~LobbyImage(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyImage(const LobbyImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyImage(LobbyImage&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyImage& operator=(const LobbyImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyImage& operator=(const LobbyImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

