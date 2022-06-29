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

GameController::GameController() // default constructer ����Ʈ ������
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

GameController::~GameController() // default destructer ����Ʈ �Ҹ���
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

	// TODO : �׽�Ʈ�� ���� �� ����
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
		// ���Լ����� ������ Ȱ���Ͽ� �״��� ���� �׸��� ������
		BottomStateUI* QueueState = PlayerHPBarSortQueue.front();

		// ���Ľ����ϹǷ� ť���� ����
		PlayerHPBarSortQueue.pop();

		// ���� ����
		BottomStateHPBarSortCheck(QueueState);
	}
}

void GameController::Update()
{
	// �¸��Ͽ����Ƿ� ���� ü����
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

	// ���� �÷��̾ 1���̹Ƿ� �¸��� �Ǵ�
	// ���� �÷��̾ ���ٸ� ���ºη� �Ǵ�
	if (1 == wormList_.size())
	{
		// �����÷��̾ �¸����·� ��ȯ
		wormList_[0]->ChangeState("Win");

		// Flag On
		GameEndFlag = true;
		return;
	}
	else if (0 == wormList_.size())
	{
		// ���� �÷��̾ �����Ƿ� FadeIn/Outó�� �� ���������� ��ȯ
		GameEndFlag = true;

		return;
	}

	// �÷��̾ ����ؼ� UI�� ���������¶��
	// ������ �ϴܹٿ� ���� ��ġ ������
	//if (true == BottomUISortEnd)
	//{
	//	BottomUISortEnd = false;

	//	// ���⼭ ���� ��� �÷��̾ ������ ����Ǿ����Ƿ�
	//	// ��� �÷��̾��� ü�»��¸� üũ�Ѵ�.
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

	//TODO : ���� �༮ ã�ƴٰ� ��Ŀ�� �������

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
			// ������Ʈ ����� 1�̴� == �Ѹ� ��Ƴ��� ���´�
			float4 cameraMovePos = wormList_[0]->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4();
			float4 MoveVector = cameraMovePos - cameraPos_;

			GetLevel()->SetCamMove(MoveVector * 0.1f);
			return;
		}

		// ����� ���� �����Ѵٸ� ī�޶� ��Ŀ�� ���(���������� �Ѿ���°��Ǹ� ������Ʈ ī��Ʈ�� ��������
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
		GameEngineDebug::MsgBoxError("�ִ� ������ ������ �ʰ��Ͽ����ϴ�.");
		return;
	}

	GameEngineMath::Random randomGenerator;
	std::string name = "Worm";
	name += std::to_string(currentIndex_++);
	Worm* newWorm = parentLevel_->CreateActor<Worm>(name);
	wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // ���� ������ ��ǥ�� ��������� ����

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
	prevwormSize_ = static_cast<int>(wormList_.size());
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

		// UI�����ڻ���
		UIController* CurUIController = parentLevel_->CreateActor<UIController>(Name);
		CurUIController->SetCurPlayer(wormList_[i]);

		// �÷��̾�� UIController ����
		wormList_[i]->SetUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetParentController(wormList_[i]->GetCurUIController());

		// �÷��̾�� ��� ���� UI
		wormList_[i]->GetCurUIController()->GetCurTopState()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTopState()->SetParentUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurTopState()->GameStartInit(static_cast<int>(i));

		// �÷��̾�� �� Ÿ�̸� UI ����
		wormList_[i]->GetCurUIController()->GetCurTimerWindow()->RenderColorInit(static_cast<int>(i));
		wormList_[i]->GetCurUIController()->GetCurTimerWindow()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTimerDigitTen()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTimerDigit()->SetParentWorm(wormList_[i]);

		// �÷��̾�� ü��ǥ���ؽ�Ʈ UI ����
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

		// �÷��̾�� ����â ���� �� Ȱ��ȭ ���� ����
		std::string SheetName = wormList_[i]->GetName();
		SheetName += "_WeaponSheet";
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetName(SheetName);

		// �ʱ� ������ �������
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
		CurUIController->CreateWeaponList(ItemListTest);				// �÷��̾ ó�� �������ִ� �����۸��(��������)

		// ����â ��� �����
		//CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// �÷��̾ ��Ϳ�����Ʈ ȹ������ ���� ����ȹ��� ȣ��(���ο���߰� �Ǵ� �������ⰳ������)
		//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// �÷��̾ ������������ ȣ��(�������ִ� ���ⰳ������)
		ItemListTest.clear();

		// �÷��̾�� �ϴ� ���� UI
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->GameStartInit(static_cast<int>(i));

		// �÷��̾� �ϴ� ���¹ٰ��� ������Ͽ� �߰�
		PlayerHPBarList[i] = wormList_[i]->GetCurUIController()->GetCurBottomState();
	}
}

