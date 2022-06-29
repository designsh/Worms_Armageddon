#include "GameController.h"

#include <GameEngineMath.h>
#include <GameEngineWindow.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineDebugExtension.h>

#include "GameOptionInfo.h"
#include "Worm.h"
#include "DrumActor.h"
#include "UIController.h"
#include "WeaponSheet.h"
#include "WeaponIcon.h"
#include "Weapon.h"
#include "BottomStateUI.h"
#include "WormTopStateUI.h"

#include "WaterLevel.h"
#include "WaterWave.h"
#include "UnderWater.h"

#include "WormArrow.h"
#include "WormHPBlankWindow.h"
#include "BottomHealthBar.h"
#include "BottomFlag.h"
#include "BottomNameTag.h"
#include "WormName.h"
#include "TimerBlankWindow.h"
#include "TimerDigit.h"
#include "WormHPNumber.h"
#include "TopHPText.h"

#include "WindBarBlank.h"
#include "WindBar.h"
#include "WindBarHider.h"
#include "BackgroundScatter.h"
#include "WindController.h"
#include "Cloud.h"

#include "PlayLevel.h"

#include <GameEngineLevelManager.h>

std::vector<BottomStateUI*> GameController::PlayerHPBarList;
std::queue<BottomStateUI*> GameController::PlayerHPBarSortQueue;
bool GameController::BottomUISortStart = false;
bool GameController::BottomUISortEnd = false;
bool GameController::BottomUIDeath = false;
bool GameController::DamageFlag = false;
bool GameController::GameEndFlag = false;
int GameController::SortStartIndex = -1;
int GameController::SortEndIndex = -1;
float GameController::SortDeltaTime = 0.f;

GameController::GameController() // default constructer 디폴트 생성자
	: currentIndex_(0)
	, currentWorm_(nullptr)
	, prevWorm_(nullptr)
	, cameraMoveSpeed_(10.f)
	, wormIndex_(0)
	, PetroleumCount_(0)
	, prevwormIndex_(MAX_WORM_COUNT)
	, IsCameraMove_(false)
	, WormDeathReady_(false)
	, WormDeathProgressing_(false)
	, cameraPos_(0.f, 0.f)
	, state_(this)
	, currentTurnTime_(0.0f)
	, wormXPosContainer_(0.0f)
	, WormDeathWaitingTime_(0.0f)
	, WaterLevel_(nullptr)
	, settementTime_(0.0f)
	, windController_(nullptr)
	, CurDeathWorm_(nullptr)
	, NextDeathWorm_(nullptr)
	, GameEndChangeTime_(10.f)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
{

}

void GameController::Start()
{
	WindInit();
	initState();
	MakeWaterLevel(750);

	if (false == GameEngineInput::GetInst().IsKey("W"))
	{
		GameEngineInput::GetInst().CreateKey("W", 'W');
	}

	if (false == GameEngineInput::GetInst().IsKey("S"))
	{
		GameEngineInput::GetInst().CreateKey("S", 'S');
	}

	if (false == GameEngineInput::GetInst().IsKey("A"))
	{
		GameEngineInput::GetInst().CreateKey("A", 'A');
	}

	if (false == GameEngineInput::GetInst().IsKey("D"))
	{
		GameEngineInput::GetInst().CreateKey("D", 'D');
	}

	if (false == GameEngineInput::GetInst().IsKey("UpArrow"))
	{
		GameEngineInput::GetInst().CreateKey("UpArrow", VK_UP);
	}
	if (false == GameEngineInput::GetInst().IsKey("DownArrow"))
	{
		GameEngineInput::GetInst().CreateKey("DownArrow", VK_DOWN);
	}
	if (false == GameEngineInput::GetInst().IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst().CreateKey("LeftArrow", VK_LEFT);
	}
	if (false == GameEngineInput::GetInst().IsKey("RightArrow"))
	{
		GameEngineInput::GetInst().CreateKey("RightArrow", VK_RIGHT);
	}

	// TODO : 테스트가 끝난 후 삭제
	if (false == GameEngineInput::GetInst().IsKey("TestKey"))
	{
		GameEngineInput::GetInst().CreateKey("TestKey", 0xC0);
	}

	// UI
	if (false == GameEngineInput::GetInst().IsKey("WeaponSheet"))
	{
		GameEngineInput::GetInst().CreateKey("WeaponSheet", VK_RBUTTON);
	}
}

