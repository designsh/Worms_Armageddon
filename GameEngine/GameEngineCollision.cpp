#include "GameEngineCollision.h"
#include <GameEngineDebug.h>
#include "GameEngineImage.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineImageFile.h"


// constructer destructer
GameEngineCollision::GameEngineCollision()
	: colType_(CollisionCheckType::MAX)
	, groupIndex_(0)
	, isCamEffect_(true)
	, CollisionOn_(true)
	, actor_(nullptr)
	, imageptr_(nullptr)
	, CheckColor(RGB(0, 0, 0))
	, radius_(0.0f)
	, rect_()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

float4 GameEngineCollision::GetCollisionPos() 
{
	return actor_->GetPos() + Pivot_;
}

GameEngineCollision::GameEngineCollision(GameEngineCollision&& _other) noexcept
	: colType_(CollisionCheckType::MAX)
	, groupIndex_(0)
	, isCamEffect_(true)
	, CollisionOn_(true)
	, actor_(nullptr)
	, imageptr_(nullptr)
	, CheckColor(RGB(0, 0, 0))
	, radius_(0.0f)
	, rect_()
{
}

//member Func

bool GameEngineCollision::CollisionCheck(GameEngineCollision* _other) 
{
	if ((false == CollisionOn_) || false == _other->CollisionOn_)
	{
		return false;
	}

	if (nullptr == this)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	if (nullptr == _other)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	if (nullptr == _other)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	if (nullptr == arrFunc_[GetTypeToIndex()][_other->GetTypeToIndex()])
	{
		GameEngineDebug::MsgBoxError("�������� ���� �浹�Լ��� �̿��Ϸ��� �մϴ�.");
		return false;
	}

	return arrFunc_[GetTypeToIndex()][_other->GetTypeToIndex()](this, _other);
}

void GameEngineCollision::SetImage(std::string _ImageName) 
{
	GameEngineImageFile* ImagePtr = GameEngineImage::GetInst().FindGameImage(_ImageName);

	if (nullptr == ImagePtr)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	imageptr_ = ImagePtr;
}

GameEngineCollision* GameEngineCollision::CollisionGroupCheckOne(int _otherIndex)
{
	// ��� �׷��� ���;� �ϴ� ������ �����Ҽ� �ִ�.
	if (nullptr == this)
	{
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	if (nullptr == actor_)
	{
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	if (nullptr == actor_->GetLevel())
	{
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	// ����ȭ
	std::list<GameEngineCollision*>& GroupList = actor_->GetLevel()->GetCollisionList(_otherIndex);

	if (true == GroupList.empty())
	{
		return nullptr;
	}

	std::list<GameEngineCollision*>::iterator StartIter = GroupList.begin();
	std::list<GameEngineCollision*>::iterator EndIter = GroupList.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (true == CollisionCheck(*StartIter))
		{
			return *StartIter;
		}
	}
	
	return nullptr;
}


// ���� xxx�׷쿡 ���� �浹ü�ε�. ��� xxx �׷�� ���δ� �浹�� ���� ������ ���ø� �˴ϴ�.
std::list<GameEngineCollision*> GameEngineCollision::CollisionGroupCheck(int _otherIndex)
{
	std::list<GameEngineCollision*> ReturnList;

	// ��� �׷��� ���;� �ϴ� ������ �����Ҽ� �ִ�.
	if (false == GetCollision_On_Off())
	{
		return ReturnList;
	}

	if (nullptr == this)
	{
		GameEngineDebug::AssertFalse();
		return ReturnList;
	}

	if (nullptr == actor_)
	{
		GameEngineDebug::AssertFalse();
		return ReturnList;
	}

	if (nullptr == actor_->GetLevel())
	{
		GameEngineDebug::AssertFalse();
		return ReturnList;
	}

	// ����ȭ
	std::list<GameEngineCollision*>& GroupList = actor_->GetLevel()->GetCollisionList(_otherIndex);

	if (true == GroupList.empty())
	{
		return ReturnList;
	}

	std::list<GameEngineCollision*>::iterator StartIter = GroupList.begin();
	std::list<GameEngineCollision*>::iterator EndIter = GroupList.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (true == CollisionCheck(*StartIter))
		{
			ReturnList.push_back(*StartIter);
		}
	}

	return ReturnList;
}

void GameEngineCollision::DebugRender() 
{
	GameEngineImageFile* BackBufferImage = GameEngineImage::GetInst().GetBackBufferImage();

	float4 RenderPos = GetDebugRenderPos();

	switch (colType_)
	{
	case CollisionCheckType::IMAGE:
		break;
	case CollisionCheckType::POINT:
	{
		Rectangle(BackBufferImage->GetDC(),
			RenderPos.ix() - 5,
			RenderPos.iy() - 5,
			RenderPos.ix() + 5,
			RenderPos.iy() + 5);
	}
		break;
	case CollisionCheckType::RECT:
	{
		Rectangle(BackBufferImage->GetDC(),
			RenderPos.ix() - size_.ihx(),
			RenderPos.iy() - size_.ihy(),
			RenderPos.ix() + size_.ihx(),
			RenderPos.iy() + size_.ihy());
		break;
	}
	case CollisionCheckType::LINE:
		break;
	case CollisionCheckType::CIRCLE:
		Ellipse(BackBufferImage->GetDC(),
			RenderPos.ix() - size_.ihx(),
			RenderPos.iy() - size_.ihy(),
			RenderPos.ix() + size_.ihx(),
			RenderPos.iy() + size_.ihy());
		break;
	case CollisionCheckType::POLYGON2D:
		break;
	case CollisionCheckType::AABBBOX:
		break;
	case CollisionCheckType::OBBBOX:
		break;
	case CollisionCheckType::SPHERE:
		break;
	case CollisionCheckType::POLYGON3D:
		break;
	case CollisionCheckType::MAX:
		break;
	default:
		break;
	}
}

Figure GameEngineCollision::GetFigure() 
{
	return { actor_->GetPos() + Pivot_, size_ };
}

float4 GameEngineCollision::GetDebugRenderPos() 
{
	if (false == isCamEffect_)
	{
		return actor_->GetPos() + Pivot_;
	}

	return actor_->GetCamEffectPos() + Pivot_;
}

void GameEngineCollision::SetRadius(float _radius)
{
	radius_ = _radius;
}

void GameEngineCollision::SetRect(FRect _rect)
{
	rect_ = _rect;
}

void GameEngineCollision::SetRect(float _left, float _top, float _right, float _bottom)
{
	rect_.left = _left;
	rect_.right = _right;
	rect_.top = _top;
	rect_.bottom = _bottom;
}

float4 GameEngineCollision::GetCollisionPoint() const
{
	return actor_->GetPos() + Pivot_;
}

FRect GameEngineCollision::GetCollisionRect() const
{
	FRect rect;
	float4 location = actor_->GetPos() + Pivot_;
	rect.left = rect_.left + location.x;
	rect.right = rect_.right + location.x;
	rect.top = rect_.top + location.y;
	rect.bottom = rect_.bottom + location.y;
	return rect;
}