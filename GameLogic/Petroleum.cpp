#include "Petroleum.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>
#include <GameEngineFSM.h>

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

#include "PlayLevel.h"

#include "Worm.h"
#include "GameController.h"

// 메모 : 간혹 폭발 후 소환이 안돼는 문제가 있음
// 원인 파악중

Petroleum::Petroleum() :
	Max_LifeTime_(5.f),
	Cur_LifeTime_(0.f),
	GravitySpeed(0.f),
	GravityAcc(0.f),
	WindAcc_(0.f),
	degree_(0.f),
	WindSpeed_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	Burn_(false),
	Isground_(false),
	isLive_(true),
	CountSecond_{},
	state_(this),
	PhysicalState_(this),
	nextState_("")
{

}

static int debugcount = 0;

Petroleum::~Petroleum() // default destructer 디폴트 소멸자
{

}

Petroleum::Petroleum(Petroleum&& _other) noexcept :
	Max_LifeTime_(5.f),
	Cur_LifeTime_(0.f),
	GravitySpeed(0.f),
	GravityAcc(0.f),
	WindAcc_(0.f),
	degree_(0.f),
	WindSpeed_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	Burn_(false),
	Isground_(false),
	CountSecond_{},
	state_(this),
	PhysicalState_(this),
	nextState_("")
{

}

void Petroleum::Start()
{
	debugcount++;
	GravityAcc = 6.f;

	state_.CreateState("Phase1",&Petroleum::Phase1Start, &Petroleum::Phase1Update);
	state_.CreateState("Phase2",&Petroleum::Phase2Start, &Petroleum::Phase2Update);
	state_.CreateState("Phase3",&Petroleum::Phase3Start, &Petroleum::Phase3Update);
	state_.CreateState("Phase4",&Petroleum::Phase4Start, &Petroleum::Phase4Update);
	state_.CreateState("Phase5",&Petroleum::Phase5Start, &Petroleum::Phase5Update);

	state_.CreateState("LiquidPhase0",&Petroleum::LiquidPhase0Start, &Petroleum::LiquidPhase0Update);
	state_.CreateState("LiquidPhase1",&Petroleum::LiquidPhase1Start, &Petroleum::LiquidPhase1Update);
	state_.CreateState("LiquidPhase2",&Petroleum::LiquidPhase2Start, &Petroleum::LiquidPhase2Update);
	state_.CreateState("LiquidPhase3",&Petroleum::LiquidPhase3Start, &Petroleum::LiquidPhase3Update);

	PhysicalState_.CreateState("Air", &Petroleum::AirStart, &Petroleum::AirUpdate);
	PhysicalState_.CreateState("Ground", &Petroleum::GroundStart, &Petroleum::GroundUpdate);


	mainSpriteRender_ = CreateRenderer("petrol-1");

	mainSpriteRender_->CreateAnimation("petrol60", "petrol60", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol50", "petrol50", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol40", "petrol40", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol30", "petrol30", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol20", "petrol20", 0, 19, true, 0.05f);

	mainSpriteRender_->CreateAnimation("petrol-1", "petrol-1", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-2", "petrol-2", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-3", "petrol-3", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-4", "petrol-4", 0, 63, true, 100.f);

	for (int i = 0; i < 3; ++i)
	{
		ChildSpriteRender_[i] = CreateRenderer("petrol-1");
		ChildSpriteRender_[i]->CreateAnimation("petrol60", "petrol60", 0, 19, true, 0.05f);
		ChildSpriteRender_[i]->CreateAnimation("petrol50", "petrol50", 0, 19, true, 0.05f);
		ChildSpriteRender_[i]->CreateAnimation("petrol40", "petrol40", 0, 19, true, 0.05f);
		ChildSpriteRender_[i]->CreateAnimation("petrol30", "petrol30", 0, 19, true, 0.05f);
		ChildSpriteRender_[i]->CreateAnimation("petrol20", "petrol20", 0, 19, true, 0.05f);

		ChildSpriteRender_[i]->CreateAnimation("petrol-1", "petrol-1", 0, 63, true, 100.f);
		ChildSpriteRender_[i]->CreateAnimation("petrol-2", "petrol-2", 0, 63, true, 100.f);
		ChildSpriteRender_[i]->CreateAnimation("petrol-3", "petrol-3", 0, 63, true, 100.f);
		ChildSpriteRender_[i]->CreateAnimation("petrol-4", "petrol-4", 0, 63, true, 100.f);
	}

	ChildSpriteRender_[0]->SetPivotMove(float4(-5.f, 0.f, 0.f));
	ChildSpriteRender_[1]->SetPivotMove(float4(2.f, 2.f, 0.f));
	ChildSpriteRender_[2]->SetPivotMove(float4(5.f, 0.f, 0.f));
	state_.ChangeState("LiquidPhase0"); // 초기 값
	PhysicalState_.ChangeState("Air");

	initCollision();
}

void Petroleum::UpdateBefore()
{
}

void Petroleum::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();
	
	PhysicalState_.Update();
	state_.Update();
}