void GameController::UpdateBefore()
{
	// UI
	if (true == GameEngineInput::GetInst().IsDown("WeaponSheet"))
	{
		wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetActive();
		prevwormIndex_ = wormIndex_;
	}

	if (!PlayerHPBarSortQueue.empty() && false == BottomUISortStart)
	{
		// 선입선출의 개념을 활용하여 그다음 정렬 항목을 빼오며
		BottomStateUI* QueueState = PlayerHPBarSortQueue.front();

		// 정렬시작하므로 큐에서 제거
		PlayerHPBarSortQueue.pop();

		// 정렬 시작
		BottomStateHPBarSortCheck(QueueState);
	}
}

void GameController::Update()
{
	// 승리하였으므로 레벨 체인지
	if (true == GameEndFlag)
	{
		GameEndChangeTime_ -= GameEngineTime::GetInst().GetDeltaTime();
		if (0.f >= GameEndChangeTime_)
		{
			GameEndChangeTime_ = 3.f;
			GameEngineLevelManager::GetInst().ChangeLevel("EndingLevel", true);
		}
	}

	state_.Update();

	// 남은 플레이어가 1명이므로 승리로 판단
	// 남은 플레이어가 없다면 무승부로 판단
	if (1 == wormList_.size())
	{
		// 남은플레이어를 승리상태로 전환
		wormList_[0]->ChangeState("Win");

		// Flag On
		GameEndFlag = true;
		return;
	}
	else if (0 == wormList_.size())
	{
		// 남은 플레이어가 없으므로 FadeIn/Out처리 후 엔딩씬으로 전환
		GameEndFlag = true;

		return;
	}

	// 플레이어가 사망해서 UI가 지워진상태라면
	// 나머지 하단바에 대한 위치 재조정
	//if (true == BottomUISortEnd)
	//{
	//	BottomUISortEnd = false;

	//	// 여기서 현재 모든 플레이어가 정렬이 종료되었으므로
	//	// 모든 플레이어의 체력상태를 체크한다.
	//	int Size = static_cast<int>(PlayerHPBarList.size());
	//	for (int i = 0; i < Size; ++i)
	//	{
	//		if (0 >= PlayerHPBarList[i]->GetParentWorm()->GetCurHP())
	//		{
	//			if (true == PlayerHPBarList[i]->GetParentWorm()->UIControllerDeath())
	//			{
	//				PlayerHPBarList.erase(PlayerHPBarList.begin() + i);
	//				Size = static_cast<int>(PlayerHPBarList.size());

	//				for (int k = 0; k < Size; ++k)
	//				{
	//					PlayerHPBarList[k]->PositionReadjustment();
	//				}

	//				BottomUIDeath = true;
	//			}
	//		}
	//	}
	//}

	//if (true == BottomUIDeath)
	//{
	//	int size = wormList_.size();
	//	for (int i = 0; i < size; ++i)
	//	{
	//		if (wormList_[i]->GetDeathState() == Worm::DeathState::DeathEnd)
	//		{
	//			if (wormList_[i] == currentWorm_)
	//			{
	//				currentWorm_ = nullptr;
	//			}
	//			wormList_[i]->WormDeath();
	//			wormList_.erase(wormList_.begin() + i);

	//			size = wormList_.size();
	//		}
	//	}
	//	BottomUIDeath = false;
	//	return;
	//}

	//TODO : 죽을 녀석 찾아다가 포커싱 해줘야함

	GameEngineDebugExtension::PrintDebugWindowText("wormIndex : ", wormIndex_);
	GameEngineDebugExtension::PrintDebugWindowText("wormListSize : ", wormList_.size());
}

