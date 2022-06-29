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
	GameController(); // default constructer 디폴트 생성자
	~GameController(); // default destructer 디폴트 소멸자
	GameController(const GameController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameController(GameController&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameController& operator=(const GameController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameController& operator=(const GameController&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

	StateInfo startSettlement(StateInfo _state); // 턴 넘어가기 직전에 일종의 "결산" 단계입니다.
	StateInfo updateSettlement(StateInfo _state); // 대미지 판정 등을 해 주는 단계라고 생각해주시면 됩니다.

	StateInfo startDeathCheck(StateInfo _state);
	StateInfo updateDeathCheck(StateInfo _state);

	StateInfo startDeathPhase(StateInfo _state); // 대미지 판정 이후, 웜들의 죽음을 순차적으로 판별,
	StateInfo updateDeathPhase(StateInfo _state); // 진행하는 단계 (제작중);

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

public: // 턴 종료시 UI관련 갱신
	static void BottomStateHPBarSortCheck(BottomStateUI* _CurUI);
	static bool BottomStateHPBarSort();
	static void CurPlayerDeathCheck();

public:
	void MakeWaterLevel(float _WaterLevel = 1350.f); // 맵 바닥의 수면 생성

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

	int PetroleumCount_; // 현재 활성중인 기름 숫자

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
	float WormDeathWaitingTime_; // worm을 죽일 간격

	bool IsCameraMove_;
	bool WormDeathReady_; // 다음 worm을 죽일때가 옴
	bool WormDeathProgressing_; // 다음 worm을 죽일때가 옴

private: // 바람관련
	WindController* windController_;
	void WindInit();
	GameEngineMath::Random windDice_;


private: // 물관련
	WaterLevel* WaterLevel_;

private: // 하단상태바 정렬관련
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

