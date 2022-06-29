#include "SuperSheep.h"

#include <GameEngineCollision.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineDebugExtension.h>
#include <GameEngineSoundManager.h>

#include "PlayLevel.h"

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"


SuperSheep::SuperSheep()
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
	, headPivot_(float4::UP)
	, direction_(float4::UP)
	, animDelay_(ANIM_DELAY)
	, soundWhoosh_("SUPERSHEEPWHOOSH.WAV")
	, EffectSpawnTime_(0.0f)
{

}

SuperSheep::~SuperSheep()
{

}

void SuperSheep::Start()
{
	SetRenderOrder(static_cast<int>(RenderOrder::Weapon));

	// 렌더러
	mainRender_ = CreateRenderer("sheepWalkLeft.bmp");
	mainRender_->CreateAnimation("WalkLeft", "sheepWalkLeft.bmp", 0, 6, true, 0.1f);
	mainRender_->CreateAnimation("WalkRight", "sheepWalkRight.bmp", 0, 6, true, 0.1f);
	mainRender_->CreateAnimation("Fly", "superSheep.bmp", 0, 63, false, FLT_MAX);

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
	if (false == GameEngineInput::GetInst().IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst().CreateKey("LeftArrow", VK_LEFT);
	}
	if (false == GameEngineInput::GetInst().IsKey("RightArrow"))
	{
		GameEngineInput::GetInst().CreateKey("RightArrow", VK_RIGHT);
	}

	// 상태
	state_.CreateState("Idle", &SuperSheep::startIdle, &SuperSheep::updateIdle);
	state_.CreateState("Walk", &SuperSheep::startWalk, &SuperSheep::updateWalk);
	state_.CreateState("Fly", &SuperSheep::startFly, &SuperSheep::updateFly);
	state_.CreateState("Explosion", &SuperSheep::startExplosion, &SuperSheep::updateExplosion);
	state_.ChangeState("Walk");
}

void SuperSheep::UpdateBefore()
{
	mainRender_->AnimationUpdate();
}

void SuperSheep::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	state_.Update();
}

void SuperSheep::UpdateAfter()
{
}

void SuperSheep::Render()
{
	if (mainRender_->IsOn())
	{
		mainRender_->Render();
	}
}

void SuperSheep::Initialize(Worm* _parentWorm, bool _bLeft)
{
	SetParentWorm(_parentWorm);
	bLeft_ = _bLeft;
}

void SuperSheep::addGravity()
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

void SuperSheep::normalMove()
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

StateInfo SuperSheep::startIdle(StateInfo _state)
{
	return StateInfo();
}

StateInfo SuperSheep::updateIdle(StateInfo _state)
{
	GameEngineSoundManager::GetInstance().PlaySoundByName("SHEEPBAA.WAV");
	return "Walk";
}

StateInfo SuperSheep::startWalk(StateInfo _state)
{
	return StateInfo();
}

StateInfo SuperSheep::updateWalk(StateInfo _state)
{
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

	if (GameEngineInput::GetInst().IsDown("Explosion"))
	{
		GameEngineSoundManager::GetInstance().PlaySoundByName("SUPERSHEEPRELEASE.WAV");
		soundWhoosh_.Play();
		return "Fly";
	}

	normalMove();
	return StateInfo();
}

StateInfo SuperSheep::startFly(StateInfo _state)
{
	mainRender_->ChangeAnimation("Fly", std::string("superSheep.bmp"));
	speed_ = float4::ZERO;
	direction_ = float4::UP;
	headPivot_ = direction_ * 15.f;
	headCollision_->SetPivot(headPivot_);
	groundCheckCollision_->SetPivot(float4::ZERO);
	bottomCenterCollision_->SetPivot(float4::ZERO);
	topCenterCollision_->SetPivot(float4::ZERO);
	return StateInfo();
}

StateInfo SuperSheep::updateFly(StateInfo _state)
{
	groundCheckCollision_->SetPivot(float4::ZERO);
	bottomCenterCollision_->SetPivot(float4::ZERO);
	topCenterCollision_->SetPivot(float4::ZERO);

	EffectSpawnTime_ += deltaTime_;
	if (EffectSpawnTime_ > 0.025f)
	{
		GetLevel<PlayLevel>()->CreatePurpleStarEffect(pos_);
		EffectSpawnTime_ = 0.f;
	}

	if (soundWhoosh_.GetPositionMillisecond() >= soundWhoosh_.GetLengthMillisecond() - 10)
	{
		soundWhoosh_.Play();
		soundWhoosh_.SetPosition(150);
	}

	float rotate = direction_.GetDegreeFromNegativeYAxisClockWise();
	int animIndex = static_cast<int>(rotate / 11.25f) * 2;

	if (animIndex < 0)
	{
		animIndex = 0;
	}
	else if (animIndex > 62)
	{
		animIndex = 62;
	}

	static bool bTemp = false;

	animDelay_ -= deltaTime_;
	if (animDelay_ < 0.0f)
	{
		bTemp = !bTemp;
		animDelay_ = ANIM_DELAY;
	}

	mainRender_->SetAnimationCurrentFrame(animIndex + (int)bTemp);

	if (GameEngineInput::GetInst().IsPress("LeftArrow"))
	{
		direction_ = float4::RadianToRotatefloat2(direction_, -deltaTime_ * 8.f);
	}
	if (GameEngineInput::GetInst().IsPress("RightArrow"))
	{
		direction_ = float4::RadianToRotatefloat2(direction_, deltaTime_ * 8.f);
	}

	headPivot_ = direction_ * 15.f;
	headCollision_->SetPivot(headPivot_);

	if (nullptr != headCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		soundWhoosh_.Stop();
		return "Explosion";
	}

	speed_ = direction_ * FLY_SPEED;
	normalMove();
	return StateInfo();
}

StateInfo SuperSheep::startExplosion(StateInfo _state)
{
	PlayLevel* level = (PlayLevel*)GetLevel();
	level->CreateExplosion100(pos_, 75, true);
	explosionDelay_ = 3.0f;
	mainRender_->Off();
	//GameEngineSoundManager::GetInstance().PlaySoundByName("Explosion1.wav");
	return StateInfo();
}

StateInfo SuperSheep::updateExplosion(StateInfo _state)
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
