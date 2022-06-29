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

private: // 현재 선택가능한 플레이어 목록
	std::vector<LobbySelectablePlayer*> SelectablePlayerList;
	int ActiveStartIndex_;
	int ActiveEndIndex_;
	std::vector<int> CurSelectIndex_;

private: // 현재 선택된 플레이어 목록
	std::vector<GameEngineRenderer*> SelectPlayerRendererList;
	std::vector<std::string> SelectPlayerNameList;
	std::vector<float4> SelectPlayerNamePosList;

public:
	LobbyCreateTeam(); // default constructer 디폴트 생성자
	~LobbyCreateTeam(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyCreateTeam(const LobbyCreateTeam& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyCreateTeam(LobbyCreateTeam&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyCreateTeam& operator=(const LobbyCreateTeam& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyCreateTeam& operator=(const LobbyCreateTeam&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public: // 선택가능 플레이어 목록 -> 선택된플레이어 목록 : 플레이어 선택하기 기능
	void SetSelectPlayer(const std::string& _Name, int _Index);
	void SetSelectablePlayerSort();

public: // 현재 선택된 플레이어 옵션렌더러 생성
	void CreateSelectPlayerOption();

};

