#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCollision.h"


// Static Var
// Static Func

// constructer destructer
GameEngineLevel::GameEngineLevel()
	: isloading_(false)
	, camPos_(float4::ZERO)
{
	// 0�� �׷��� ������ ����� �����ϴ�.
	allActorUpdateList_.insert(std::map<int, std::list<GameEngineActor*>>::value_type(0, std::list<GameEngineActor*>()));
	allActorRenderList_.insert(std::map<int, std::list<GameEngineActor*>>::value_type(0, std::list<GameEngineActor*>()));
	allActorCollisionList_.insert(std::map<int, std::list<GameEngineCollision*>>::value_type(0, std::list<GameEngineCollision*>()));
}

GameEngineLevel::~GameEngineLevel()
{
	Clear();
}

GameEngineLevel::GameEngineLevel(GameEngineLevel&& _other) noexcept
{
}

//member Func


std::list<GameEngineCollision*>& GameEngineLevel::GetCollisionList(int _Group) 
{
	std::map<int, std::list<GameEngineCollision*>>::iterator FindGroupIter
		= allActorCollisionList_.find(_Group);

	if (FindGroupIter == allActorCollisionList_.end())
	{
		allActorCollisionList_.insert(std::map<int, std::list<GameEngineCollision*>>::value_type(_Group, std::list<GameEngineCollision*>()));
		FindGroupIter = allActorCollisionList_.find(_Group);
	}

	return FindGroupIter->second;
}

GameEngineActor* GameEngineLevel::FindActor(const std::string& _actorName) 
{
	std::map<std::string, GameEngineActor*>::iterator FindIter = allActorMap_.find(_actorName);

	if (allActorMap_.end() == FindIter)
	{
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineLevel::UpdateOrderCheck()
{
	{
		//  ���ο� �׷��� �����.
		std::map<int, std::list<GameEngineActor*>>::iterator UpdateStart = allActorUpdateList_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator UpdateEnd = allActorUpdateList_.end();
		for (; UpdateStart != UpdateEnd; ++UpdateStart)
		{
			std::list<GameEngineActor*>::iterator Start = UpdateStart->second.begin();
			std::list<GameEngineActor*>::iterator End = UpdateStart->second.end();
			for (; Start != End; ++Start)
			{
				// �̰� �ٸ��ٴ°���
				// �̳༮�� �ڽ��� ������ �ٲٰڴٴ� �̾߱Ⱑ �ȴ�.
				if (UpdateStart->first == (*Start)->UpdateOrder)
				{
					continue;
				}

				if (allActorUpdateList_.end() == allActorUpdateList_.find((*Start)->UpdateOrder))
				{
					allActorUpdateList_.insert(std::map<int, std::list<GameEngineActor*>>::value_type((*Start)->UpdateOrder, std::list<GameEngineActor*>()));
				}

				std::map<int, std::list<GameEngineActor*>>::iterator UpdateIter = allActorUpdateList_.find((*Start)->UpdateOrder);
				UpdateIter->second.push_back((*Start));
			}
		}
	}

	{
		// �����ִ� �κ�
		// �ٸ� �༮���� �����ش�.
		std::map<int, std::list<GameEngineActor*>>::iterator UpdateStart = allActorUpdateList_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator UpdateEnd = allActorUpdateList_.end();
		for (; UpdateStart != UpdateEnd; ++UpdateStart)
		{
			std::list<GameEngineActor*>::iterator Start = UpdateStart->second.begin();
			std::list<GameEngineActor*>::iterator End = UpdateStart->second.end();
			for (; Start != End; )
			{
				if (UpdateStart->first == (*Start)->UpdateOrder)
				{
					++Start;
					continue;
				}

				Start = UpdateStart->second.erase(Start);
			}
		}
	}

}

void GameEngineLevel::UpdateBefore() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateStart = allActorUpdateList_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateEnd = allActorUpdateList_.end();

	for (; UpdateStart != UpdateEnd; ++UpdateStart)
	{
		std::list<GameEngineActor*>::iterator Start = UpdateStart->second.begin();
		std::list<GameEngineActor*>::iterator End = UpdateStart->second.end();

		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}

			(*Start)->UpdateBefore();
		}
	}
}

void GameEngineLevel::Update() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateStart = allActorUpdateList_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateEnd = allActorUpdateList_.end();

	for (; UpdateStart != UpdateEnd; ++UpdateStart)
	{
		std::list<GameEngineActor*>::iterator Start = UpdateStart->second.begin();
		std::list<GameEngineActor*>::iterator End = UpdateStart->second.end();

		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}

			(*Start)->Update();
		}
	}
}

