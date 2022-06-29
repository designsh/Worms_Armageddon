#include "AirStrike.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>
#include <GameEngineSoundManager.h>

#include "PlayLevel.h"
#include "AirStrikeBullet.h"

AirStrike::AirStrike()
	: mainRender_(nullptr)
	, direction_(float4::RIGHT)
	, deltaTime_(0.0f)
	, firePoint_()
	, destroyTime_(7.f)
	, fireTime_(0.0f)
	, fire_(false)
	, fireCount_(5)
{

}

AirStrike::~AirStrike() // default destructer 디폴트 소멸자
{

}

void AirStrike::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);

	mainRender_ = CreateRenderer("airjetbLeft");

	GameEngineSoundManager::GetInstance().PlaySoundByName("ROCKETRELEASE.WAV");
}

void AirStrike::UpdateBefore()
{

}

void AirStrike::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	SetMove(direction_ * 1000.f * deltaTime_);

	destroyTime_ -= deltaTime_;

	if (destroyTime_ <= 0.f)
	{
		Death();
	}

	//if (GetPos().DistanceTo(firePoint_) <= 15.f)
	//{
	//	fire_ = true;
	//}

	float4 pos = GetPos();
	if (abs(firePoint_.x - pos.x) < 20)
	{
		fire_ = true;

	}

	if (true == fire_)
	{
		fireTime_ -= deltaTime_;

		if (fireTime_ <= 0.f && fireCount_ != 0)
		{
			AirStrikeBullet* newAirStrike = parentLevel_->CreateActor<AirStrikeBullet>();
			newAirStrike->SetPos(float4(pos_.x, pos_.y + 20.f));
			newAirStrike->SetParentWorm(parentWorm_);
			parentWorm_->BulletFocusOn(newAirStrike);
			fireTime_ = 0.03f;
			--fireCount_;
		}
	}
}

void AirStrike::UpdateAfter()
{
}

void AirStrike::Render()
{
	mainRender_->Render();
}

void AirStrike::SetAirStrike(bool _Left, float4 _Pos)
{
	firePoint_ = _Pos;
	
	if (true == _Left)
	{
		direction_ = float4::RIGHT;
		mainRender_ = CreateRenderer("airjetbRight");

		SetPos(float4(_Pos.x - 1000.f, _Pos.y - 400.f));
	}
	else
	{
		direction_ = float4::LEFT;
		SetPos(float4(_Pos.x + 1000.f, _Pos.y - 400.f));
	}
}