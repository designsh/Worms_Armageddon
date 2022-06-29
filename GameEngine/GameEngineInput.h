#pragma once
#include <GameEngineNameBase.h>
#include <map>
#include <list>
#include <Windows.h>

// �з� :
// �뵵 :
// ���� :
class GameEngineWindow;
class GameEngineInput
{
	friend GameEngineWindow;

private:	// member Var
	class GameEngineKey : public GameEngineNameBase
	{
		friend GameEngineInput;

	private:
		bool down_; // ���� 1ȸ �������� true �̹� �����ӿ� �ѹ� üũ�� �˴ϴ�.
		bool press_; // ���������� ������ true
		bool up_; // �̹� �����ӿ� 1���� ����
		bool free_; // ���� �ȴ����� �ִ�.
		int key_; // ���� �������� Ű�� �ε��� Ȥ�� Ÿ��

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
	// 100�� ���϶�� �ƹ��ǹ� ����.
	std::map<std::string, GameEngineKey*> allkeys_;

public:		
	GameEngineInput(); // default constructer ����Ʈ ������
	~GameEngineInput(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineInput(const GameEngineInput& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineInput(GameEngineInput&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineInput& operator=(const GameEngineInput& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineInput& operator=(const GameEngineInput&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	bool CreateKey(const std::string _name, int _key);

	bool IsDown(const std::string _name);
	bool IsUp(const std::string _name);
	bool IsPress(const std::string _name);
	bool IsFree(const std::string _name);

	// �� Ű�� �������� �־�?
	bool IsKey(const std::string _name);


private:
	GameEngineKey* FindKey(const std::string _name);
	void Update();
};

