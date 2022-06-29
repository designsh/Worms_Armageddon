#include "GameEngineSoundPlayer.h"

GameEngineSoundPlayer::GameEngineSoundPlayer(const std::string& _soundName)
	: sound_(nullptr)
	, channel_(nullptr)
{
	sound_ = GameEngineSoundManager::GetInstance().getSound(_soundName);
}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{
}

void GameEngineSoundPlayer::ChangeSound(const std::string& _soundName)
{
	sound_ = GameEngineSoundManager::GetInstance().getSound(_soundName);
}

void GameEngineSoundPlayer::Play()
{
	GameEngineSoundManager::GetInstance().system_->playSound(sound_, nullptr, false, &channel_);
}

void GameEngineSoundPlayer::Stop()
{
	FMOD_RESULT result = channel_->stop();
}

bool GameEngineSoundPlayer::IsPlaying()
{
	bool bReturn;
	FMOD_RESULT result = channel_->isPlaying(&bReturn);
	return bReturn;
}

bool GameEngineSoundPlayer::IsPaused()
{
	bool bReturn = true;
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->getPaused(&bReturn);
	}
	return bReturn;
}

void GameEngineSoundPlayer::SetPaused(bool _bPause)
{
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setPaused(_bPause);
	}
}

void GameEngineSoundPlayer::SetVolume(float _volume)
{
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setVolume(_volume);
	}
}

void GameEngineSoundPlayer::SetPitch(float _pitch)
{
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setPitch(_pitch);
	}
}

void GameEngineSoundPlayer::SetPosition(unsigned int _positionMilliSec)
{
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setPosition(_positionMilliSec, FMOD_TIMEUNIT_MS);
	}
}

unsigned int GameEngineSoundPlayer::GetPositionMillisecond()
{
	unsigned int returnPosition;
	FMOD_RESULT result = channel_->getPosition(&returnPosition, FMOD_TIMEUNIT_MS);
	return returnPosition;
}

unsigned int GameEngineSoundPlayer::GetLengthMillisecond()
{
	unsigned int returnLength;
	FMOD_RESULT result = sound_->getLength(&returnLength, FMOD_TIMEUNIT_MS);
	return returnLength;
}
