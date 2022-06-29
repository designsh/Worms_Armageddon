#pragma once
#include <Windows.h>
#include <string>
#include <GameEngineMath.h>
#include <GameEngineNameBase.h>

// #include "GameEngineImage.h"

// 분류 : 엔진
// 용도 : winapi의 윈도우 창을 제어하는 기능들에 대한 
//       랩핑(다른 api의 기능을 내 입맛에 맞는 클래스로 한번 감쌌다.)을하고
//       편의 함수들을 제공한다.
// 설명 : 
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

	// 이녀석도 알고 있도록 하겠습니다.
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
	// 삭제에 대한건 받아간쪽이 알아서 해라.
	static GameEngineWindow* CreateSubWindow(const std::string& _titlename, const float4& _size, const float4& _pos);


public:
	void CreateMainWindowClass(HINSTANCE _hInstance, std::string _className);
	void CreateMainWindow(const std::string& _titlename, const float4& _size, const float4& _pos);



	//void SetPos(const float4& _size);
	//void SetSize(const float4& _size);

	// 윈도우가 지원주는 함수가
	// 사이즈와 포지션을 각가 지정해주는 함수가 없어요.
	void SetSizeAndPos(const float4& _size, const float4& _pos);
	void Loop(void(*_loopFunc)());

private:
	GameEngineWindow();
	~GameEngineWindow();
};
