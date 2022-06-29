#pragma once
#include "EngineEnum.h"
#include <GameEngineMath.h>
#include <GameEngineDebug.h>
#include <GameEngineNameBase.h>
#include <list>
#include <Windows.h>


// �з� :
// �뵵 :
// ���� :
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
		// dynamic_cast �����Լ��� ����ϰ� �ִ� �θ��ڽİ� ���迡����
		// ������ ����ȯ�� �����ϰ� ���ִ� ������.

		// ���� �����е��� actor_�� nullptr�� �ƴѵ���
		// ����ȯ�� �ߴµ� ConvertPtr�� nullptr�̶��
		// �ٲܼ� ���� �༮�� ����Ʈ �ߴٴ� �Ҹ��̴�.

		ActorType* ConvertPtr = nullptr;
		if (nullptr != actor_)
		{
			ConvertPtr = dynamic_cast<ActorType*>(actor_);
		}

		if (nullptr == ConvertPtr)
		{
			GameEngineDebug::MsgBoxError("actor ����Ʈ ����");
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
	GameEngineCollision(); // default constructer ����Ʈ ������
	~GameEngineCollision(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineCollision(const GameEngineCollision& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineCollision(GameEngineCollision&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineCollision& operator=(const GameEngineCollision& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineCollision& operator=(const GameEngineCollision&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

