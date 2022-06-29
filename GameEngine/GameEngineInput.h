#pragma once
#include <GameEngineNameBase.h>
#include <map>
#include <list>
#include <Windows.h>

// 분류 :
// 용도 :
// 설명 :
class GameEngineWindow;
class GameEngineInput
{
	friend GameEngineWindow;

private:	// member Var
	class GameEngineKey : public GameEngineNameBase
	{
		friend GameEngineInput;

	private:
		bool down_; // 최초 1회 눌렸을때 true 이번 프레임에 한번 체크가 됩니다.
		bool press_; // 지속적으로 누를때 true
		bool up_; // 이번 프레임에 1번만 땠다
		bool free_; // 지금 안누르고 있다.
		int key_; // 내가 누르려는 키의 인덱스 혹은 타입

	public:
		void Update();

	private:
		GameEngineKey();
		~GameEngineKey();
	};

private:
	static GameEngineInput* Inst;

public:
	static GameEngineInput& GetInst()
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
	// 100개 이하라면 아무의미 없다.
	std::map<std::string, GameEngineKey*> allkeys_;

public:		
	GameEngineInput(); // default constructer 디폴트 생성자
	~GameEngineInput(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineInput(const GameEngineInput& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineInput(GameEngineInput&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineInput& operator=(const GameEngineInput& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineInput& operator=(const GameEngineInput&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	bool CreateKey(const std::string _name, int _key);

	bool IsDown(const std::string _name);
	bool IsUp(const std::string _name);
	bool IsPress(const std::string _name);
	bool IsFree(const std::string _name);

	// 이 키를 만든적이 있어?
	bool IsKey(const std::string _name);


private:
	GameEngineKey* FindKey(const std::string _name);
	void Update();
};

