#pragma once
#include <list>
#include <map>
#include <string>
#include <GameEngineDebug.h>
#include <GameEngineNameBase.h>
#include <GameEngineMath.h>


// �з� :
// �뵵 :
// ���� :
class GameEngineActor;
class GameEngineLevelManager;
class GameEngineCollision;
class GameEngineLevel : public GameEngineNameBase
{
public:
	friend GameEngineActor;
	friend GameEngineLevelManager;
	friend GameEngineCollision;

private:	// member Var
	bool isReset_;
	bool isloading_;
	float4 camPos_;

	// 100�� ������ �׷��� ������̴�.��� �����ϰ� ����ϴ�.
	std::map<int, std::list<GameEngineActor*>> allActorUpdateList_;
	std::map<int, std::list<GameEngineActor*>> allActorRenderList_;

	//


	// std::map<int, std::list<Renderer*>> allActorRenderList_;

	std::map<int, std::list<GameEngineCollision*>> allActorCollisionList_;

	std::map<std::string, GameEngineActor*> allActorMap_;

	////�׽�Ʈ��, ������� ����
	//std::map<std::string, GameEngineActor*> CloneActorMap_;

private:
	std::list<GameEngineCollision*>& GetCollisionList(int _Group);

public:
	float4 GetCamPos() {
		return camPos_;
	}

	void SetCamMove(float4 _pos) 
	{
		camPos_ += _pos;
	}

	void SetCamPos(float4 _pos)
	{
		camPos_ = _pos;
	}

private:
	void LevelLoading() 
	{
		if (false == GetIsLoading())
		{
			Loading();
			LoadingEnd();
		}
	}

	bool GetIsLoading() 
	{
		return isloading_;
	}

	void LoadingEnd() 
	{
		isloading_ = true;
	}

protected:		
	GameEngineLevel(); // default constructer ����Ʈ ������
	~GameEngineLevel()  override; // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineLevel(GameEngineLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	template<typename ActorType>
	ActorType* CreateActor()
	{
		std::map<int, std::list<GameEngineActor*>>::iterator UpdateIter = allActorUpdateList_.find(0);
		if (allActorUpdateList_.end() == UpdateIter)
		{
			GameEngineDebug::AssertFalse();
			return nullptr;
		}

		std::map<int, std::list<GameEngineActor*>>::iterator RenderIter = allActorRenderList_.find(0);
		if (allActorRenderList_.end() == RenderIter)
		{
			GameEngineDebug::AssertFalse();
			return nullptr;
		}

		this; // <- �� Level

		ActorType* NewActor = new ActorType();
		NewActor->SetName("Actor");
		NewActor->SetLevel(this);

		// ������ �������ټ� �ִ� �غ� �̸��̳� �غ� 
		// ���δ� ���� ���¿��� 1�� �������ִ� �Լ�.
		NewActor->Start();

		UpdateIter->second.push_back(NewActor);
		RenderIter->second.push_back(NewActor);
		return NewActor;
	}

	template<typename ActorType>
	ActorType* CreateActor(const std::string& _actorName)
	{
		ActorType* NewActor = CreateActor<ActorType>();

		if (allActorMap_.end() != allActorMap_.find(_actorName))
		{
			GameEngineDebug::AssertFalse();
			return nullptr;
		}

		NewActor->SetName(_actorName);
		NewActor->SetLevel(this);

		allActorMap_.insert(std::map<std::string, GameEngineActor*>::value_type(_actorName, NewActor));
		return NewActor;
	}



	template<typename ActorType>
	ActorType* CreateActor(float4 Pos)
	{
		std::map<int, std::list<GameEngineActor*>>::iterator UpdateIter = allActorUpdateList_.find(0);
		if (allActorUpdateList_.end() == UpdateIter)
		{
			GameEngineDebug::AssertFalse();
			return nullptr;
		}

		std::map<int, std::list<GameEngineActor*>>::iterator RenderIter = allActorRenderList_.find(0);
		if (allActorRenderList_.end() == RenderIter)
		{
			GameEngineDebug::AssertFalse();
			return nullptr;
		}

		ActorType* NewActor = new ActorType();
		NewActor->SetName("Actor");
		NewActor->SetLevel(this);
		NewActor->SetPos(Pos);

		// ������ �������ټ� �ִ� �غ� �̸��̳� �غ� 
		// ���δ� ���� ���¿��� 1�� �������ִ� �Լ�.
		NewActor->Start();

		UpdateIter->second.push_back(NewActor);
		RenderIter->second.push_back(NewActor);
		return NewActor;
	}


	GameEngineActor* FindActor(const std::string& _actorName);

private:
	void PushCollision(GameEngineCollision* _collision);


protected:

	// virtual => �Ϲ� �����Լ�
	// �ڽ��ʿ��� ������ �ص��ǰ� ���ص� �ȴ�.

	// virtual ... �Լ��� = 0
	// ���������Լ���� �մϴ�.
	// ���������Լ��� �����
	// �ڽ��� ������ �� �Լ��� ��������� �Ѵ�.

	// Level�� �ε��ϴ� ���
	// ���������Լ��� Cpp������ ���� �ʾƵ� �˴ϴ�.
	// ���� => �ڽ��ʿ��� ������ ����������״� ���� �ȸ��� �ȴ�.
	// level�� �Լ��� �������� �������� �־�
	// ���������Լ��� �� �ִ� �߻�Ŭ������
	// ��üȭ �ɼ� ����.
	virtual void Loading() = 0;

	// ���� ������Ʈ�� ���� �ʿ�������
	// ���� ���ؼ� ���� ���Ͱ� �ʿ������
	// ���������� ���𰡸� �Ǵ��ϰų�
	// ex) ���Ͱ� 1������ ���ٸ�????
	// ���������� ���𰡸� �����ؾ� �Ѵٸ�
	// ex) 4�ʸ��� ���͸� �����ض�.
	// ex) ������ x�� �̶��.
	virtual void LevelUpdateBefore();
	virtual void LevelUpdateAfter();
	virtual void LevelUpdate();



protected:		//member Func
	void UpdateOrderCheck();
	void CollisionOrderCheck();
	void RenderOrderCheck();

	void UpdateBefore();
	void Update();
	void UpdateAfter();
	void Collision();
	void Render();
	void Release();
	void Clear();


public:
	void Reset();

};