void Petroleum::UpdateAfter()
{
}

void Petroleum::Render()
{
#ifdef _DEBUG	
	//if (GetLevel<PlayLevel>()->GetDebug())
	//{
	//	groundCollision_->DebugRender();
	//}
#endif // DEBUG
	mainSpriteRender_->AnimationUpdate();
	ChildSpriteRender_[0]->AnimationUpdate();
	ChildSpriteRender_[1]->AnimationUpdate();
	ChildSpriteRender_[2]->AnimationUpdate();

}

void Petroleum::PetroleumDeath()
{
	GetLevel<PlayLevel>()->GetGameController()->DecresePetroleumCount();
	GameEngineActor::Death();
}

void Petroleum::initCollision()
{
	BodyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM_HITBOX), CollisionCheckType::CIRCLE);
	BodyCollision_->SetSize({ 10.f, 10.f });

	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM), CollisionCheckType::POINT);
	groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCollision_->SetPivot({ 0.f, 1.f });
}

StateInfo Petroleum::AirStart(StateInfo _state)
{
	Isground_ = false;

	return StateInfo();
}

StateInfo Petroleum::AirUpdate(StateInfo _state)
{
	if (nullptr != groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		return "Ground";
	}
	else
	{
		if (false == Burn_)
		{
			prevPos_ = pos_;
		}
		WindSpeed_ += WindAcc_;
		GravitySpeed += GravityAcc;
		SetMove((Dir_.x + WindSpeed_) * deltaTime_, (Dir_.y + GravitySpeed) * deltaTime_);
	}
	return StateInfo();
}

StateInfo Petroleum::GroundStart(StateInfo _state)
{
	Burn_ = true;
	Isground_ = true;
	WindSpeed_ = 0.f;
	GravitySpeed = 0.f;
	Dir_.y = 0.f;
	Dir_.x = 0.f;

	return StateInfo();
}

StateInfo Petroleum::GroundUpdate(StateInfo _state)
{
	if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		return "Air";
	}

	return StateInfo();
}



//초기 State
StateInfo Petroleum::LiquidPhase0Start(StateInfo _state)
{
	mainSpriteRender_->ChangeAnimation("petrol-1", std::string("petrol-1"));
	ChildSpriteRender_[0]->ChangeAnimation("petrol-1", std::string("petrol-1"));
	ChildSpriteRender_[1]->ChangeAnimation("petrol-1", std::string("petrol-1"));
	ChildSpriteRender_[2]->ChangeAnimation("petrol-1", std::string("petrol-1"));

	return StateInfo();
}

