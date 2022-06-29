#pragma once
#include <vector>
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineCollision;
class LobbySelectMapImage : public GameEngineActor
{
private:
	int curmapimage_;

private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

private:
	std::vector<std::string> mapimagenamelist_;

public:
	LobbySelectMapImage(); // default constructer ����Ʈ ������
	~LobbySelectMapImage(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbySelectMapImage(const LobbySelectMapImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbySelectMapImage(LobbySelectMapImage&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbySelectMapImage& operator=(const LobbySelectMapImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbySelectMapImage& operator=(const LobbySelectMapImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void CreateSelMapImageNameList(const std::vector<std::string>& _NameList);
	void SetCurMapIndex(int _Index);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

