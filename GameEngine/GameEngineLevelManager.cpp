#include "GameEngineLevelManager.h"
#include "GameEngineLevel.h"
#include "GameEngineImage.h"
#include "GameEngineCollision.h"
#include <GameEngineTime.h>

// Static Var
GameEngineLevelManager* GameEngineLevelManager::Inst = new GameEngineLevelManager();

// Static Func

// constructer destructer
GameEngineLevelManager::GameEngineLevelManager()
	: allLevel_(), curLevel_(nullptr), nextLevel_(nullptr)
{
}

GameEngineLevelManager::~GameEngineLevelManager()
{
	std::map<std::string, GameEngineLevel*>::iterator StartIter = allLevel_.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = allLevel_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}
	allLevel_.clear();

	// ranged for
	//for (std::map<std::string, Level*>::value_type& level : allLevel_)
	//{
	//	if (nullptr != level.second)
	//	{
	//		delete level.second;
	//		level.second = nullptr;
	//	}
	//}
	//allLevel_.clear();
}

GameEngineLevelManager::GameEngineLevelManager(GameEngineLevelManager&& _other) noexcept
{
}


void GameEngineLevelManager::ChangeLevel(std::string _levelname, bool _Reset /*= false*/)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = allLevel_.find(_levelname);

	if (allLevel_.end() == FindIter)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineCollision::ColCheckFuncInitialize();

	nextLevel_ = FindIter->second;

	if (true == _Reset)
	{
		nextLevel_->Reset();
	}

	// curLevel_ = FindIter->second;
}

void GameEngineLevelManager::Update()
{
	if (nullptr != nextLevel_)
	{
		// 다음레벨이 존재한다는 거니까.

		// Level이 이전까지 세팅된적이 없었다.
		// 최초로 레벨이 바뀌는 순간
		if (nullptr == curLevel_)
		{
			curLevel_ = nextLevel_;
		}
		// 이전레벨이 있었다는것
		else 
		{
			curLevel_ = nextLevel_;
		}


		nextLevel_ = nullptr;
		GameEngineTime::GetInst().TimeCheckReset();
	}

	if (true == curLevel_->isReset_)
	{
		curLevel_->Clear();
		curLevel_->Loading();
		curLevel_->isReset_ = false;
		GameEngineTime::GetInst().TimeCheckReset();
	}

	// 프레임이 시작할때 바뀌는게 가장 안전하다.

	// 업데이트 오더체크는 업데이트를 하기전에
	// 실행순서가 바뀌는 액터를 체크해서 순서를 변경해주는 작업을 합니다.
	curLevel_->UpdateOrderCheck();
	curLevel_->RenderOrderCheck();
	curLevel_->CollisionOrderCheck();

	// 레벨의 업데이트는 언제나 액터보다 먼저 돈다.
	curLevel_->LevelUpdateBefore();
	curLevel_->UpdateBefore();

	curLevel_->LevelUpdate();
	// Title
	curLevel_->Update();
	// Play
	curLevel_->LevelUpdateAfter();
	curLevel_->UpdateAfter();

	GameEngineImage::GetInst().ClearBackBuffer();
	curLevel_->Render();
	GameEngineImage::GetInst().DoubleBuffering();

	curLevel_->Collision();

	curLevel_->Release();
	

}

void GameEngineLevelManager::ChangeLevelCheck()
{

}