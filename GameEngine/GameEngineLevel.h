#pragma once
#include <list>
#include <map>
#include <string>
#include <GameEngineDebug.h>
#include <GameEngineNameBase.h>
#include <GameEngineMath.h>


// 분류 :
// 용도 :
// 설명 :
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

	// 100개 이하의 그룹이 생길것이다.라고 예상하고 만듭니다.
	std::map<int, std::list<GameEngineActor*>> allActorUpdateList_;
	std::map<int, std::list<GameEngineActor*>> allActorRenderList_;

	//


	// std::map<int, std::list<Renderer*>> allActorRenderList_;

	std::map<int, std::list<GameEngineCollision*>> allActorCollisionList_;

	std::map<std::string, GameEngineActor*> allActorMap_;

	////테스트중, 사용하지 말것
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
	GameEngineLevel(); // default constructer 디폴트 생성자
	~GameEngineLevel()  override; // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineLevel(GameEngineLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

		this; // <- 가 Level

		ActorType* NewActor = new ActorType();
		NewActor->SetName("Actor");
		NewActor->SetLevel(this);

		// 엔진이 지원해줄수 있는 준비가 이름이나 준비가 
		// 전부다 끝난 상태에서 1번 실행해주는 함수.
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

		// 엔진이 지원해줄수 있는 준비가 이름이나 준비가 
		// 전부다 끝난 상태에서 1번 실행해주는 함수.
		NewActor->Start();

		UpdateIter->second.push_back(NewActor);
		RenderIter->second.push_back(NewActor);
		return NewActor;
	}


	GameEngineActor* FindActor(const std::string& _actorName);

private:
	void PushCollision(GameEngineCollision* _collision);


protected:

	// virtual => 일반 가상함수
	// 자식쪽에서 구현을 해도되고 안해도 된다.

	// virtual ... 함수끝 = 0
	// 순수가상함수라고 합니다.
	// 순수가상함수를 만들면
	// 자식은 무조건 이 함수를 구현해줘야 한다.

	// Level을 로딩하는 기능
	// 순수가상함수는 Cpp구현을 하지 않아도 됩니다.
	// 이유 => 자식쪽에서 무조건 만들어줬을테니 나는 안만들어도 된다.
	// level은 함수가 존재하지 않을수가 있어
	// 순수가상함수가 들어가 있는 추상클래스는
	// 객체화 될수 없다.
	virtual void Loading() = 0;

	// 씬의 업데이트가 따로 필요한이유
	// 씬을 통해서 굳이 액터가 필요없지만
	// 지속적으로 무언가를 판단하거나
	// ex) 몬스터가 1마리도 없다면????
	// 지속적으로 무언가를 실행해야 한다면
	// ex) 4초마다 몬스터를 생성해라.
	// ex) 점수가 x점 이라면.
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

