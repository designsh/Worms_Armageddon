#pragma once

// 분류 :
// 용도 :
// 설명 :
class GameEngineObjectBase
{
private:	// member Var
	// true라고 하는순간 메모리적으로 파괴될겁니다.
	bool isDeath_;
	// 죽지는 않고 실행만 안되게 만드는 값
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
	GameEngineObjectBase(); // default constructer 디폴트 생성자
	virtual ~GameEngineObjectBase(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineObjectBase(const GameEngineObjectBase& _other);// = delete; // default Copy constructer 디폴트 복사생성자
	//GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	//GameEngineObjectBase& operator=(const GameEngineObjectBase& _other) = delete; // default Copy operator 디폴트 대입 연산자
	//GameEngineObjectBase& operator=(const GameEngineObjectBase&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
};

