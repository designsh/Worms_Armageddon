#pragma once

#pragma warning(disable:26812)

#include "../ThirdParty/include/FMOD/fmod.hpp"

#ifdef WIN32
#pragma comment(lib, "../ThirdParty/Win32/Release/FMOD/fmod_vc.lib")
#else
#pragma comment(lib, "../ThirdParty/x64/Release/FMOD/fmod_vc.lib")
#endif

#include <unordered_map>

class GameEngineSoundPlayer;
class GameEngineSoundManager
{
	friend GameEngineSoundPlayer;
public:
	~GameEngineSoundManager();

	GameEngineSoundManager(const GameEngineSoundManager& _other) = delete;
	GameEngineSoundManager(GameEngineSoundManager&& _other) = delete;

	GameEngineSoundManager& operator=(const GameEngineSoundManager& _other) = delete;
	GameEngineSoundManager& operator=(const GameEngineSoundManager&& _other) = delete;

public:
	static GameEngineSoundManager& GetInstance() { return *instance_; }
	static void Destroy();

	void Initialize();
	void Update();

	void CreateSound(const std::string& _name, const std::string& _path, bool _bLoop = false);
	
	void PlaySoundByName(const std::string& _name);
	void SetVolume(unsigned int _volume);
	void StopSound();

private:
	GameEngineSoundManager();

	FMOD::Sound* getSound(const std::string& _name);

private:
	static GameEngineSoundManager* instance_;

private:
	FMOD::System* system_;
	FMOD::Channel* channel_;

	std::unordered_map<std::string, FMOD::Sound*> allSounds_;
};

