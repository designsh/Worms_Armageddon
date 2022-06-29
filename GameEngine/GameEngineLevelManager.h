#pragma once
#include <string>
#include <map>
#include <GameEngineDebug.h>


// �з� : �Ŵ���(����Ŭ����)
// �뵵 : ��������
// ���� : ������ �����
//        ������ ��ȯ�����ټ� �ִ� ����� ����մϴ�..
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
	GameEngineLevelManager(); // default constructer ����Ʈ ������
	~GameEngineLevelManager(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineLevelManager(const GameEngineLevelManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineLevelManager(GameEngineLevelManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineLevelManager& operator=(const GameEngineLevelManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineLevelManager& operator=(const GameEngineLevelManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

