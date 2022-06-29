#pragma once
#include <GameEngineDebug.h>
#include <GameEngineMath.h>
#include <sstream>

// �з� :
// �뵵 :
// ���� :
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
	GameEngineDebugExtension(); // default constructer ����Ʈ ������
	~GameEngineDebugExtension(); // default destructer ����Ʈ �Ҹ���

private:		// delete constructer
	GameEngineDebugExtension(const GameEngineDebugExtension& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineDebugExtension(GameEngineDebugExtension&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineDebugExtension& operator=(const GameEngineDebugExtension& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineDebugExtension& operator=(const GameEngineDebugExtension&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����


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

