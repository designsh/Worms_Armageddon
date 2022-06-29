#include "GameEngineInput.h"
#include "GameEngineWindow.h"
#include <GameEngineDebug.h>

// Static Var

GameEngineInput* GameEngineInput::Inst = new GameEngineInput();

// Static Func

GameEngineInput::GameEngineKey::GameEngineKey()
	:
	down_(false),
	press_(false),
	up_(false),
	free_(true),
	key_(-1)
{

}

GameEngineInput::GameEngineKey::~GameEngineKey() 
{

}

void GameEngineInput::GameEngineKey::Update()
{
	if (0 != GetAsyncKeyState(key_))
	{
		// 그 키가 눌렸다.
		//bool down_; 
		//bool press_; 
		//bool up_; 
		//bool free_; 
		
		// 이전까지 눌린적이 없다.
		if (false == press_)
		{
			down_ = true;
			press_ = true;
			up_ = false;
			free_ = false;
		}
		// 이전에 눌렸다.
		else if(true == press_)
		{
			down_ = false;
			press_ = true;
			up_ = false;
			free_ = false;
		}
	}
	else
	{
		// 방금전까지도 키가 눌려있었다.
		if (true == press_)
		{
			down_ = false;
			press_ = false;
			up_ = true;
			free_ = false;
		}
		else if (false == press_)
		{
			// 최초 상태로 돌아온다.
			down_ = false;
			press_ = false;
			up_ = false;
			free_ = true;
		}


	}
}


// constructer destructer
GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
	std::map<std::string, GameEngineKey*>::iterator KeyStart = allkeys_.begin();
	std::map<std::string, GameEngineKey*>::iterator KeyEnd = allkeys_.end();

	for (; KeyStart != KeyEnd; ++KeyStart)
	{
		if (nullptr == KeyStart->second)
		{
			continue;
		}

		delete KeyStart->second;
		KeyStart->second = nullptr;
	}

	allkeys_.clear();
}

GameEngineInput::GameEngineInput(GameEngineInput&& _other) noexcept
{
}

//member Func

GameEngineInput::GameEngineKey* GameEngineInput::FindKey(const std::string _name) 
{
	std::map<std::string, GameEngineKey*>::iterator FindIter = allkeys_.find(_name);

	if (FindIter == allkeys_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

bool GameEngineInput::IsKey(const std::string _name) 
{
	GameEngineKey* FindKeyPtr = FindKey(_name);

	if (nullptr == FindKeyPtr)
	{
		return false;
	}

	return true;
}


bool GameEngineInput::IsDown(const std::string _name)
{
	GameEngineKey* FindKeyPtr = FindKey(_name);

	if (nullptr == FindKeyPtr)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	return FindKeyPtr->down_;
}


bool GameEngineInput::IsUp(const std::string _name)
{
	GameEngineKey* FindKeyPtr = FindKey(_name);

	if (nullptr == FindKeyPtr)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	return FindKeyPtr->up_;
}
bool GameEngineInput::IsPress(const std::string _name)
{
	GameEngineKey* FindKeyPtr = FindKey(_name);

	if (nullptr == FindKeyPtr)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	return FindKeyPtr->press_;
}
bool GameEngineInput::IsFree(const std::string _name)
{
	GameEngineKey* FindKeyPtr = FindKey(_name);

	if (nullptr == FindKeyPtr)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	return FindKeyPtr->free_;
}

bool GameEngineInput::CreateKey(const std::string _name, int _key)
{
	if ('a' <= _key && 'z' >= _key)
	{
		_key = std::toupper(_key);
	}

	GameEngineKey* NewKey = new GameEngineKey();
	NewKey->key_ = _key;
	NewKey->SetName(_name);

	allkeys_.insert(std::map<std::string, GameEngineKey*>::value_type(_name, NewKey));
	return true;
}


void GameEngineInput::Update()
{
	std::map<std::string, GameEngineKey*>::iterator KeyStart = allkeys_.begin();
	std::map<std::string, GameEngineKey*>::iterator KeyEnd = allkeys_.end();

	for (; KeyStart != KeyEnd; ++KeyStart)
	{
		KeyStart->second->Update();
	}
}