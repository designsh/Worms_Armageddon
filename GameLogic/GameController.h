#pragma once

#include <queue>
#include <vector>
#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineMath;
class Worm;
class WaterLevel;
class WindController;
class BackGroundScatter;
class BottomStateUI; 
class Petroleum;
class GameController : public GameEngineActor
{
public:
	GameController(); // default constructer ����Ʈ ������
	~GameController(); // default destructer ����Ʈ �Ҹ���
	GameController(const GameController& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameController(GameController&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	GameController& operator=(const GameController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameController& operator=(const GameController&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void CreateWorm(const float _minX, const float _maxX);
	void CreateWormUI();
	void CreateDrum(const float _minX, const float _maxX);

	void SetFocusOnlyOneWorm(Worm* _Worm);
	void SetFocusOnlyOneWorm(int _WormIndex);
	void SetCurrentWorm(int _WormIndex);
	

	std::vector<Worm*> GetWormList() const;
	Worm* GetCurWorm() const;
	

private:
	void initState();

private:
#pragma region States

	StateInfo startNextWorm(StateInfo _state);
	StateInfo updateNextWorm(StateInfo _state);

	StateInfo startAction(StateInfo _state);
	StateInfo updateAction(StateInfo _state);

	StateInfo startActionEnd(StateInfo _state);
	StateInfo updateActionEnd(StateInfo _state);

	StateInfo startSettlement(StateInfo _state); // �� �Ѿ�� ������ ������ "���" �ܰ��Դϴ�.
	StateInfo updateSettlement(StateInfo _state); // ����� ���� ���� �� �ִ� �ܰ��� �������ֽø� �˴ϴ�.

	StateInfo startDeathCheck(StateInfo _state);
	StateInfo updateDeathCheck(StateInfo _state);

	StateInfo startDeathPhase(StateInfo _state); // ����� ���� ����, ������ ������ ���������� �Ǻ�,
	StateInfo updateDeathPhase(StateInfo _state); // �����ϴ� �ܰ� (������);

	StateInfo startDeath(StateInfo _state);
	StateInfo updateDeath(StateInfo _state);

	StateInfo startVictory(StateInfo _state);
	StateInfo updateVictory(StateInfo _state);

	StateInfo startItemDrop(StateInfo _state);
	StateInfo updateItemDrop(StateInfo _state);

#pragma endregion
public:
	float4 GetCameraPos() const
	{
		return cameraPos_;
	}

	const float GetWaterLevel();

public:
	void IncresePetroleumCount()
	{
		PetroleumCount_++;
	}

	void DecresePetroleumCount()
	{
		PetroleumCount_--;
	}

	WindController* GetWindController()
	{
		return windController_;
	}
	void RandomTurnWind();

public: // �� ����� UI���� ����
	static void BottomStateHPBarSortCheck(BottomStateUI* _CurUI);
	static bool BottomStateHPBarSort();
	static void CurPlayerDeathCheck();

public:
	void MakeWaterLevel(float _WaterLevel = 1350.f); // �� �ٴ��� ���� ����

private:
	const int MAX_WORM_COUNT = 8;
	const float DEFAULT_TURN_TIME = 46.f;
	const float SETTLEMENT_TIME = 4.0f;

private:
	float GameEndChangeTime_;

private:
	GameEngineFSM<GameController> state_;
	std::vector<Worm*> wormList_;
	std::list<Worm*> readyToDeathWorm_;
	std::vector<float> xPosList_;

	int PetroleumCount_; // ���� Ȱ������ �⸧ ����

	size_t currentIndex_;

	Worm* CurDeathWorm_;
	Worm* NextDeathWorm_;

	Worm* currentWorm_;
	Worm* prevWorm_;

	int wormIndex_;
	int prevwormIndex_;
	int prevwormSize_;
	float4 cameraPos_;

	float cameraMoveSpeed_;
	float wormXPosContainer_;
	float settementTime_;
	float currentTurnTime_;
	float WormDeathWaitingTime_; // worm�� ���� ����

	bool IsCameraMove_;
	bool WormDeathReady_; // ���� worm�� ���϶��� ��
	bool WormDeathProgressing_; // ���� worm�� ���϶��� ��

private: // �ٶ�����
	WindController* windController_;
	void WindInit();
	GameEngineMath::Random windDice_;


private: // ������
	WaterLevel* WaterLevel_;

private: // �ϴܻ��¹� ���İ���
	static std::vector<BottomStateUI*> PlayerHPBarList;
	static std::queue<BottomStateUI*> PlayerHPBarSortQueue;
	static bool GameEndFlag;
	static bool DamageFlag;
	static bool BottomUISortEnd;
	static bool BottomUIDeath;
	static int SortStartIndex;
	static int SortEndIndex;
	static float SortDeltaTime;

public:
	static bool BottomUISortStart;
};