StateInfo Petroleum::LiquidPhase0Update(StateInfo _state)
{
	if (false == Burn_)
	{
		if (Cur_LifeTime_ < 0.35f)
		{
			Cur_LifeTime_ += deltaTime_;
			CalFrameIndex();
			return StateInfo();
		}
		else
		{
			return "LiquidPhase1";
		}
	}

	else
	{
		Cur_LifeTime_ = 0.f;
		return "Phase1";
	}
	return StateInfo();
}

StateInfo Petroleum::LiquidPhase1Start(StateInfo _state)
{
	mainSpriteRender_->ChangeAnimation("petrol-2", std::string("petrol-2"));
	ChildSpriteRender_[0]->ChangeAnimation("petrol-2", std::string("petrol-2"));
	ChildSpriteRender_[1]->ChangeAnimation("petrol-2", std::string("petrol-2"));
	ChildSpriteRender_[2]->ChangeAnimation("petrol-2", std::string("petrol-2"));
	return StateInfo();
}

StateInfo Petroleum::LiquidPhase1Update(StateInfo _state)
{
	if (false == Burn_)
	{
		if (Cur_LifeTime_ < 0.4f)
		{
			Cur_LifeTime_ += deltaTime_;
			CalFrameIndex();

			return StateInfo();
		}
		else
		{
			return "LiquidPhase2";
		}
	}
	else
	{
		Cur_LifeTime_ = 0.f;
		return "Phase1";
	}
	return StateInfo();
}

StateInfo Petroleum::LiquidPhase2Start(StateInfo _state)
{
	mainSpriteRender_->ChangeAnimation("petrol-3", std::string("petrol-3"));
	ChildSpriteRender_[0]->ChangeAnimation("petrol-3", std::string("petrol-3"));
	ChildSpriteRender_[1]->ChangeAnimation("petrol-3", std::string("petrol-3"));
	ChildSpriteRender_[2]->ChangeAnimation("petrol-3", std::string("petrol-3"));
	return StateInfo();
}

StateInfo Petroleum::LiquidPhase2Update(StateInfo _state)
{
	if (false == Burn_)
	{
		if (Cur_LifeTime_ < 0.45f)
		{
			Cur_LifeTime_ += deltaTime_;
			CalFrameIndex();

			return StateInfo();
		}
		else
		{
			return "LiquidPhase3";
		}
	}
	else
	{
		Cur_LifeTime_ = 0.f;
		return "Phase1";
	}
	return StateInfo();
}

StateInfo Petroleum::LiquidPhase3Start(StateInfo _state)
{
	mainSpriteRender_->ChangeAnimation("petrol-4", std::string("petrol-4"));
	ChildSpriteRender_[0]->ChangeAnimation("petrol-4", std::string("petrol-4"));
	ChildSpriteRender_[1]->ChangeAnimation("petrol-4", std::string("petrol-4"));
	ChildSpriteRender_[2]->ChangeAnimation("petrol-4", std::string("petrol-4"));
	return StateInfo();
}

StateInfo Petroleum::LiquidPhase3Update(StateInfo _state)
{
	if (false == Burn_)
	{
		if (Cur_LifeTime_ < 0.5f)
		{
			Cur_LifeTime_ += deltaTime_;
			CalFrameIndex();

			return StateInfo();
		}
		else
		{
			return "Phase1";
		}
	}
	else
	{
		Cur_LifeTime_ = 0.f;
		return "Phase1";
	}
	return StateInfo();
}

StateInfo Petroleum::Phase1Start(StateInfo _state)
{
	Burn_ = true;
	mainSpriteRender_->ChangeAnimation("petrol60", std::string("petrol60"));
	ChildSpriteRender_[0]->ChangeAnimation("petrol60", std::string("petrol60"));
	ChildSpriteRender_[1]->ChangeAnimation("petrol60", std::string("petrol60"));
	ChildSpriteRender_[2]->ChangeAnimation("petrol60", std::string("petrol60"));
	return StateInfo();
}

