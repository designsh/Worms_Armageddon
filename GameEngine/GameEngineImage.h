#pragma once
#include <map>
#include <string>
#include <list>
#include <vector>
#include <Windows.h>

// �з� :
// �뵵 :
// ���� :
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
	// ���� �����Ҷ� �������� DC�� �޾Ƽ� �̹����� �ϳ� �����.
	// ��� �������� �Ҷ�
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
	GameEngineImage(); // default constructer ����Ʈ ������
	~GameEngineImage(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineImage(const GameEngineImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineImage(GameEngineImage&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineImage& operator=(const GameEngineImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineImage& operator=(const GameEngineImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
};

