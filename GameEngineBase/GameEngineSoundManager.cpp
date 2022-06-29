#include "GameEngineSoundManager.h"
#include "GameEngineDebug.h"

#include <Windows.h>

GameEngineSoundManager* GameEngineSoundManager::instance_ = new GameEngineSoundManager;

GameEngineSoundManager::GameEngineSoundManager()
	: system_(nullptr)
	, channel_(nullptr)
{
}

FMOD::Sound* GameEngineSoundManager::getSound(const std::string& _name)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = allSounds_.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = allSounds_.end();

	if (findIter == endIter)
	{
		GameEngineDebug::MsgBoxError("No Sounds.");
		return nullptr;
	}

	return findIter->second;
}

GameEngineSoundManager::~GameEngineSoundManager()
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator startIter = allSounds_.begin();
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = allSounds_.end();

	while (startIter != endIter)
	{
		startIter->second->release();
		++startIter;
	}

	allSounds_.clear();

	system_->close();
	system_->release();
}

void GameEngineSoundManager::Initialize()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&system_);
	if (FMOD_OK != result)
	{
		GameEngineDebug::MsgBoxError("FMOD system create failed.");
	}

	result = system_->init(32, FMOD_INIT_NORMAL, nullptr);
	if (FMOD_OK != result)
	{
		GameEngineDebug::MsgBoxError("FMOD system initialize failed.");
	}
}

void GameEngineSoundManager::Update()
{
	if (nullptr == system_)
	{
		GameEngineDebug::AssertFalse();
	}

	system_->update();
}

void GameEngineSoundManager::CreateSound(const std::string& _name, const std::string& _path, bool _bLoop)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = allSounds_.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = allSounds_.end();

	if (findIter != endIter)
	{
		findIter->second->release();
	}

	FMOD_RESULT result;
	FMOD::Sound* newSound;
	FMOD_MODE mode = FMOD_DEFAULT;

	if (_bLoop)
	{
		mode = FMOD_LOOP_NORMAL;
	}

	result = system_->createSound(_path.c_str(), mode, nullptr, &newSound);

	if (FMOD_OK != result)
	{
		GameEngineDebug::MsgBoxError("createSound failed.");
	}

	allSounds_[_name] = newSound;
}

void GameEngineSoundManager::PlaySoundByName(const std::string& _name)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = allSounds_.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = allSounds_.end();

	if (findIter == endIter)
	{
		GameEngineDebug::MsgBoxError("No Sounds.");
	}

	system_->playSound(findIter->second, 0, false, &channel_);
}

void GameEngineSoundManager::SetVolume(unsigned int _volume)
{
}

void GameEngineSoundManager::StopSound()
{
	channel_->stop();
}

void GameEngineSoundManager::Destroy()
{

	if (nullptr != instance_)
	{
		delete instance_;
		instance_ = nullptr;
	}
}