void GameEngineLevel::Collision()
{
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateStart = allActorUpdateList_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateEnd = allActorUpdateList_.end();

	for (; UpdateStart != UpdateEnd; ++UpdateStart)
	{
		std::list<GameEngineActor*>::iterator Start = UpdateStart->second.begin();
		std::list<GameEngineActor*>::iterator End = UpdateStart->second.end();

		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}

			(*Start)->Collision();
		}
	}
}


void GameEngineLevel::UpdateAfter() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateStart = allActorUpdateList_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateEnd = allActorUpdateList_.end();

	for (; UpdateStart != UpdateEnd; ++UpdateStart)
	{
		std::list<GameEngineActor*>::iterator Start = UpdateStart->second.begin();
		std::list<GameEngineActor*>::iterator End = UpdateStart->second.end();

		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}

			(*Start)->UpdateAfter();
		}
	}
}


void GameEngineLevel::RenderOrderCheck()
{
	{
		//  ���ο� �׷��� �����.
		std::map<int, std::list<GameEngineActor*>>::iterator RenderStart = allActorRenderList_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator RenderEnd = allActorRenderList_.end();
		for (; RenderStart != RenderEnd; ++RenderStart)
		{
			std::list<GameEngineActor*>::iterator Start = RenderStart->second.begin();
			std::list<GameEngineActor*>::iterator End = RenderStart->second.end();
			for (; Start != End; ++Start)
			{
				// �̰� �ٸ��ٴ°���
				// �̳༮�� �ڽ��� ������ �ٲٰڴٴ� �̾߱Ⱑ �ȴ�.
				if (RenderStart->first == (*Start)->RenderOrder)
				{
					continue;
				}

				if (allActorRenderList_.end() == allActorRenderList_.find((*Start)->RenderOrder))
				{
					allActorRenderList_.insert(std::map<int, std::list<GameEngineActor*>>::value_type((*Start)->RenderOrder, std::list<GameEngineActor*>()));
				}

				std::map<int, std::list<GameEngineActor*>>::iterator RenderIter = allActorRenderList_.find((*Start)->RenderOrder);
				RenderIter->second.push_back((*Start));
			}
		}
	}

	{
		// �����ִ� �κ�
		// �ٸ� �༮���� �����ش�.
		std::map<int, std::list<GameEngineActor*>>::iterator RenderStart = allActorRenderList_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator RenderEnd = allActorRenderList_.end();
		for (; RenderStart != RenderEnd; ++RenderStart)
		{
			std::list<GameEngineActor*>::iterator Start = RenderStart->second.begin();
			std::list<GameEngineActor*>::iterator End = RenderStart->second.end();
			for (; Start != End; )
			{
				if (RenderStart->first == (*Start)->RenderOrder)
				{
					++Start;
					continue;
				}

				Start = RenderStart->second.erase(Start);
			}
		}
	}
}



void GameEngineLevel::CollisionOrderCheck()
{
	{
		//  ���ο� �׷��� �����.
		std::map<int, std::list<GameEngineCollision*>>::iterator RenderStart = allActorCollisionList_.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator RenderEnd = allActorCollisionList_.end();
		for (; RenderStart != RenderEnd; ++RenderStart)
		{
			std::list<GameEngineCollision*>::iterator Start = RenderStart->second.begin();
			std::list<GameEngineCollision*>::iterator End = RenderStart->second.end();
			for (; Start != End; ++Start)
			{
				// �̰� �ٸ��ٴ°���
				// �̳༮�� �ڽ��� ������ �ٲٰڴٴ� �̾߱Ⱑ �ȴ�.
				if (RenderStart->first == (*Start)->GetGroupIndex())
				{
					continue;
				}

				if (allActorCollisionList_.end() == allActorCollisionList_.find((*Start)->GetGroupIndex()))
				{
					allActorCollisionList_.insert(std::map<int, std::list<GameEngineCollision*>>::value_type((*Start)->GetGroupIndex(), std::list<GameEngineCollision*>()));
				}

				std::map<int, std::list<GameEngineCollision*>>::iterator RenderIter = allActorCollisionList_.find((*Start)->GetGroupIndex());
				RenderIter->second.push_back((*Start));
			}
		}
	}

	{
		// �����ִ� �κ�
		// �ٸ� �༮���� �����ش�.
		std::map<int, std::list<GameEngineCollision*>>::iterator RenderStart = allActorCollisionList_.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator RenderEnd = allActorCollisionList_.end();
		for (; RenderStart != RenderEnd; ++RenderStart)
		{
			std::list<GameEngineCollision*>::iterator Start = RenderStart->second.begin();
			std::list<GameEngineCollision*>::iterator End = RenderStart->second.end();
			for (; Start != End; )
			{
				if (RenderStart->first == (*Start)->GetGroupIndex())
				{
					++Start;
					continue;
				}

				Start = RenderStart->second.erase(Start);
			}
		}
	}
}


