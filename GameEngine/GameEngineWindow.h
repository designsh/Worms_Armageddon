#pragma once
#include <Windows.h>
#include <string>
#include <GameEngineMath.h>
#include <GameEngineNameBase.h>

// #include "GameEngineImage.h"

// �з� : ����
// �뵵 : winapi�� ������ â�� �����ϴ� ��ɵ鿡 ���� 
//       ����(�ٸ� api�� ����� �� �Ը��� �´� Ŭ������ �ѹ� ���մ�.)���ϰ�
//       ���� �Լ����� �����Ѵ�.
// ���� : 
class GameEngineImageFile;
class GameEngineDebugExtension;
class GameEngineWindow : public GameEngineNameBase
{
private:
	friend GameEngineDebugExtension;
//private:
//	static GameEngineWindow Inst;
//
//public:
//	static GameEngineWindow& GetInst() 
//	{
//		return Inst;
//	}

private:
	static GameEngineWindow* Inst;

public:
	static GameEngineWindow& GetInst() 
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
	std::string className_;
	std::string windowTitle_;
	HINSTANCE hInstance_;
	HWND windowhandle_;
	HDC devicecontext_;

	float4 size_;
	float4 pos_;
	float4 mousepos_;

	// �̳༮�� �˰� �ֵ��� �ϰڽ��ϴ�.
	GameEngineImageFile* windowimage_;
	GameEngineImageFile* backBufferImage_;

public:
	GameEngineImageFile* GetWindowImage()
	{
		return windowimage_;
	}

	GameEngineImageFile* GetBackBuffer()
	{
		return backBufferImage_;
	}

	float4 GetSize() {
		return size_;
	}

	float4 GetPos() {
		return pos_;
	}

	float4 GetMousePos();
	bool SetMousePos(int _x, int _y);

	HWND GetMainWindowHandle() const
	{
		return windowhandle_;
	}

public:
	// ������ ���Ѱ� �޾ư����� �˾Ƽ� �ض�.
	static GameEngineWindow* CreateSubWindow(const std::string& _titlename, const float4& _size, const float4& _pos);


public:
	void CreateMainWindowClass(HINSTANCE _hInstance, std::string _className);
	void CreateMainWindow(const std::string& _titlename, const float4& _size, const float4& _pos);



	//void SetPos(const float4& _size);
	//void SetSize(const float4& _size);

	// �����찡 �����ִ� �Լ���
	// ������� �������� ���� �������ִ� �Լ��� �����.
	void SetSizeAndPos(const float4& _size, const float4& _pos);
	void Loop(void(*_loopFunc)());

private:
	GameEngineWindow();
	~GameEngineWindow();
};
