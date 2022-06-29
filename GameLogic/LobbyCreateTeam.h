#pragma once
#include <GameEngineActor.h>

class GameEngineRenderer;
class LobbySelectablePlayer;
class LobbyCreateTeam : public GameEngineActor
{
private:
	static int PlayWormCount;

private:	// member Var
	GameEngineRenderer* playerselInputSpriteRender_;
	GameEngineRenderer* playerselboxSpriteRender_;
	GameEngineRenderer* playerboxSpriteRender_;

private: // ���� ���ð����� �÷��̾� ���
	std::vector<LobbySelectablePlayer*> SelectablePlayerList;
	int ActiveStartIndex_;
	int ActiveEndIndex_;
	std::vector<int> CurSelectIndex_;

private: // ���� ���õ� �÷��̾� ���
	std::vector<GameEngineRenderer*> SelectPlayerRendererList;
	std::vector<std::string> SelectPlayerNameList;
	std::vector<float4> SelectPlayerNamePosList;

public:
	LobbyCreateTeam(); // default constructer ����Ʈ ������
	~LobbyCreateTeam(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyCreateTeam(const LobbyCreateTeam& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyCreateTeam(LobbyCreateTeam&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyCreateTeam& operator=(const LobbyCreateTeam& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyCreateTeam& operator=(const LobbyCreateTeam&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public: // ���ð��� �÷��̾� ��� -> ���õ��÷��̾� ��� : �÷��̾� �����ϱ� ���
	void SetSelectPlayer(const std::string& _Name, int _Index);
	void SetSelectablePlayerSort();

public: // ���� ���õ� �÷��̾� �ɼǷ����� ����
	void CreateSelectPlayerOption();

};