void GameController::CreateDrum(const float _minX, const float _maxX)
{
	GameEngineMath::Random randomGenerator;
	DrumActor* newDrum = parentLevel_->CreateActor<DrumActor>();
	wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // ���� ������ ��ǥ�� ��������� ����

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
		//TODO : �̺κ� ������ �ʿ��� ����
		//6���� ���� ���������� ���̰� ������ 1������ �������� UpdateAfter���� ������ �߻�����, 
		//wormlist_ ���� [0]�� ���Ҵµ� �ε����� 1�ΰ��
		// �׳� ���ε��� �ý����� ���ְ� �� ���� ������ ����Ʈ�� ������ ���°� ��� ��

		prevwormIndex_ = wormIndex_;

		// ���⼭ ����� ��� �ִ��� üũ
		if (prevwormSize_ != static_cast<int>(wormList_.size()))
		{
			// ����ߴ� ���� �ε����� ���� WormIndex�� ���� ��,
			// ����� ���� �������ε������ٸ� -1


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

	// ���� ��Ÿ�Ӽ��ÿ� ���� ��Ÿ���� �޶��� - 220207 SJH ����
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
	// Ÿ�̸� ������ �� ����ϴ� �κ�
	currentWorm_->GetCurUIController()->GetCurTimerDigitTen()->SetTenDigitTime(currentTurnTime_);
	currentWorm_->GetCurUIController()->GetCurTimerDigit()->SetDigitTime(currentTurnTime_);

	if (GameEngineInput::GetInst().IsDown("TestKey"))
	{
		currentWorm_->SubtractActionToken(1);

		// ������ȯ�������� ����â �� ��������� ��Ȱ��ȭ
		currentWorm_->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		currentTurnTime_ = 0.0f;
	}

	if (currentTurnTime_ < 0 || 0 >= currentWorm_->GetActionTokenCount())
	{
		// �Ͻð� �ʰ� or ��ū �������� ���� �÷��̾� ��ȯ�� �߻��ϹǷ� �̰�����
		// ����â ��Ȱ���� �ȴ�.
		currentWorm_->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		// ���Ÿ�� �ʰ� �� �÷��̾� ���ʰ��� ������ ���
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

	// Damage�� ���� ��� ������ �ٷ� �ѱ�
	if (false == DamageFlag)
	{
		BottomUISortEnd = false;
		return "DeathCheck";
	}

	// UI ���� �Ϸ� ������ �ѱ��ȉ�
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

		// ���⼭ ���� ��� �÷��̾ ������ ����Ǿ����Ƿ�
		// ��� �÷��̾��� ü�»��¸� üũ�Ѵ�.
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
	// ���丮 ������Ʈ���� �̷л� ������Ʈ�� ���� �� �����ۿ� �����ϴ�.
	// ������ ������ ī�޶� ��Ŀ�̵Ǹ� �ش� ���� Win ������Ʈ�� �����մϴ�.
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
	WaterLevel_ = GetLevel()->CreateActor<WaterLevel>("WaterLevel"); // ��� �ĵ� actor �׷�ȭ
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
	// ���� �̹� �ٸ� �÷��̾� Bottom HPBar�� �������̶��
	// ���ť�� �ش� �÷��̾�UI����
	if (true == BottomUISortStart)
	{
		PlayerHPBarSortQueue.push(_CurUI);
	}
	else
	{
		// ���� �÷��̾��� ü�¿� ���� ���� ����
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
				// �÷��̾ �̹� �Ѹ����̹Ƿ�
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
			else if (SortStartIndex == Size - 1) // �̹� ���� ���� ü���� �÷��̾�
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
			// ���� ������ ���Ĵ�⿭�� ������ HPBar�� �����Ѵٸ�
			// �ش� HPBar���� ����
			if (SortStartIndex == SortEndIndex && 1 != Size)
			{
				// ������ �ε������� ������ �Ϸ�Ǿ����� Flag ����
				// �ٷ� ���� �Ѿ�ų� ��� �ٷ� �״°Ÿ� �����ϱ� ���� ����
				//BottomUISortStart = false;

				// ���� ���� ������ ����ǰ� ���ť�� �����Ϸ��� �÷��̾
				// ���������ʴٸ� ���� ��������
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
					// �������� ������ ��ġ�� �����ϰ�
					float CurPlayerYPos = PlayerHPBarList[i]->GetBottomUIYPos();
					float ComparePlayerYPos = PlayerHPBarList[j]->GetBottomUIYPos();
					PlayerHPBarList[i]->SetBottomStateBarRenderPos(ComparePlayerYPos);
					PlayerHPBarList[j]->SetBottomStateBarRenderPos(CurPlayerYPos);

					// PlayerHPBarList_ ������ ����
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
	// Worm* ���� GetDeathEnd�� �޾ƿ��� �� // ����

	// �����÷��̾ �׾����Ƿ�
	//if (0 >= wormList_[currentIndex_]->GetCurHP())
	//{
		// ���� �÷��̾��� ���¹ٴ� ȭ������� ��������
		// ���� �ϴܻ��¹� ����� �����ϴ� ���µ��� ��ĭ������.

	//}

	// �̶� ���� �÷��̾� ��Ͽ� ü���� 0�� �÷��̾ �����Ѵٸ�
	// �ش� �÷��̾ ���¹ٸ� ȭ������� �������� 
	// ���� �÷��̾����� �������Ѵ�.
	// ���ٸ� ����

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
	// �ٶ� UI �� ����
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