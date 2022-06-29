#include "GameEngineCollision.h"
#include <GameEngineDebug.h>
#include "GameEngineImageFile.h"


// Static Var
// Static Func

bool (*GameEngineCollision::arrFunc_[static_cast<int>(CollisionCheckType::MAX)][static_cast<int>(CollisionCheckType::MAX)])(GameEngineCollision* _PointCol, GameEngineCollision* _ImageCol) = { nullptr };

void GameEngineCollision::ColCheckFuncInitialize()
{
	for (size_t y = 0; y < static_cast<int>(CollisionCheckType::MAX); y++)
	{
		for (size_t x = 0; x < static_cast<int>(CollisionCheckType::MAX); x++)
		{
			arrFunc_[y][x] = nullptr;
		}
	}

	arrFunc_[static_cast<int>(CollisionCheckType::IMAGE)][static_cast<int>(CollisionCheckType::POINT)] = &GameEngineCollision::ImageToPoint;

	arrFunc_[static_cast<int>(CollisionCheckType::POINT)][static_cast<int>(CollisionCheckType::IMAGE)] = &GameEngineCollision::PointToImage;

	arrFunc_[static_cast<int>(CollisionCheckType::POINT)][static_cast<int>(CollisionCheckType::POINT)] = &GameEngineCollision::PointToPoint;
	arrFunc_[static_cast<int>(CollisionCheckType::POINT)][static_cast<int>(CollisionCheckType::RECT)] = &GameEngineCollision::PointToRect;
	arrFunc_[static_cast<int>(CollisionCheckType::POINT)][static_cast<int>(CollisionCheckType::CIRCLE)] = &GameEngineCollision::collisionCheckPointToCircle;


	arrFunc_[static_cast<int>(CollisionCheckType::RECT)][static_cast<int>(CollisionCheckType::POINT)] = &GameEngineCollision::RectToPoint;
	arrFunc_[static_cast<int>(CollisionCheckType::RECT)][static_cast<int>(CollisionCheckType::RECT)] = &GameEngineCollision::RectToRect;
	arrFunc_[static_cast<int>(CollisionCheckType::RECT)][static_cast<int>(CollisionCheckType::CIRCLE)] = &GameEngineCollision::collisionCheckRectToCircle;

	arrFunc_[static_cast<int>(CollisionCheckType::CIRCLE)][static_cast<int>(CollisionCheckType::POINT)] = &GameEngineCollision::collisionCheckCircleToPoint;
	arrFunc_[static_cast<int>(CollisionCheckType::CIRCLE)][static_cast<int>(CollisionCheckType::RECT)] = &GameEngineCollision::collisionCheckCircleToRect;
	arrFunc_[static_cast<int>(CollisionCheckType::CIRCLE)][static_cast<int>(CollisionCheckType::CIRCLE)] = &GameEngineCollision::collisionCheckCircleToCircle;
}

//bool GameEngineCollision::RectToImage(GameEngineCollision* _PointCol, GameEngineCollision* _ImageCol)
//{
//	float4 size = _PointCol->GetSize();
//	float4 Pos;
//	DWORD Color;
//	for (int i = 0; i < size.x; ++i)
//	{
//		for (int j = 0; j < size.y; ++j)
//		{
//			Pos = _PointCol->GetCollisionPos();
//			Color = _ImageCol->imageptr_->GetColor4Byte(Pos.ix(), Pos.iy());
//			if (_PointCol->GetColorCheck() == Color)
//			{
//				return true;
//			}
//		}
//	}
//	//if (nullptr == _ImageCol->imageptr_)
//	//{
//	//	GameEngineDebug::AssertFalse();
//	//	return false;
//	//}
//	return false;
//}

