#pragma once
#include <string>
#include <map>
#include <GameEngineDebug.h>


// 분류 : 매니저(관리클래스)
// 용도 : 레벨관리
// 설명 : 레벨을 만들고
//        레벨을 전환시켜줄수 있는 기능을 담당합니다..
class GameEngineLevel;
class GameEngineLevelManager
{
private:	// member Var

private:
	static GameEngineLevelManager* Inst;

public:
	static GameEngineLevelManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:
	std::map<std::string, GameEngineLevel*> allLevel_;
	GameEngineLevel* curLevel_;
	GameEngineLevel* nextLevel_;

public:
	GameEngineLevel* GetCurLevel()
	{
		return curLevel_;
	}

public:
	void Update();

private:		
	GameEngineLevelManager(); // default constructer 디폴트 생성자
	~GameEngineLevelManager(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineLevelManager(const GameEngineLevelManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineLevelManager(GameEngineLevelManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineLevelManager& operator=(const GameEngineLevelManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineLevelManager& operator=(const GameEngineLevelManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	template<typename LevelType> 
	void CreateLevel(std::string _levelname)
	{
		if (allLevel_.end() != allLevel_.find(_levelname))
		{
			GameEngineDebug::AssertFalse();
			return;
		}

		GameEngineLevel* NewLevel = new LevelType();
		NewLevel->LevelLoading();
		NewLevel->SetName(_levelname);

		allLevel_.insert(std::map<std::string, GameEngineLevel*>::value_type(
			_levelname, NewLevel));
	}

	void ChangeLevel(std::string _levelname, bool _Reset = false);

private:
	void ChangeLevelCheck();
};