void GameEngineLevel::Render() 
{

	std::map<int, std::list<GameEngineActor*>>::iterator RenderStart = allActorRenderList_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator RenderEnd = allActorRenderList_.end();

	for (; RenderStart != RenderEnd; ++RenderStart)
	{
		std::list<GameEngineActor*>::iterator Start = RenderStart->second.begin();
		std::list<GameEngineActor*>::iterator End = RenderStart->second.end();

		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}

			(*Start)->Render();
		}
	}
}

void GameEngineLevel::LevelUpdateBefore()
{

}

void GameEngineLevel::LevelUpdateAfter() 
{

}

void GameEngineLevel::LevelUpdate() 
{
}


void GameEngineLevel::PushCollision(GameEngineCollision* _collision)
{
	std::map<int, std::list<GameEngineCollision*>>::iterator CollisionIter = allActorCollisionList_.find(0);
	if (allActorCollisionList_.end() == CollisionIter)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	CollisionIter->second.push_back(_collision);
	return;
}

void GameEngineLevel::Release() 
{

	{
		// �����ִ� �κ�
		// �ٸ� �༮���� �����ش�.
		std::map<int, std::list<GameEngineCollision*>>::iterator CollisionStart = allActorCollisionList_.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator CollisionEnd = allActorCollisionList_.end();
		for (; CollisionStart != CollisionEnd; ++CollisionStart)
		{
			std::list<GameEngineCollision*>::iterator Start = CollisionStart->second.begin();
			std::list<GameEngineCollision*>::iterator End = CollisionStart->second.end();
			for (; Start != End; )
			{
				if (false == (*Start)->IsDeath())
				{
					++Start;
					continue;
				}

				Start = CollisionStart->second.erase(Start);
			}
		}
	}

	{
		std::map<int, std::list<GameEngineActor*>>::iterator RenderStart = allActorRenderList_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator RenderEnd = allActorRenderList_.end();

		for (; RenderStart != RenderEnd; ++RenderStart)
		{
			std::list<GameEngineActor*>::iterator Start = RenderStart->second.begin();
			std::list<GameEngineActor*>::iterator End = RenderStart->second.end();

			for (; Start != End; )
			{
				if (true == (*Start)->IsDeath())
				{
					Start = RenderStart->second.erase(Start);
				}
				else {
					++Start;
				}
			}
		}
	}

	{
		std::map<int, std::list<GameEngineActor*>>::iterator UpdateStart = allActorUpdateList_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator UpdateEnd = allActorUpdateList_.end();

		for (; UpdateStart != UpdateEnd; ++UpdateStart)
		{
			std::list<GameEngineActor*>::iterator Start = UpdateStart->second.begin();
			std::list<GameEngineActor*>::iterator End = UpdateStart->second.end();

			for (; Start != End; )
			{
				if (true == (*Start)->IsDeath())
				{
					// RenderList
					// UpdateList
					// �ΰ��� ��������� �����Ƿ�
					// ����°� ������Ʈ�� �����̴ϴ�.
					delete (*Start);
					Start = UpdateStart->second.erase(Start);
				}
				else {
					++Start;
				}
			}
		}
	}
}

void GameEngineLevel::Reset() 
{
	isReset_ = true;
	// Clear();
}

void GameEngineLevel::Clear() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateStart = allActorUpdateList_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator UpdateEnd = allActorUpdateList_.end();

	for (; UpdateStart != UpdateEnd; ++UpdateStart)
	{
		std::list<GameEngineActor*>::iterator Start = UpdateStart->second.begin();
		std::list<GameEngineActor*>::iterator End = UpdateStart->second.end();

		for (; Start != End; ++Start)
		{
			delete (*Start);
			(*Start) = nullptr;
		}
	}

	allActorCollisionList_.clear();
	allActorRenderList_.clear();
	allActorUpdateList_.clear();
	allActorMap_.clear();

	allActorUpdateList_.insert(std::map<int, std::list<GameEngineActor*>>::value_type(0, std::list<GameEngineActor*>()));
	allActorRenderList_.insert(std::map<int, std::list<GameEngineActor*>>::value_type(0, std::list<GameEngineActor*>()));
	allActorCollisionList_.insert(std::map<int, std::list<GameEngineCollision*>>::value_type(0, std::list<GameEngineCollision*>()));

	camPos_ = float4::ZERO;

	////�׽�Ʈ��
	//auto iter0 = CloneActorMap_.begin();
	//auto iter1 = CloneActorMap_.end();
	//for(; iter0!= iter1;)
	//{
	//	delete iter0->second;
	//	(iter0->second) = nullptr;

	//	iter0++;
	//}

	//CloneActorMap_.clear();
}