#pragma once
#include "EngineEnum.h"
#include <GameEngineMath.h>
#include <GameEngineDebug.h>
#include <GameEngineNameBase.h>
#include <list>
#include <Windows.h>


// 분류 :
// 용도 :
// 설명 :
class GameEngineActor;
class GameEngineLevel;
class GameEngineImageFile;
class GameEngineLevelManager;
class GameEngineCollision : public GameEngineNameBase
{
private:
	static bool (*arrFunc_[static_cast<int>(CollisionCheckType::MAX)][static_cast<int>(CollisionCheckType::MAX)])(GameEngineCollision* _PointCol, GameEngineCollision* _ImageCol);
	static void ColCheckFuncInitialize();

public:

	//static bool RectToImage(GameEngineCollision* _PointCol, GameEngineCollision* _ImageCol);

	static bool PointToImage(GameEngineCollision* _PointCol, GameEngineCollision* _ImageCol);
	static bool ImageToPoint(GameEngineCollision* _ImageCol, GameEngineCollision* _PointCol);

	static bool RectToPoint(GameEngineCollision* _left, GameEngineCollision* _right);
	static bool RectToRect(GameEngineCollision* _left, GameEngineCollision* _right);
	static bool collisionCheckRectToCircle(GameEngineCollision* lhs, GameEngineCollision* rhs);

	static bool PointToPoint(GameEngineCollision* _left, GameEngineCollision* _right);
	static bool PointToRect(GameEngineCollision* _left, GameEngineCollision* _right);
	static bool collisionCheckPointToCircle(GameEngineCollision* lhs, GameEngineCollision* rhs);

	static bool collisionCheckCircleToPoint(GameEngineCollision* lhs, GameEngineCollision* rhs);
	static bool collisionCheckCircleToRect(GameEngineCollision* lhs, GameEngineCollision* rhs);
	static bool collisionCheckCircleToCircle(GameEngineCollision* lhs, GameEngineCollision* rhs);

public:
	float4 GetCollisionPoint() const;
	FRect GetCollisionRect() const;
	void SetRadius(float _radius);
	void SetRect(FRect _rect);
	void SetRect(float _left, float _top, float _right, float _bottom);

private:
	friend GameEngineLevelManager;
	friend GameEngineLevel;
	friend GameEngineActor;

private:
	GameEngineActor* actor_;
	float4 Pivot_;
	float4 size_;

	bool CollisionOn_;

	float radius_;
	FRect rect_;

	CollisionCheckType colType_;
	int groupIndex_;

	GameEngineImageFile* imageptr_;
	DWORD CheckColor;

private:
	float4 GetCollisionPos();

public:
	void CollisionOn()
	{
		CollisionOn_ = true;
	}
	void CollisionOff()
	{
		CollisionOn_ = false;
	}

	bool GetCollision_On_Off()
	{
		return CollisionOn_;
	}

	GameEngineActor* GetActor()
	{
		return actor_;
	}

	template<typename ActorType>
	ActorType* GetActorConvert()
	{
		// dynamic_cast 가상함수를 사용하고 있는 부모자식간 관계에서만
		// 안전한 형변환이 가능하게 해주는 연산자.

		// 만약 여러분들이 actor_가 nullptr이 아닌데도
		// 형변환을 했는데 ConvertPtr이 nullptr이라면
		// 바꿀수 없는 녀석을 컨버트 했다는 소리이다.

		ActorType* ConvertPtr = nullptr;
		if (nullptr != actor_)
		{
			ConvertPtr = dynamic_cast<ActorType*>(actor_);
		}

		if (nullptr == ConvertPtr)
		{
			GameEngineDebug::MsgBoxError("actor 컨버트 에러");
		}

		return ConvertPtr;
	}

public:
	void SetImage(std::string _ImageName);

public:
	void SetColorCheck(DWORD _Color)
	{
		CheckColor = _Color;
	}

	void SetGroupIndex(int _Index)
	{
		groupIndex_ = _Index;
	}

	void SetColType(CollisionCheckType _colType)
	{
		colType_ = _colType;
	}

	void SetPivot(float4 _pivot)
	{
		Pivot_ = _pivot;
	}

	void SetSize(float4 _size)
	{
		size_ = _size;
	}

public:
	int GetTypeToIndex()
	{
		return static_cast<int>(colType_);
	}

	int GetGroupIndex()
	{
		return groupIndex_;
	}

	DWORD GetColorCheck()
	{
		return CheckColor;
	}

	float4 GetDebugRenderPos();

	bool isCamEffect_;
	
	float4 GetSize()
	{
		return size_;
	}

private:
	void SetActor(GameEngineActor* _parent)
	{
		actor_ = _parent;
	}

private:
	GameEngineCollision(); // default constructer 디폴트 생성자
	~GameEngineCollision(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineCollision(const GameEngineCollision& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineCollision(GameEngineCollision&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineCollision& operator=(const GameEngineCollision& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineCollision& operator=(const GameEngineCollision&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	// Debug
	void DebugRender();

	// CollisionCheck
	bool CollisionCheck(GameEngineCollision* _other);

	template<typename COLGROUP>
	GameEngineCollision* CollisionGroupCheckOne(COLGROUP _otherGroup)
	{
		return CollisionGroupCheckOne(static_cast<int>(_otherGroup));
	}

	GameEngineCollision* CollisionGroupCheckOne(int _otherIndex);
	std::list<GameEngineCollision*> CollisionGroupCheck(int _otherIndex);

public:
	Figure GetFigure();

};

