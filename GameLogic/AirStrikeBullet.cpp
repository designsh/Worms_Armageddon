#include "AirStrikeBullet.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>
#include <GameEngineSoundManager.h>

#include "WindController.h"
#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"
#include "PlayLevel.h"
#include "GameController.h"
#include "Explosion.h"

AirStrikeBullet::AirStrikeBullet()
	: mainRender_(nullptr)
	, groundCheckCollision_(nullptr)
	, accelation_(float4::ZERO)
	, speed_(float4(0.f, 200.f))
	, direction_(float4::RIGHT)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
{

}

AirStrikeBullet::~AirStrikeBullet() // default destructer 디폴트 소멸자
{

}

void AirStrikeBullet::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);

	mainRender_ = CreateRenderer("airmisl.bmp");
	//
	mainRender_->CreateAnimation("airmisl1", "airmisl.bmp", 0, 31, true, FLT_MAX);
	mainRender_->ChangeAnimation("airmisl1");

	groundCheckCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::WEAPON), CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 1.f });

	GameEngineSoundManager::GetInstance().PlaySoundByName("ROCKETRELEASE.WAV");
}

void AirStrikeBullet::UpdateBefore()
{

}

void AirStrikeBullet::Update()
{
	prevPos_ = pos_;
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (nullptr == groundCheckCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		PlayLevel* level = (PlayLevel*)GetLevel();
		float windSpeed = level->GetGameController()->GetWindController()->GetCurrentWindSpeed();

		bGround_ = false;

		speed_.x += windSpeed * deltaTime_;
		speed_.y += GRAVITY_POWER * deltaTime_;
		float4 MovePos = speed_ * deltaTime_;
		SetMove(MovePos);

		float4 moveVector = pos_ - prevPos_;
		float normalize = sqrtf(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
		moveVector.x /= normalize;
		moveVector.y /= normalize;

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

		degree_ += 5.625f;

		if (degree_ > 360.f)
		{
			degree_ -= 360.f;
		}

		int frameIndex = (int)(degree_ / 11.25);
		mainRender_->SetAnimationCurrentFrame(frameIndex);
	}
	else
	{
		PlayLevel* level = (PlayLevel*)GetLevel();
		level->CreateExplosion75(pos_);

		//GameEngineSoundManager::GetInstance().PlaySoundByName("Explosion1.wav");
		parentWorm_->BulletFocusOff();
		Death();
	}
}

void AirStrikeBullet::UpdateAfter()
{
}

void AirStrikeBullet::Render()
{
	mainRender_->AnimationUpdate();
}

