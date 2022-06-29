#pragma once
#include <GameEngineActor.h>
#include <GameEngineMath.h>
// �з� : 
// �뵵 : 
// ���� : 

class LobbyScatter : public GameEngineActor
{

private:	// member Var
	GameEngineRenderer* mainRender_;

private:
	float4 spawnPos_;
	GameEngineMath::Random randomGenerator_;

	float windSpeed_;
	float fallSpeed_;

public:
	LobbyScatter(); // default constructer ����Ʈ ������
	~LobbyScatter(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyScatter(const LobbyScatter& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyScatter(LobbyScatter&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyScatter& operator=(const LobbyScatter& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyScatter& operator=(const LobbyScatter&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

