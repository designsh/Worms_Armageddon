#pragma once
#include <GameEngineDebug.h>
#include <GameEngineMath.h>
#include <sstream>

// 분류 :
// 용도 :
// 설명 :
class GameEngineWindow;
class GameEngineDebugExtension final : public GameEngineDebug
{
public:
	static GameEngineWindow* debugWindow_;

	static std::vector<std::string> debugList_;

public:	// member Var
	static void DebugWindowOpen(float4 _Size, float4 _Scale);
	static void DebugWindowClose();
	static void Release();

private:		
	GameEngineDebugExtension(); // default constructer 디폴트 생성자
	~GameEngineDebugExtension(); // default destructer 디폴트 소멸자

private:		// delete constructer
	GameEngineDebugExtension(const GameEngineDebugExtension& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineDebugExtension(GameEngineDebugExtension&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineDebugExtension& operator=(const GameEngineDebugExtension& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineDebugExtension& operator=(const GameEngineDebugExtension&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자


private:
	static void PrintDebugWindowTextTrim()
	{
		debugList_.push_back(Str.str());
		Str = std::stringstream();
	}

	static void PrintDebugWindowText()
	{
		debugList_.push_back(Str.str());
		Str = std::stringstream();
	}

public:		//member Func
	static std::stringstream Str;

	template<typename StartType, typename ... Arg>
	static void PrintDebugWindowText(StartType _StartValue, Arg ... _Value)
	{
		Str << _StartValue;
		PrintDebugWindowText(_Value...);
	}

	template<typename StartType, typename ... Arg>
	static void PrintDebugWindowTextTrim(StartType _StartValue, Arg ... _Value)
	{
		Str << _StartValue;
		Str << "  ";
		PrintDebugWindowText(_Value...);
	}



	// static void PrintDebugWindowText(const std::string& _Text);


	static void Update();
};