void GameController::UpdateAfter()
{
	{
		if (true == GameEngineInput::GetInst().IsPress("W"))
		{
			GetLevel()->SetCamMove(float4::UP * cameraMoveSpeed_);
			IsCameraMove_ = true;
		}

		if (true == GameEngineInput::GetInst().IsPress("S"))
		{
			GetLevel()->SetCamMove(float4::DOWN * cameraMoveSpeed_);
			IsCameraMove_ = true;
		}

		if (true == GameEngineInput::GetInst().IsPress("A"))
		{
			GetLevel()->SetCamMove(float4::LEFT * cameraMoveSpeed_);
			IsCameraMove_ = true;
		}

		if (true == GameEngineInput::GetInst().IsPress("D"))
		{
			GetLevel()->SetCamMove(float4::RIGHT * cameraMoveSpeed_);
			IsCameraMove_ = true;
		}
	}
	if (IsCameraMove_)
	{
		if (GameEngineInput::GetInst().IsPress("UpArrow"))
		{
			IsCameraMove_ = false;
		}
		if (GameEngineInput::GetInst().IsPress("DownArrow"))
		{
			IsCameraMove_ = false;
		}
		if (GameEngineInput::GetInst().IsPress("LeftArrow"))
		{
			IsCameraMove_ = false;
		}
		if (GameEngineInput::GetInst().IsPress("RightArrow"))
		{
			IsCameraMove_ = false;
		}
	}
	else
	{
		cameraPos_ = GetLevel()->GetCamPos();

		if (1 == static_cast<int>(wormList_.size()))
		{
			// 웜리스트 사이즈가 1이다 == 한명만 살아남은 상태다
			float4 cameraMovePos = wormList_[0]->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4();
			float4 MoveVector = cameraMovePos - cameraPos_;

			GetLevel()->SetCamMove(MoveVector * 0.1f);
			return;
		}

		// 사망한 웜이 존재한다면 카메라 포커스 대기(다음웜으로 넘어간상태가되면 웜리스트 카운트를 리셋해줌
		if (prevwormSize_ != static_cast<int>(wormList_.size()))
		{
			return;
		}

		float4 cameraMovePos = wormList_[wormIndex_]->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4();
		float4 MoveVector = cameraMovePos - cameraPos_;

		GetLevel()->SetCamMove(MoveVector * 0.1f);
	}
}

void GameController::Render()
{
}

void GameController::CreateWorm(const float _minX, const float _maxX)
{
	if (wormList_.size() >= MAX_WORM_COUNT)
	{
		GameEngineDebug::MsgBoxError("최대 지렁이 개수를 초과하였습니다.");
		return;
	}

	GameEngineMath::Random randomGenerator;
	std::string name = "Worm";
	name += std::to_string(currentIndex_++);
	Worm* newWorm = parentLevel_->CreateActor<Worm>(name);
	wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // 전에 생성한 좌표를 멤버변수에 저장

	std::vector<float>::iterator startIter = xPosList_.begin();
	std::vector<float>::iterator endIter = xPosList_.end();
	for (; startIter != endIter; startIter++)
	{
		if (wormXPosContainer_ >= *startIter - 25.0f && wormXPosContainer_ <= *startIter + 25.0f) // 
		{
			wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX);
			startIter = xPosList_.begin();
			continue;
		}
	}

	WormArrow* newArrow = GetLevel()->CreateActor<WormArrow>();
	newArrow->SetParent(newWorm);

	newWorm->SetPos({ wormXPosContainer_ , -500.0f });
	newWorm->SetFocus(false);

	wormList_.push_back(newWorm);

	xPosList_.push_back(wormXPosContainer_);
	wormList_[0]->SetFocus(true);
	prevwormSize_ = wormList_.size();
	currentWorm_ = wormList_[0];
}