StateInfo Petroleum::Phase1Update(StateInfo _state)
{
	if (Cur_LifeTime_ < 0.2f)
	{
		Cur_LifeTime_ += deltaTime_;
		WormCollision();
	}
	else
	{
		return "Phase2";
	}
	return StateInfo();
}

StateInfo Petroleum::Phase2Start(StateInfo _state)
{
	mainSpriteRender_->ChangeAnimation("petrol50", std::string("petrol50"));//GetLevel<PlayLevel>()->GroundUpdate13(pos_);
	ChildSpriteRender_[0]->ChangeAnimation("petrol50", std::string("petrol50"));//GetLevel<PlayLevel>()->GroundUpdate13(pos_);
	ChildSpriteRender_[1]->ChangeAnimation("petrol50", std::string("petrol50"));//GetLevel<PlayLevel>()->GroundUpdate13(pos_);
	ChildSpriteRender_[2]->ChangeAnimation("petrol50", std::string("petrol50"));//GetLevel<PlayLevel>()->GroundUpdate13(pos_);
	return StateInfo();
}

StateInfo Petroleum::Phase2Update(StateInfo _state)
{
	if (Cur_LifeTime_ < 1.f)
	{
		if (true == Isground_)
		{
			Cur_LifeTime_ += deltaTime_;
		}
		WormCollision();
	}
	else
	{
		return "Phase3";
	}
	return StateInfo();
}

StateInfo Petroleum::Phase3Start(StateInfo _state)
{
	mainSpriteRender_->ChangeAnimation("petrol40", std::string("petrol40"));
	ChildSpriteRender_[0]->ChangeAnimation("petrol40", std::string("petrol40"));
	ChildSpriteRender_[1]->ChangeAnimation("petrol40", std::string("petrol40"));
	ChildSpriteRender_[2]->ChangeAnimation("petrol40", std::string("petrol40"));
	GetLevel<PlayLevel>()->GroundUpdate13(pos_);
	return StateInfo();
}

StateInfo Petroleum::Phase3Update(StateInfo _state)
{
	if (Cur_LifeTime_ < 1.5f)
	{
		if (true == Isground_)
		{
			Cur_LifeTime_ += deltaTime_;
		}
		WormCollision();
	}
	else
	{
		return "Phase4";
	}
	return StateInfo();
}

StateInfo Petroleum::Phase4Start(StateInfo _state)
{
	mainSpriteRender_->ChangeAnimation("petrol30", std::string("petrol30"));
	ChildSpriteRender_[0]->ChangeAnimation("petrol30", std::string("petrol30"));
	ChildSpriteRender_[1]->ChangeAnimation("petrol30", std::string("petrol30"));
	ChildSpriteRender_[2]->ChangeAnimation("petrol30", std::string("petrol30"));
	GetLevel<PlayLevel>()->GroundUpdate6(pos_);
	return StateInfo();
}

StateInfo Petroleum::Phase4Update(StateInfo _state)
{
	if (Cur_LifeTime_ < 2.f)
	{
		if (true == Isground_)
		{
			Cur_LifeTime_ += deltaTime_;
		}
		WormCollision();
	}
	else
	{
		return "Phase5";
	}
	return StateInfo();
}

StateInfo Petroleum::Phase5Start(StateInfo _state)
{
	mainSpriteRender_->ChangeAnimation("petrol20", std::string("petrol20"));
	ChildSpriteRender_[0]->ChangeAnimation("petrol20", std::string("petrol20"));
	ChildSpriteRender_[1]->ChangeAnimation("petrol20", std::string("petrol20"));
	ChildSpriteRender_[2]->ChangeAnimation("petrol20", std::string("petrol20"));
	GetLevel<PlayLevel>()->GroundUpdate4(pos_);
	return StateInfo();
}

StateInfo Petroleum::Phase5Update(StateInfo _state)
{
	if (Cur_LifeTime_ < 2.5f)
	{
		if (true == Isground_)
		{
			Cur_LifeTime_ += deltaTime_;
		}
		WormCollision();
	}
	else if(pos_.y > GetLevel<PlayLevel>()->GetGameController()->GetWaterLevel())
	{
		PetroleumDeath();
	}
	else
	{
		PetroleumDeath();
	}
	return StateInfo();
}

