#include "HomingMissile.h"

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
#include "Explosion.h"
#include "GameController.h"
#include "MouseObject.h"

HomingMissile::HomingMissile()
	: mainRender_(nullptr)
	, groundCheckCollision_(nullptr)
	, accelation_(float4::ZERO)
	, speed_(float4(0.f, -300.f))
	, direction_(float4::RIGHT)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
	, launchTime_(1.f)
	, homingPos_(float4::ZERO)
	, rotPos_(float4::ZERO)
	, rotAngle_(0.f)
	, endTime_(3.f)
	, homingTime(0.f)
	, targetPos_(float4::ZERO)
	, soundWhoosh_("ShotGunFire.wav")
	, bHomingSound_(true)
	, explosionDelay_(0.0f)
	, bExplosionWait_(false)
{

}

HomingMissile::~HomingMissile() // default destructer 디폴트 소멸자
{

}

void HomingMissile::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);

	//mainRender_ = CreateRenderer("hmissil1");
	//mainRender_->ChangeAnimation("blueMissle");

	mainRender_ = CreateRenderer("hmissil2.bmp");
	mainRender_->CreateAnimation("redMissle", "hmissil2.bmp", 0, 31, true, 0.01f);
	mainRender_->CreateAnimation("blueMissle", "hmissil1.bmp", 0, 31, true, FLT_MAX);
	mainRender_->ChangeAnimation("redMissle");

	groundCheckCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::WEAPON), CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 1.f });

	wormPos_ = pos_;

	GameEngineSoundManager::GetInstance().PlaySoundByName("ShotGunFire.wav");
}

void HomingMissile::UpdateBefore()
{
	mainRender_->AnimationUpdate();
}

void HomingMissile::Update()
{
	prevPos_ = pos_;
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (bExplosionWait_)
	{
		explosionDelay_ -= deltaTime_;

		if (explosionDelay_ < 0.0f)
		{
			parentWorm_->BulletFocusOff();
			MouseObject* mouse = (MouseObject*)GetLevel()->FindActor("PlayLevelMouse");
			mouse->MouseBlock(false);
			parentWorm_->SubtractActionToken(1);
			Death();
		}
		return;
	}

	if (nullptr == groundCheckCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		launchTime_ -= deltaTime_;

		PlayLevel* level = (PlayLevel*)GetLevel();
		float windSpeed = level->GetGameController()->GetWindController()->GetCurrentWindSpeed();

		if (launchTime_ >= 0.f)
		{
			bGround_ = false;

			speed_.x += windSpeed * deltaTime_;
			speed_.y += GRAVITY_POWER * deltaTime_;
			float4 MovePos = speed_ * deltaTime_;
			SetMove(MovePos);

			startPos_ = pos_;
			rotPos_.x = windSpeed * 0.1f;
			rotPos_.y = 0.f;
		}
		else if (endTime_ >= 0.f)
		{
			if (true == bHomingSound_)
			{
				GameEngineSoundManager::GetInstance().PlaySoundByName("WEAPONHOMING.WAV");
				bHomingSound_ = false;
			}

			endTime_ -= deltaTime_;
			homingTime -= deltaTime_;

			mainRender_->ChangeAnimation("blueMissle", std::string("hmissil1.bmp"));

			float Radian = rotAngle_ * GameEngineMath::RadianToDegree;

			float4 MovePos;

			MovePos.x = rotPos_.x * cosf(Radian) - rotPos_.y * sinf(Radian);
			MovePos.y = rotPos_.x * sinf(Radian) + rotPos_.y * cosf(Radian);

			MovePos += homingPos_;

			float4 MoveVector = MovePos - pos_;

			float4 normalizeVector = Normalize(MoveVector);

			if (homingTime <= 0.f)
			{
				targetPos_ = normalizeVector;
				homingTime = 0.25f;
				rotAngle_ += 90.f;
			}

			SetMove(targetPos_ * 6.f);

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

			speed_ = MoveVector;
		}
		else
		{
			mainRender_->ChangeAnimation("redMissle", std::string("hmissil2.bmp"));

			speed_.x += windSpeed * deltaTime_;
			speed_.y += GRAVITY_POWER * deltaTime_;
			float4 MovePos = speed_ * deltaTime_;
			SetMove(MovePos);
		}
	}
	else
	{
		explosionDelay_ = 3.0f;
		bExplosionWait_ = true;

		PlayLevel* level = (PlayLevel*)GetLevel();
		level->CreateExplosion100(pos_, 75, true);
		mainRender_->Off();
		//GameEngineSoundManager::GetInstance().PlaySoundByName("Explosion1.wav");
	}

}

void HomingMissile::UpdateAfter()
{
}

void HomingMissile::Render()
{
	if (mainRender_->IsOn())
	{
		mainRender_->Render();
	}
}

