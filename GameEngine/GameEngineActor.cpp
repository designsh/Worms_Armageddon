#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"


// Static Var
// Static Func

// constructer destructer
GameEngineActor::GameEngineActor()
	: ActorType(-1),
	UpdateOrder(0),
	RenderOrder(0),
	parentLevel_(nullptr),
	cameraEffectScale_(1.0f)
{
}

GameEngineActor::~GameEngineActor()
{
	{
		std::list<GameEngineRenderer*>::iterator StartIter = rendererList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = rendererList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == (*StartIter))
			{
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
		rendererList_.clear();
	}

	{
		std::list<GameEngineCollision*>::iterator StartIter = collisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = collisionList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == (*StartIter))
			{
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
		collisionList_.clear();
	}

}

float4 GameEngineActor::GetCamEffectPos()
{
	return GetPos() - (parentLevel_->GetCamPos() * cameraEffectScale_);
}

void GameEngineActor::Collision()
{

}

GameEngineRenderer* GameEngineActor::CreateRenderer(std::string _ImageName)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	NewRenderer->SetParent(this);
	// 부모도 알게 됩니다.
	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_ImageName);
	rendererList_.push_back(NewRenderer);
	return NewRenderer;
}


GameEngineCollision* GameEngineActor::CreateCollision(int _Group, CollisionCheckType _type)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();
	// 부모도 알게 됩니다.
	NewCollision->SetParent(this);
	NewCollision->SetActor(this);
	NewCollision->SetColType(_type);
	NewCollision->SetGroupIndex(_Group);
	collisionList_.push_back(NewCollision);

	GetLevel()->PushCollision(NewCollision);
	GetLevel()->CollisionOrderCheck();

	return NewCollision;
}