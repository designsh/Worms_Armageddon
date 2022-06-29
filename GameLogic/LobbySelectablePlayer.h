#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbyCreateTeam;
class LobbySelectablePlayer : public GameEngineActor
{
private:
	LobbyCreateTeam* parent_;

private: // Ȱ��ȭ�Ǿ��ִٸ� Ȱ��ȭ Index�� �˰��ִ´�.
	int ActiveIndex_;
	
private:
	bool SelectPlayerEnd_;

private:	// member Var
	bool ShowPlayer_;
	int Index_;
	std::string Name_;
	float4 NamePos_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbySelectablePlayer(); // default constructer ����Ʈ ������
	~LobbySelectablePlayer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbySelectablePlayer(const LobbySelectablePlayer& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbySelectablePlayer(LobbySelectablePlayer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbySelectablePlayer& operator=(const LobbySelectablePlayer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbySelectablePlayer& operator=(const LobbySelectablePlayer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
	virtual void Collision() override;

public:
	std::string GetPlayerName() const;
	int GetIndex() const;
	int GetActiveIndex() const;
	bool GetCurPlayerShow() const;
	GameEngineCollision* GetMainCollision() const;

public:// ���ð����� �÷��̾� ��Ͽ����� �÷��̾� ���� �ʱ� ���� �� �÷��̾� �������� ���� ���� ����
	void SetPlayerInfo(LobbyCreateTeam* _Parent, const float4& _NamePos, const float4& _RenderPos, const float4& _RenderSize = float4::ZERO);
	void ChangePlayerPos(const float4& _NamePos, const float4& _RenderPos, const float4& _RenderSize = float4::ZERO);

public: // �÷��̾� �������� ���� Ȱ��ȭ/��Ȱ��ȭ
	void SetPlayerOn(int _ActiveIndex);
	void SetPlayerOff();
	void DelActiveIndex();

public: // �÷��̾� ����(CPU or PLAYER)
	void CreatePlayer(const std::string& _PlayerName, int _Index, int _CPUIndex, bool _PlayerAndCPU = true);
};

