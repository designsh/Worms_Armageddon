#pragma once
#include <map>
#include <string>
#include <list>
#include <vector>
#include <Windows.h>

// 분류 :
// 용도 :
// 설명 :
class GameEngineLevelManager;
class GameEngineImageFile;
class GameEngineWindow;
class GameEngineImage
{
public:
	friend GameEngineLevelManager;
	friend GameEngineWindow;

private:
	static GameEngineImage* Inst;

public:
	static GameEngineImage& GetInst()
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
	GameEngineImageFile* windowimage_;
	GameEngineImageFile* backBufferImage_;

private:
	// 최초 시작할때 윈도우의 DC를 받아서 이미지를 하나 만들다.
	// 모든 랜더링을 할때
	void InitializeWindowImage(HDC _windowbackgroundDc);
	void DoubleBuffering();
	void ClearBackBuffer();

public:
	GameEngineImageFile* GetBackBufferImage();

private:	// member Var
	std::map<std::string, GameEngineImageFile*> globalManagedimages_;

public:
	GameEngineImageFile* LoadGameImage(std::string _name, std::string _path);

	GameEngineImageFile* FindGameImage(std::string _name);

	std::vector<std::string> FindAllSpecKeyImage(const std::string& _SpecKey);

public:		
	GameEngineImage(); // default constructer 디폴트 생성자
	~GameEngineImage(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineImage(const GameEngineImage& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineImage(GameEngineImage&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineImage& operator=(const GameEngineImage& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineImage& operator=(const GameEngineImage&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
};