void GameController::CreateWormUI()
{
	size_t wormcnt = wormList_.size();
	PlayerHPBarList.resize(wormcnt);
	for (int i = 0; i < wormcnt; ++i)
	{
		std::string Name = wormList_[i]->GetName();
		Name += "_UI";

		// UI관리자생성
		UIController* CurUIController = parentLevel_->CreateActor<UIController>(Name);
		CurUIController->SetCurPlayer(wormList_[i]);

		// 플레이어당 UIController 지정
		wormList_[i]->SetUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetParentController(wormList_[i]->GetCurUIController());

		// 플레이어당 상단 상태 UI
		wormList_[i]->GetCurUIController()->GetCurTopState()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTopState()->SetParentUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurTopState()->GameStartInit(static_cast<int>(i));

		// 플레이어당 턴 타이머 UI 지정
		wormList_[i]->GetCurUIController()->GetCurTimerWindow()->RenderColorInit(static_cast<int>(i));
		wormList_[i]->GetCurUIController()->GetCurTimerWindow()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTimerDigitTen()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTimerDigit()->SetParentWorm(wormList_[i]);

		// 플레이어당 체력표시텍스트 UI 지정
		//wormList_[i]->GetCurUIController()->GetCurHPNumberHundred()->SetParentWorm(wormList_[i]);
		//wormList_[i]->GetCurUIController()->GetCurHPNumberHundred()->ColorInit(static_cast<int>(i));
		//wormList_[i]->GetCurUIController()->GetCurHPNumberHundred()->SetDigitToHundred();
		//wormList_[i]->GetCurUIController()->GetCurHPNumberHundred()->HPInit();
		//wormList_[i]->GetCurUIController()->GetCurHPNumberTen()->SetParentWorm(wormList_[i]);
		//wormList_[i]->GetCurUIController()->GetCurHPNumberTen()->ColorInit(static_cast<int>(i));
		//wormList_[i]->GetCurUIController()->GetCurHPNumberTen()->SetDigitToTen();
		//wormList_[i]->GetCurUIController()->GetCurHPNumberTen()->HPInit();
		//wormList_[i]->GetCurUIController()->GetCurHPNumber()->SetParentWorm(wormList_[i]);
		//wormList_[i]->GetCurUIController()->GetCurHPNumber()->ColorInit(static_cast<int>(i));
		//wormList_[i]->GetCurUIController()->GetCurHPNumber()->HPInit();

		// 플레이어당 무기창 지정 및 활성화 무기 지정
		std::string SheetName = wormList_[i]->GetName();
		SheetName += "_WeaponSheet";
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetName(SheetName);

		// 초기 아이템 목록지정
		std::vector<eItemList> ItemListTest;
		ItemListTest.resize(11);
		ItemListTest[0] = eItemList::WEAPON_BAZOOKA;
		ItemListTest[1] = eItemList::WEAPON_HOMINGMISSILE;
		ItemListTest[2] = eItemList::WEAPON_FIREPUNCH;
		ItemListTest[3] = eItemList::WEAPON_UZI;
		ItemListTest[4] = eItemList::WEAPON_BATTLEAXE;
		ItemListTest[5] = eItemList::WEAPON_GIRDER;
		ItemListTest[6] = eItemList::WEAPON_SHEEP;
		ItemListTest[7] = eItemList::WEAPON_SUPERSHEEP;
		ItemListTest[8] = eItemList::WEAPON_BLOWTORCH;
		ItemListTest[9] = eItemList::WEAPON_PNEUMATICDRILL;
		ItemListTest[10] = eItemList::WEAPON_AIRSTRIKE;
		CurUIController->CreateWeaponList(ItemListTest);				// 플레이어가 처음 가지고있는 아이템목록(최초지정)

		// 무기창 기능 참고용
		//CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 기믹오브젝트 획득으로 인한 무기획득시 호출(새로운무기추가 또는 기존무기개수증가)
		//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 무기사용했을대 호출(가지고있는 무기개수감수)
		ItemListTest.clear();

		// 플레이어당 하단 상태 UI
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->GameStartInit(static_cast<int>(i));

		// 플레이어 하단 상태바관련 관리목록에 추가
		PlayerHPBarList[i] = wormList_[i]->GetCurUIController()->GetCurBottomState();
	}
}

void GameController::CreateDrum(const float _minX, const float _maxX)
{
	GameEngineMath::Random randomGenerator;
	DrumActor* newDrum = parentLevel_->CreateActor<DrumActor>();
	wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // 전에 생성한 좌표를 멤버변수에 저장

	std::vector<float>::iterator startIter = xPosList_.begin();
	std::vector<float>::iterator endIter = xPosList_.end();
	for (; startIter != endIter; startIter++)
	{
		if (wormXPosContainer_ >= *startIter - 25.0f && wormXPosContainer_ <= *startIter + 25.0f) // 
		{
			wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX);
			startIter = xPosList_.begin();
			continue;
		}
	}

	newDrum->SetPos({ wormXPosContainer_ , -500.0f });
}

void GameController::SetFocusOnlyOneWorm(Worm* _Worm)
{
	for (int i = 0; i < wormList_.size(); ++i)
	{
		if (_Worm == wormList_[i])
		{
			wormList_[i]->SetFocus(true);
		}
		else
		{
			wormList_[i]->SetFocus(false);
		}
	}
}

void GameController::SetFocusOnlyOneWorm(int _WormIndex)
{
	for (int i = 0; i < wormList_.size(); ++i)
	{
		if (_WormIndex == i)
		{
			wormList_[i]->SetFocus(true);
		}
		else
		{
			wormList_[i]->SetFocus(false);
		}
	}
}