void Petroleum::CalFrameIndex()
{
	float4 moveVector = pos_ - prevPos_;
	moveVector.Normalize2D();

	float theta;

	if (pos_.x < prevPos_.x)
	{
		theta = float4::DOWN.x * moveVector.x + float4::DOWN.y * moveVector.y;
	}
	else
	{
		theta = float4::UP.x * moveVector.x + float4::UP.y * moveVector.y;
	}

	theta = acos(theta);
	degree_ = theta * (180.f / 3.14f);

	if (pos_.x < prevPos_.x)
	{
		degree_ += 180.f;
	}

	degree_ += 2.8125f;

	if (degree_ > 360.f)
	{
		degree_ -= 360.f;
	}

	int frameIndex = (int)(degree_ / 5.625f);

	mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
	ChildSpriteRender_[0]->SetAnimationCurrentFrame(frameIndex);
	ChildSpriteRender_[1]->SetAnimationCurrentFrame(frameIndex);
	ChildSpriteRender_[2]->SetAnimationCurrentFrame(frameIndex);

}

void Petroleum::WormCollision()
{
	if (false == Isground_)
		return;

	std::list<GameEngineCollision*> ColList_ = BodyCollision_->CollisionGroupCheck(static_cast<int>(eCollisionGroup::PLAYER_HITBOX));

	if (false == ColList_.empty())
	{
		auto iter0 = ColList_.begin();
		auto iter1 = ColList_.end();

		for (; iter0 != iter1;)
		{
#ifdef _DEBUG
			std::string name = (*iter0)->GetActor()->GetName();
			name = name.substr(0, 4);

			if (name != "Worm")
			{
				GameEngineDebug::MsgBoxError("Worm이 아닌 충돌체가 eCollisionGroup::PLAYER_HITBOX로 설정되었습니다.");
			}
#endif // _DEBUG
			float4 Dir = (*iter0)->GetCollisionPoint() - pos_;

			if (Dir.y > 0)
			{
				Dir.y *= -1;
			}

			Dir.Normalize2D();

			dynamic_cast<Worm*>((*iter0)->GetActor())->Damage(1, Dir);

			++iter0;
		}
	}
}

