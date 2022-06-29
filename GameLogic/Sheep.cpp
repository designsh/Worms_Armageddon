#include "Sheep.h"

#include <GameEngineCollision.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineSoundManager.h>

#include "PlayLevel.h"

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

Sheep::Sheep()
	: state_(this)
	, speed_(float4::ZERO)
	, mainRender_(nullptr)
	, headCollision_(nullptr)
	, bottomCenterCollision_(nullptr)
	, groundCheckCollision_(nullptr)
	, topCenterCollision_(nullptr)
	, bLeft_(false)
	, bGround_(false)
	, jumpDelay_(JUMP_DELAY)
	, deltaTime_(0.0f)
	, explosionDelay_(0.0f)
{
}

Sheep::~Sheep()
{

}

void Sheep::Start()
{
	SetRenderOrder(static_cast<int>(RenderOrder::Weapon));

	// 렌더러
	mainRender_ = CreateRenderer("sheepWalkLeft.bmp");
	mainRender_->CreateAnimation("WalkLeft", "sheepWalkLeft.bmp", 0, 6, true, 0.1f);
	mainRender_->CreateAnimation("WalkRight", "sheepWalkRight.bmp", 0, 6, true, 0.1f);

	mainRender_->ChangeAnimation("WalkRight", std::string("sheepWalkRight.bmp"));

	// 충돌체
	topCenterCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	topCenterCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	topCenterCollision_->SetPivot({ 0.0f, -BOTTOM_PIVOT });

	headCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	headCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));

	bottomCenterCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	bottomCenterCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	bottomCenterCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT });

	groundCheckCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 1 });

	// 키
	if (false == GameEngineInput::GetInst().IsKey("Explosion"))
	{
		GameEngineInput::GetInst().CreateKey("Explosion", VK_SPACE);
	}

	// 상태
	state_.CreateState("Idle", &Sheep::startIdle, &Sheep::updateIdle);
	state_.CreateState("Walk", &Sheep::startWalk, &Sheep::updateWalk);
	state_.CreateState("Explosion", &Sheep::startExplosion, &Sheep::updateExplosion);
	state_.ChangeState("Idle");
}

void Sheep::UpdateBefore()
{
	mainRender_->AnimationUpdate();
}

void Sheep::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();
	state_.Update();
}

void Sheep::UpdateAfter()
{
}

void Sheep::Render()
{
	if (mainRender_->IsOn())
	{
		mainRender_->Render();
	}
}

void Sheep::Initialize(Worm* _parentWorm, bool _bLeft)
{
	parentWorm_ = _parentWorm;
	bLeft_ = _bLeft;
}

void Sheep::addGravity()
{
	if (nullptr == groundCheckCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		bGround_ = false;
		speed_.y += GRAVITY_POWER * deltaTime_;
	}
	else
	{
		bGround_ = true;
		speed_.y = 0.0f;
		pos_.y = static_cast<float>(static_cast<int>(pos_.y));
	}
}

void Sheep::normalMove()
{
	SetMove(speed_ * deltaTime_);

	// 땅에 박힌 것
	if (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		while (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			SetMove({ 0.0f, -1.0f });
			pos_.y = static_cast<float>(static_cast<int>(pos_.y));
		}
	}
	else
	{
		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 1 });
		if (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			// 정상 땅에 딱 붙어있는 상태
			bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
			return;
		}

		// 낭떠러지에 섰다
		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 5 });
		if (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			bGround_ = false;
			bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
			return;
		}


		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
		// 여기 왔으면 경사라고 본다.
		while (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			SetMove({ 0.0f, 1.0f });
			pos_.y = static_cast<float>(static_cast<int>(pos_.y));
		}

		SetMove({ 0.0f, -1.0f });
	}
}

StateInfo Sheep::startIdle(StateInfo _state)
{
	return StateInfo();
}

StateInfo Sheep::updateIdle(StateInfo _state)
{
	GameEngineSoundManager::GetInstance().PlaySoundByName("SHEEPBAA.WAV");
	return "Walk";
}

StateInfo Sheep::startWalk(StateInfo _state)
{
	return StateInfo();
}

StateInfo Sheep::updateWalk(StateInfo _state)
{
	if (GameEngineInput::GetInst().IsDown("Explosion"))
	{
		return "Explosion";
	}

	addGravity();
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("WalkLeft", std::string("sheepWalkLeft.bmp"));
		speed_.x = -200;
		headCollision_->SetPivot({ -15.f, -5.0f });
	}
	else
	{
		mainRender_->ChangeAnimation("WalkRight", std::string("sheepWalkRight.bmp"));
		speed_.x = 200;
		headCollision_->SetPivot({ 15.f, -5.0f });
	}
	if (nullptr != headCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		bLeft_ = !bLeft_;
		return "Walk";
	}

	if (jumpDelay_ < 0.0f && bGround_)
	{
		GameEngineSoundManager::GetInstance().PlaySoundByName("SHEEPBAA.WAV");
		jumpDelay_ = JUMP_DELAY;
		SetMove({ 0.0f, -6.f });
		speed_.y = -300.f;
	}
	jumpDelay_ -= deltaTime_;

	if (nullptr != topCenterCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		SetMove({ 0.0f, 2.f });
		speed_.y = 0.0f;
	}

	normalMove();
	return StateInfo();
}

StateInfo Sheep::startExplosion(StateInfo _state)
{
	PlayLevel* level = (PlayLevel*)GetLevel();
	level->CreateExplosion100(pos_,75,true);
	explosionDelay_ = 3.0f;
	mainRender_->Off();
	//GameEngineSoundManager::GetInstance().PlaySoundByName("Explosion1.wav");
	return StateInfo();
}

StateInfo Sheep::updateExplosion(StateInfo _state)
{
	explosionDelay_ -= GameEngineTime::GetInst().GetDeltaTime();

	if (explosionDelay_ <= 0)
	{
		parentWorm_->ChangeState("Idle");
		parentWorm_->BulletFocusOff();
		parentWorm_->SubtractActionToken(1);
		Death();
	}
	return StateInfo();
}
