#include "Aim.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>
#include <GameEngineSoundManager.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"

Aim::Aim()
	: mainRender_(nullptr)
	, endPos_(float4::RIGHT)
	, power_(false)
	, maxTime_(1.f)
	, deltaTime_(0.f)
	, tickTime_(0.f)
	, tickTimeBase_(0.f)
	, startPos_(float4::ZERO)
	, nextPos_(float4::ZERO)
	, imageIndex_(0)
	, parentAim_(false)
	, renderOn(false)
{
}

Aim::~Aim()
{
}

void Aim::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);
	mainRender_ = CreateRenderer("blob");

	mainRender_->CreateAnimation("blob", "blob", 0, 15, true, FLT_MAX);
	mainRender_->ChangeAnimation("blob");
	//mainRender_->SetAnimationCurrentFrame(imageIndex_);
}

void Aim::UpdateBefore()
{
}

void Aim::Update()
{
	if (parentAim_)
	{
		deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

		tickTime_ -= deltaTime_;

		if (tickTime_ <= 0.f && imageIndex_ < 16)
		{
			if (false == renderOn)
			{
				renderOn = true;
				childAim_.push_back(this);
			}

			tickTime_ = tickTimeBase_;
			NextAimRender();
			++imageIndex_;
		}
	}
}

void Aim::UpdateAfter()
{
}

void Aim::Render()
{
	if (true == renderOn)
	{
		mainRender_->AnimationUpdate();
	}
}

void Aim::NextAimRender()
{
	float4 Pos = nextPos_;
	Pos.x *= (float)imageIndex_;
	Pos.y *= (float)imageIndex_;

	Aim* newAim = parentLevel_->CreateActor<Aim>();
	newAim->SetChildAim(startPos_ + Pos, imageIndex_);
	childAim_.push_back(newAim);
}

void Aim::AimClear()
{
	parentAim_ = false;

	std::vector<Aim*>::iterator iter = childAim_.begin();

	for (; iter != childAim_.end(); ++iter)
	{
		(*iter)->Death();
	}
}

void Aim::SetAim(float _MaxTime, float4 _EndPos, float4 _Pos)
{
	maxTime_ = _MaxTime;
	endPos_ = _EndPos;
	pos_ = _Pos;
	startPos_ = _Pos;
	parentAim_ = true;

	tickTime_ = maxTime_ * 0.0625f;
	tickTimeBase_ = maxTime_ * 0.0625f;

	float4 Pos = endPos_ - startPos_;

	Pos.x *= 0.0625f;
	Pos.y *= 0.0625f;

	nextPos_ = Pos;
}

void Aim::SetChildAim(float4 _Pos, int _ImageIndex)
{
	parentAim_ = false;
	pos_ = _Pos;
	mainRender_->SetAnimationCurrentFrame(_ImageIndex);
	renderOn = true;
}