bool GameEngineCollision::PointToImage(GameEngineCollision* _PointCol, GameEngineCollision* _ImageCol)
{
	float4 Pos = _PointCol->GetCollisionPos();

	if (nullptr == _ImageCol->imageptr_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	DWORD Color = _ImageCol->imageptr_->GetColor4Byte(Pos.ix(), Pos.iy());

	return _PointCol->GetColorCheck() == Color;
}

bool GameEngineCollision::ImageToPoint(GameEngineCollision* _ImageCol, GameEngineCollision* _PointCol)
{
	return PointToImage(_PointCol, _ImageCol);
}


bool GameEngineCollision::RectToRect(GameEngineCollision* _left, GameEngineCollision* _right) 
{
	Figure Left = _left->GetFigure();
	Figure Right = _right->GetFigure();

	if (Left.iRight() < Right.iLeft())
	{
		return false;
	}

	if (Left.iLeft() > Right.iRight())
	{
		return false;
	}

	if (Left.iTop() > Right.iBot())
	{
		return false;
	}

	if (Left.iBot() < Right.iTop())
	{
		return false;
	}

	return true;
}

// Point란? size가 zero인 rect라고 볼수가 있다.

bool GameEngineCollision::RectToPoint(GameEngineCollision* _left, GameEngineCollision* _right)
{
	Figure Left = _left->GetFigure();
	float4 Right = _right->GetCollisionPos();

	if (Left.iRight() < Right.ix())
	{
		return false;
	}

	if (Left.iLeft() > Right.ix())
	{
		return false;
	}

	if (Left.iTop() > Right.iy())
	{
		return false;
	}

	if (Left.iBot() < Right.iy())
	{
		return false;
	}

	return true;
}

	//구현은 해놨지만 의미는 없는ㄱ것 같은 함수
bool GameEngineCollision::PointToPoint(GameEngineCollision* _left, GameEngineCollision* _right)
{
	return _left->GetCollisionPos() == _right->GetCollisionPos();
}

bool GameEngineCollision::PointToRect(GameEngineCollision* _left, GameEngineCollision* _right)
{
	return RectToPoint(_right, _left);
}


bool GameEngineCollision::collisionCheckCircleToCircle(GameEngineCollision* lhs, GameEngineCollision* rhs)
{
	float distance = lhs->GetCollisionPoint().DistanceTo(rhs->GetCollisionPoint());

	return 0 >= (distance - lhs->size_.x * 0.5f - rhs->size_.x * 0.5f);
}

bool GameEngineCollision::collisionCheckPointToCircle(GameEngineCollision* lhs, GameEngineCollision* rhs)
{
	float distance = lhs->GetCollisionPoint().DistanceTo(rhs->GetCollisionPoint());

	return 0 >= (distance - rhs->size_.x * 0.5f);
}

bool GameEngineCollision::collisionCheckCircleToPoint(GameEngineCollision* lhs, GameEngineCollision* rhs)
{
	return collisionCheckPointToCircle(rhs, lhs);
}

bool GameEngineCollision::collisionCheckRectToCircle(GameEngineCollision* lhs, GameEngineCollision* rhs)
{
	//float4 RectSize;
	float4 RectPos = lhs->GetCollisionPos() + lhs->Pivot_;
	float4 point = rhs->GetCollisionPos()+ rhs->Pivot_;
	lhs->rect_.left = RectPos.x - rhs->size_.x / 2;
	lhs->rect_.top = RectPos.y - rhs->size_.x / 2;
	lhs->rect_.right = RectPos.x + lhs->size_.x + rhs->size_.x / 2;;
	lhs->rect_.bottom = RectPos.y + lhs->size_.y + rhs->size_.x / 2;;

	if (point.x < lhs->rect_.left)
	{
		return false;
	}

	if (point.x > lhs->rect_.right)
	{
		return false;
	}

	if (point.y < lhs->rect_.top)
	{
		return false;
	}

	if (point.y > lhs->rect_.bottom)
	{
		return false;
	}

	return true;
}

bool GameEngineCollision::collisionCheckCircleToRect(GameEngineCollision* lhs, GameEngineCollision* rhs)
{
	return collisionCheckRectToCircle(rhs, lhs);
}