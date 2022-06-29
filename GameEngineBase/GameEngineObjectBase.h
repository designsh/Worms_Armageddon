#pragma once

// �з� :
// �뵵 :
// ���� :
class GameEngineObjectBase
{
private:	// member Var
	// true��� �ϴ¼��� �޸������� �ı��ɰ̴ϴ�.
	bool isDeath_;
	// ������ �ʰ� ���ุ �ȵǰ� ����� ��
	bool isUpdate_;

	bool isDebug_;

	GameEngineObjectBase* parent_;

public:
	void SetParent(GameEngineObjectBase* _parent) 
	{
		parent_ = _parent;
	}

public:
	bool IsDeath()
	{
		if (nullptr == parent_)
		{
			return isDeath_;
		}

		return true == isDeath_ || parent_->isDeath_;
	}

	bool IsOn()
	{
		if (nullptr == parent_)
		{
			return isUpdate_;
		}

		return true == isUpdate_ && parent_->isUpdate_;
	}


	void Death()
	{
		isDeath_ = true;
	}

	void On()
	{
		isUpdate_ = true;
	}

	void Off()
	{
		isUpdate_ = false;
	}

	void DebugOn()
	{
		isDebug_ = true;
	}

	void DebugOff()
	{
		isDebug_ = false;
	}

	bool IsDebugOn()
	{
		return isDebug_;
	}

public:		
	GameEngineObjectBase(); // default constructer ����Ʈ ������
	virtual ~GameEngineObjectBase(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineObjectBase(const GameEngineObjectBase& _other);// = delete; // default Copy constructer ����Ʈ ���������
	//GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	//GameEngineObjectBase& operator=(const GameEngineObjectBase& _other) = delete; // default Copy operator ����Ʈ ���� ������
	//GameEngineObjectBase& operator=(const GameEngineObjectBase&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
};