void GameController::SetCurrentWorm(int _WormIndex)
{
	currentWorm_ = wormList_[_WormIndex];
}

std::vector<Worm*> GameController::GetWormList() const
{
	return wormList_;
}

Worm* GameController::GetCurWorm() const
{
	if (wormIndex_ == MAX_WORM_COUNT)
	{
		return nullptr;
	}

	return currentWorm_;
}

void GameController::initState()
{
	state_.CreateState("NextWorm", &GameController::startNextWorm, &GameController::updateNextWorm);
	state_.CreateState("Action", &GameController::startAction, &GameController::updateAction);
	state_.CreateState("ActionEnd", &GameController::startActionEnd, &GameController::updateActionEnd);
	state_.CreateState("Settlement", &GameController::startSettlement, &GameController::updateSettlement);
	state_.CreateState("DeathCheck", &GameController::startDeathCheck, &GameController::updateDeathCheck);
	state_.CreateState("DeathPhase", &GameController::startDeathPhase, &GameController::updateDeathPhase);
	state_.CreateState("Death", &GameController::startDeath, &GameController::updateDeath);
	state_.CreateState("Victory", &GameController::startVictory, &GameController::updateVictory);
	state_.CreateState("ItemDrop", &GameController::startItemDrop, &GameController::updateItemDrop);

	state_.ChangeState("NextWorm");
}

StateInfo GameController::startNextWorm(StateInfo _state)
{
	GameEngineSoundManager::GetInstance().PlaySoundByName("YESSIR.WAV");

	RandomTurnWind();

	for (size_t i = 0; i < wormList_.size(); i++)
	{
		wormList_[i]->ResetisDamaged();
	}

	return "";
}

StateInfo GameController::updateNextWorm(StateInfo _state)
{
	if (currentWorm_ == nullptr)
	{
		//TODO : 이부분 수정이 필요해 보임
		//6마리 웜을 순차적으로 죽이고 마지막 1마리만 남았을때 UpdateAfter에서 문제가 발생했음, 
		//wormlist_ 에는 [0]만 남았는데 인덱스가 1인경우
		// 그냥 웜인덱스 시스템을 없애고 웜 진행 순서를 리스트로 구현해 보는건 어떨까 함

		prevwormIndex_ = wormIndex_;

		// 여기서 사망한 웜즈가 있는지 체크
		if (prevwormSize_ != static_cast<int>(wormList_.size()))
		{
			// 사망했던 웜의 인덱스를 현재 WormIndex에 셋팅 단,
			// 사망한 웜이 마지막인덱스였다면 -1


			prevwormSize_ = static_cast<int>(wormList_.size());
		}
		else
		{
			++wormIndex_;
		}

		if (wormIndex_ == wormList_.size())
		{
			wormIndex_ = 0;
		}

		SetFocusOnlyOneWorm(wormIndex_);
		SetCurrentWorm(wormIndex_);

		IsCameraMove_ = false;
		return "";
	}

	currentWorm_->AddActionToken(1);

	// 대기실 턴타임셋팅에 따라 턴타임이 달라짐 - 220207 SJH 수정
	currentTurnTime_ = GameOptionInfo::TernTime;
	//currentTurnTime_ = DEFAULT_TURN_TIME;
	return "Action";
}

