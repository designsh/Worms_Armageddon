#include <GameEngineTime.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include "GameEngineSoundManager.h"

#include "eCollisionCheckColor.h"
#include "eCollisionGroup.h"

#include "Grave.h"

Grave::Grave():
	GravitySpeed_(0.f),
	GravityAcc_(0.f),
	GravityMove_(0.f),
	deltaTime_(0.f),
	bound_(0),
	state_(this),
	mainSpriteRender_(nullptr),
	HeadCollision_(nullptr),
	groundCollision_(nullptr)
	// default constructer 디폴트 생성자
{

}

Grave::~Grave() // default destructer 디폴트 소멸자
{

}

void Grave::Start()
{
	GameEngineMath::Random random;
	int Randomint = random.RandomInt(0, 5);

	SetRenderOrder(static_cast<int>(RenderOrder::Drum));
	mainSpriteRender_ = CreateRenderer("grave1");

	switch (Randomint)
	{
	case 0:	
		mainSpriteRender_->CreateAnimation("grave1", "grave1", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave1", std::string("grave1"));
		break;
	case 1:
		mainSpriteRender_->CreateAnimation("grave2", "grave2", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave2", std::string("grave2"));
		break;
	case 2:
		mainSpriteRender_->CreateAnimation("grave3", "grave3", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave3", std::string("grave3"));
		break;
	case 3:
		mainSpriteRender_->CreateAnimation("grave4", "grave4", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave4", std::string("grave4"));
		break;
	case 4:
		mainSpriteRender_->CreateAnimation("grave5", "grave5", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave5", std::string("grave5"));
		break;
	case 5:
		mainSpriteRender_->CreateAnimation("grave6", "grave6", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave6", std::string("grave6"));
		break;
	}

	state_.CreateState("Air",&Grave::StartAir, &Grave::UpdateAir);
	state_.CreateState("Ground", &Grave::StartGround, &Grave::UpdateGround);

	state_.ChangeState("Air");

	GravityMove_ = -300;
	GravityAcc_ = 0.5f;

	initCollision();
}

void Grave::UpdateBefore()
{
}

void Grave::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();
	state_.Update();
}

void Grave::UpdateAfter()
{
}

void Grave::Render()
{
	mainSpriteRender_->AnimationUpdateReverseLoop();
}

StateInfo Grave::StartAir(StateInfo)
{
	GravitySpeed_ = 0.f;
	bound_ = 8;
	return StateInfo();
}

StateInfo Grave::UpdateAir(StateInfo)
{
	{
		if (nullptr != HeadCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			if (GravityMove_ < 0)
			{
				GravityMove_ *= -1.f;
			}
		}

		else if (nullptr != groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			GameEngineSoundManager::GetInstance().PlaySoundByName("TEAMBOUNCE.WAV");

			if (bound_ == 0)
			{
				return "Ground";
			}

			else
			{
				bound_--;
				if (GravityMove_ > 0.f)
				{
					GravityMove_ *= -1.f;
				}

				SetMove(0.f, GravityMove_ * deltaTime_);
				GravitySpeed_ *= 0.75f;
				GravityMove_ *= 0.75f;
				
				GravitySpeed_ += GravityAcc_;
				GravityMove_ += GravitySpeed_;		

				return StateInfo();
			}
		}

		SetMove(0.f, GravityMove_ * deltaTime_);
		GravitySpeed_ += GravityAcc_;
		GravityMove_ += GravitySpeed_;

		return StateInfo();
	}
}

StateInfo Grave::StartGround(StateInfo)
{
	return StateInfo();
}

StateInfo Grave::UpdateGround(StateInfo)
{
	if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		return "Air";
	}

	return StateInfo();
}


void Grave::initCollision()
{
	HeadCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::GRAVE), CollisionCheckType::POINT);
	HeadCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	HeadCollision_->SetPivot({ 0.f, -15.f });
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::GRAVE), CollisionCheckType::POINT);
	groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCollision_->SetPivot({ 0.f, 5.f });
}