//void Petroleum::PetroleumMoveUpdate(float deltaTime_)
//{
//	{
//		if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
//		{
//			WindSpeed_ += WindAcc_;
//			GravitySpeed += GravityAcc;
//			Isground_ = false;
//
//			if (true == Burn_)
//			{
//				SetMove((Dir_.x + WindSpeed_) * deltaTime_, (Dir_.y + GravitySpeed) * deltaTime_);
//			}
//			else
//			{
//				prevPos_ = pos_;
//				SetMove((Dir_.x + WindSpeed_) * deltaTime_, (Dir_.y + GravitySpeed) * deltaTime_);
//			}
//		}
//		else if (false == Isground_)
//		{
//			Dir_.y = 0.f;
//			Dir_.x = 0.f;
//			GravitySpeed = 0.f;
//			WindSpeed_ = 0.f;
//			Burn_ = true;
//			Isground_ = true;
//		}
//	}
//
//}
//
//void Petroleum::PetroleumGroundUpdate(float deltaTime_)
//{
//	if (false == Burn_)
//	{
//		Cur_LifeTime_ += deltaTime_;
//
//		float4 moveVector = pos_ - prevPos_;
//		moveVector.Normalize2D();
//
//		float theta;
//
//		if (pos_.x < prevPos_.x)
//		{
//			theta = float4::DOWN.x * moveVector.x + float4::DOWN.y * moveVector.y;
//		}
//		else
//		{
//			theta = float4::UP.x * moveVector.x + float4::UP.y * moveVector.y;
//		}
//
//		theta = acos(theta);
//		degree_ = theta * (180.f / 3.14f);
//
//		if (pos_.x < prevPos_.x)
//		{
//			degree_ += 180.f;
//		}
//
//		degree_ += 2.8125f;
//
//		if (degree_ > 360.f)
//		{
//			degree_ -= 360.f;
//		}
//
//		int frameIndex = (int)(degree_ / 5.625f);
//
//		if (Cur_LifeTime_ < 0.3f)
//		{
//			mainSpriteRender_->ChangeAnimation("petrol-2", std::string("petrol-2"));
//			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
//		}
//
//		else if (Cur_LifeTime_ < 0.45f)
//		{
//			mainSpriteRender_->ChangeAnimation("petrol-3", std::string("petrol-3"));
//			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
//		}
//
//		else if (Cur_LifeTime_ < 0.6f)
//		{
//			mainSpriteRender_->ChangeAnimation("petrol-4", std::string("petrol-4"));
//			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
//		}
//
//		else if (Cur_LifeTime_ < 0.75f)
//		{
//			mainSpriteRender_->ChangeAnimation("petrol60", std::string("petrol60"));
//			Burn_ = true;
//			Cur_LifeTime_ = 0.f;
//		}
//	}
//	else if (true == Isground_)
//	{
//		{
//			if (Cur_LifeTime_ < 1.5f)
//			{
//				mainSpriteRender_->ChangeAnimation("petrol50", std::string("petrol50"));
//			}
//			else if (Cur_LifeTime_ < 2.3f)
//			{
//				mainSpriteRender_->ChangeAnimation("petrol40", std::string("petrol40"));
//			}
//			else if (Cur_LifeTime_ < 3.5f)
//			{
//				mainSpriteRender_->ChangeAnimation("petrol30", std::string("petrol30"));
//			}
//			else if (Cur_LifeTime_ < Max_LifeTime_)
//			{
//				mainSpriteRender_->ChangeAnimation("petrol20", std::string("petrol20"));
//			}
//		}
//
//		if (false == CountSecond_[static_cast<int>(Cur_LifeTime_)])
//		{
//			if (Cur_LifeTime_ < 2.f)
//			{
//				GetLevel<PlayLevel>()->GroundUpdate13(pos_);
//			}
//
//			if (Cur_LifeTime_ < 4.f)
//			{
//				GetLevel<PlayLevel>()->GroundUpdate6(pos_);
//			}
//
//			else
//			{
//				GetLevel<PlayLevel>()->GroundUpdate4(pos_);
//			}
//
//			CountSecond_[static_cast<int>(Cur_LifeTime_)] = true;
//		}
//
//		{
//			std::list<GameEngineCollision*> ColList_ = BodyCollision_->CollisionGroupCheck(static_cast<int>(eCollisionGroup::PLAYER_HITBOX));
//
//			if (false == ColList_.empty())
//			{
//				auto iter0 = ColList_.begin();
//				auto iter1 = ColList_.end();
//
//				for (; iter0 != iter1;)
//				{
//#ifdef _DEBUG
//					std::string name = (*iter0)->GetActor()->GetName();
//					name = name.substr(0, 4);
//
//					if (name != "Worm")
//					{
//						GameEngineDebug::MsgBoxError("Worm이 아닌 충돌체가 eCollisionGroup::PLAYER_HITBOX로 설정되었습니다.");
//					}
//#endif // _DEBUG
//					float4 Dir = (*iter0)->GetCollisionPoint() - pos_;
//					Dir.Normalize2D();
//
//					dynamic_cast<Worm*>((*iter0)->GetActor())->Damage(10.f, Dir);
//
//					++iter0;
//				}
//			}
//		}
//
//		Cur_LifeTime_ += deltaTime_;
//	}
//
//	if (Cur_LifeTime_ >= Max_LifeTime_)
//	{
//		SetisLive(false);
//		return;
//	}
//}