StateInfo GameController::startAction(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateAction(StateInfo _state)
{

	currentTurnTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	// 타이머 갱신을 해 줘야하는 부분
	currentWorm_->GetCurUIController()->GetCurTimerDigitTen()->SetTenDigitTime(currentTurnTime_);
	currentWorm_->GetCurUIController()->GetCurTimerDigit()->SetDigitTime(currentTurnTime_);

	if (GameEngineInput::GetInst().IsDown("TestKey"))
	{
		currentWorm_->SubtractActionToken(1);

		// 강제전환으로인한 무기창 및 무기아이콘 비활성화
		currentWorm_->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		currentTurnTime_ = 0.0f;
	}

	if (currentTurnTime_ < 0 || 0 >= currentWorm_->GetActionTokenCount())
	{
		// 턴시간 초과 or 토큰 소진으로 인한 플레이어 전환이 발생하므로 이곳에서
		// 무기창 비활성이 된다.
		currentWorm_->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		// 라운타임 초과 및 플레이어 턴초과시 물높이 상승
		if (nullptr != WaterLevel_)
		{
			WaterLevel_->TernChangeWaterLevelUp();
		}

		return "ActionEnd";
	}
	return StateInfo();
}

StateInfo GameController::startActionEnd(StateInfo _state)
{
	currentWorm_->ClearActionToken();
	currentWorm_->ChangeState("WeaponOff");
	return StateInfo();
}

StateInfo GameController::updateActionEnd(StateInfo _state)
{
	currentWorm_ = nullptr;

	return "Settlement";
}

StateInfo GameController::startSettlement(StateInfo _state)
{
	for (size_t i = 0; i < wormList_.size(); i++)
	{
		if (true == wormList_[i]->isDamagedThisTurn())
		{
			BottomUISortStart = true;
			wormList_[i]->GetCurUIController()->GetCurTopState()->SetTextChangeRequest();
		}
	}

	return StateInfo();
}

StateInfo GameController::updateSettlement(StateInfo _state)
{
	for (size_t i = 0; i < wormList_.size(); i++)
	{
		if (true == wormList_[i]->isDamagedThisTurn())
		{
			DamageFlag = true;

			if (false == wormList_[i]->GetCurUIController()->GetCurBottomState()->GetDecreaswHPBarFlag())
			{
				if (true == BottomStateHPBarSort())
				{
					wormList_[i]->ResetisDamaged();
				}
			}
			wormList_[i]->GetCurUIController()->GetCurTopState()->SetTextChangeRequest();
		}
	}

	// Damage를 받은 웜즈가 없으면 바로 넘김
	if (false == DamageFlag)
	{
		BottomUISortEnd = false;
		return "DeathCheck";
	}

	// UI 정렬 완료 전까지 넘기면안됌
	if (true == BottomUISortEnd)
	{
		BottomUISortEnd = false;
		return "DeathCheck";
	}

	return StateInfo();
}

StateInfo GameController::startDeathCheck(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateDeathCheck(StateInfo _state)
{
	std::vector<Worm*>::iterator startIter = wormList_.begin();

		while (startIter != wormList_.end())
		{
			Worm* currentWorm = *startIter;
			if (currentWorm->GetDeathState() == Worm::DeathState::DeathReady)
			{
				readyToDeathWorm_.push_back(currentWorm);
				startIter = wormList_.erase(startIter);
			}
			else
			{
				++startIter;
			}
		}

	CurDeathWorm_ = nullptr;

	return "DeathPhase";
}

StateInfo GameController::startDeathPhase(StateInfo _state) // 
{
	return StateInfo();
}

StateInfo GameController::updateDeathPhase(StateInfo _state)
{
	if (0 < readyToDeathWorm_.size())
	{
		CurDeathWorm_ = readyToDeathWorm_.front();
		CurDeathWorm_->SetDeathState(Worm::DeathState::DeathStart);
		//CurDeathWorm_->ChangeState("Death");
		readyToDeathWorm_.pop_front();

		return "Death";
	}

	return "NextWorm";
}


StateInfo GameController::startDeath(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateDeath(StateInfo _state)
{
	if (CurDeathWorm_ != nullptr && CurDeathWorm_->GetDeathState() == Worm::DeathState::DeathEnd)
	{
		BottomStateUI* DeathBottomUI = CurDeathWorm_->GetCurUIController()->GetCurBottomState();

		// 여기서 현재 모든 플레이어가 정렬이 종료되었으므로
		// 모든 플레이어의 체력상태를 체크한다.
		int Size = static_cast<int>(PlayerHPBarList.size());
		for (int i = 0; i < Size; ++i)
		{
			if (0 >= PlayerHPBarList[i]->GetParentWorm()->GetCurHP())
			{
				if (PlayerHPBarList[i] == DeathBottomUI)
				{
					PlayerHPBarList.erase(PlayerHPBarList.begin() + i);
					Size = static_cast<int>(PlayerHPBarList.size());
					for (int k = 0; k < Size; ++k)
					{
						PlayerHPBarList[k]->PositionReadjustment();
					}
				}
			}
		}

		CurDeathWorm_->WormDeath();
		DamageFlag = false;
		BottomUISortEnd = false;
		CurDeathWorm_ = nullptr;
		if (0 < readyToDeathWorm_.size())
		{
			return "DeathPhase";
		}
		else
		{
			return "NextWorm";
		}
	}

	return StateInfo();
}

StateInfo GameController::startVictory(StateInfo _state)
{
	// 빅토리 스테이트에선 이론상 웜리스트에 웜은 한 마리밖에 없습니다.
	// 유일한 웜에게 카메라가 포커싱되며 해당 웜은 Win 스테이트를 실행합니다.
	return StateInfo();
}

StateInfo GameController::updateVictory(StateInfo _state)
{
	for (size_t i = 0; i < wormList_.size(); i++)
	{
		wormList_[i]->ChangeState("Win");
	}

	static float waitTime = 2.0f;

	waitTime -= GameEngineTime::GetInst().GetDeltaTime();
	if (waitTime < 0.f)
	{
		GameEngineLevelManager::GetInst().ChangeLevel("EndingLevel");
	}

	return StateInfo();
}

StateInfo GameController::startItemDrop(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateItemDrop(StateInfo _state)
{
	return StateInfo();
}

const float GameController::GetWaterLevel()
{
	return WaterLevel_->GetWaterLevel();
}

void GameController::MakeWaterLevel(float _WaterLevel)
{
	WaterLevel_ = GetLevel()->CreateActor<WaterLevel>("WaterLevel"); // 모든 파도 actor 그룹화
	WaterLevel_->SetwaterLevel(_WaterLevel);

	WaterWave* WaterWaveactor;
	UnderWater* UnderWaterActor;

	for (int j = -1; j < 2; ++j)
	{
		for (int i = 0; i < 2; ++i)
		{
			WaterWaveactor = GetLevel()->CreateActor<WaterWave>(float4(j * 2560.f, _WaterLevel + i * 30.f, 0.f));
			WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
			WaterWaveactor->SetAnimationCurrentFrame(i * 2);
			WaterLevel_->Waterlist.push_back(WaterWaveactor);
		}

		for (int i = 2; i < 5; ++i)
		{
			WaterWaveactor = GetLevel()->CreateActor<WaterWave>(float4(j * 2560.f, _WaterLevel + i * 30.f, 0.f));
			WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
			WaterWaveactor->SetAnimationCurrentFrame(i * 2);
			WaterLevel_->Waterlist.push_back(WaterWaveactor);
		}
		UnderWaterActor = GetLevel()->CreateActor<UnderWater>(float4(j * 2560.f, _WaterLevel + 680.f, 0.f));
		UnderWaterActor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
		WaterLevel_->Waterlist.push_back(UnderWaterActor);
	}
}

void GameController::BottomStateHPBarSortCheck(BottomStateUI* _CurUI)
{
	// 현재 이미 다른 플레이어 Bottom HPBar가 정렬중이라면
	// 대기큐에 해당 플레이어UI저장
	if (true == BottomUISortStart)
	{
		PlayerHPBarSortQueue.push(_CurUI);
	}
	else
	{
		// 현재 플레이어의 체력에 따라 정렬 시작
		int Size = static_cast<int>(PlayerHPBarList.size());
		for (int i = 0; i < Size; ++i)
		{
			if (PlayerHPBarList[i] == _CurUI)
			{
				SortStartIndex = i;
				break;
			}
		}

		for (int i = 0; i < Size; ++i)
		{
			if (1 == Size && PlayerHPBarList[SortStartIndex] == PlayerHPBarList[i])
			{
				// 플레이어가 이미 한마리이므로
				SortEndIndex = SortStartIndex;
				continue;
			}

			if (PlayerHPBarList[i] == _CurUI)
			{
				continue;
			}

			if (SortStartIndex + 1 == Size)
			{
				continue;
			}

			if (PlayerHPBarList[SortStartIndex]->GetCurHP() < PlayerHPBarList[i]->GetCurHP())
			{
				BottomUISortStart = true;
				SortEndIndex = i;
			}
			else if (SortStartIndex == Size - 1) // 이미 가장 낮은 체력의 플레이어
			{
				BottomUISortStart = false;
				SortEndIndex = SortStartIndex;
			}

			if (SortEndIndex < SortStartIndex)
			{
				SortEndIndex = SortStartIndex;
			}
		}
	}
}

bool GameController::BottomStateHPBarSort()
{
	SortDeltaTime += GameEngineTime::GetInst().GetDeltaTime();
	if (0.3f <= SortDeltaTime)
	{
		SortDeltaTime = 0.f;

		int Size = static_cast<int>(PlayerHPBarList.size());
		bool Flag = false;
		for (int i = SortStartIndex; i < SortStartIndex + 1; ++i)
		{
			// 정렬 종료후 정렬대기열에 정렬할 HPBar가 존재한다면
			// 해당 HPBar정렬 시작
			if (SortStartIndex == SortEndIndex && 1 != Size)
			{
				// 마지막 인덱스까지 정렬이 완료되었으면 Flag 해제
				// 바로 턴이 넘어가거나 웜즈가 바로 죽는거를 방지하기 위해 삭제
				//BottomUISortStart = false;

				// 만약 현재 정렬이 종료되고 대기큐에 정렬하려는 플레이어가
				// 존재하지않다면 정렬 완전종료
				if (true == PlayerHPBarSortQueue.empty())
				{
					BottomUISortEnd = true;

					return true;
				}
			}
			else if (SortEndIndex == -1)
			{
				if (true == PlayerHPBarSortQueue.empty())
				{
					BottomUISortEnd = true;

					return true;
				}
			}
			else if (SortEndIndex < SortStartIndex)
			{
				if (true == PlayerHPBarSortQueue.empty())
				{
					BottomUISortEnd = true;

					return true;
				}
			}
			else if (SortEndIndex == SortStartIndex)
			{
				if (true == PlayerHPBarSortQueue.empty())
				{
					BottomUISortEnd = true;

					return true;
				}
			}

			for (int j = SortStartIndex + 1; j < Size; ++j)
			{
				if (PlayerHPBarList[i] == PlayerHPBarList[j])
				{
					continue;
				}

				if (PlayerHPBarList[i]->GetCurHP() < PlayerHPBarList[j]->GetCurHP())
				{
					// 실질적인 렌더링 위치를 변경하고
					float CurPlayerYPos = PlayerHPBarList[i]->GetBottomUIYPos();
					float ComparePlayerYPos = PlayerHPBarList[j]->GetBottomUIYPos();
					PlayerHPBarList[i]->SetBottomStateBarRenderPos(ComparePlayerYPos);
					PlayerHPBarList[j]->SetBottomStateBarRenderPos(CurPlayerYPos);

					// PlayerHPBarList_ 순서를 변경
					BottomStateUI* Temp = PlayerHPBarList[i];
					PlayerHPBarList[i] = PlayerHPBarList[j];
					PlayerHPBarList[j] = Temp;

					SortStartIndex = j;

					Flag = true;

					break;
				}
			}

			if (true == Flag)
			{
				Flag = false;
				break;
			}
		}
	}
	return false;
}

void GameController::CurPlayerDeathCheck()
{
	// Worm* 에서 GetDeathEnd로 받아오면 됨 // 이현

	// 현재플레이어가 죽었으므로
	//if (0 >= wormList_[currentIndex_]->GetCurHP())
	//{
		// 현재 플레이어의 상태바는 화면밖으로 내보내며
		// 현재 하단상태바 목록의 존재하는 상태들을 한칸내린다.

	//}

	// 이때 현재 플레이어 목록에 체력이 0인 플레이어가 존재한다면
	// 해당 플레이어도 상태바를 화면밖으로 내보내며 
	// 위의 플레이어목록을 재정렬한다.
	// 없다면 종료

}

void GameController::WindInit()
{
	windController_ = GetLevel()->CreateActor<WindController>();

	for (int i = 0; i < 70; i++)
	{
		BackgroundScatter* newScatter = GetLevel()->CreateActor<BackgroundScatter>();
		newScatter->SetParent(windController_);
		Cloud* newCloud = GetLevel()->CreateActor<Cloud>();
		newCloud->SetParent(windController_);
	}
	// 바람 UI 바 생성
	GetLevel()->CreateActor<WindBarBlank>();
	WindBar* windBar = GetLevel()->CreateActor<WindBar>();
	windBar->SetParentController(windController_);
	WindBarHider* windBarHider = GetLevel()->CreateActor<WindBarHider>();
	windBarHider->SetParentController(windController_);
}

void GameController::RandomTurnWind()
{
	int diceRoll = windDice_.RandomInt(1, 2);
	switch (diceRoll)
	{
	case 1:
		windController_->SetWind(WindDir::TOLEFT, 300.0f);
		break;
	case 2:
		windController_->SetWind(WindDir::TORIGHT, 300.0f);
		break;
	default:
		break;
	}
}