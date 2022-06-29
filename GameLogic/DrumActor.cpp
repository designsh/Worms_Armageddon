#include "DrumActor.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>
#include <GameEngineInput.h>
#include <GameEngineDebugExtension.h>

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

#include "PlayLevel.h"
#include "WindController.h"
#include "GameController.h"
#include "Petroleum.h"

#define COUNT 40

DrumActor::DrumActor():
	Phase_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	PetroleumSpeed(150.f),
	deltaTime_(0.f),
	degree_(0.f),
	WindSpeed_(0.f),
	random_{}
	// default constructer 디폴트 생성자
{
}

DrumActor::~DrumActor() // default destructer 디폴트 소멸자
{
}

DrumActor::DrumActor(DrumActor&& _other) noexcept :
	Phase_(0.f),
	mainSpriteRender_(nullptr) , // default RValue Copy constructer 디폴트 RValue 복사생성자
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	PetroleumSpeed(150.f),
	deltaTime_(0.f),
	degree_(0.f),
	WindSpeed_(0.f),
	random_{}
{
}

void DrumActor::Start()
{
	SetRenderOrder(static_cast<int>(RenderOrder::Drum));
	mainSpriteRender_ = CreateRenderer("oildrum1");

	mainSpriteRender_->CreateAnimation("oildrum1", "oildrum1", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("oildrum2", "oildrum2", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("oildrum3", "oildrum3", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("oildrum4", "oildrum4", 0, 19, true, 0.1f);

	mainSpriteRender_->ChangeAnimation("oildrum1");

	initCollision();
}

void DrumActor::UpdateBefore()
{
}

void DrumActor::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (nullptr != BodyCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::WEAPON)))
	{
		DrumExplode();
		return;
	}

	else if (nullptr != BodyCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::PETROLEUM_HITBOX)))
	{
		Phase_ += deltaTime_;
		
		if (Phase_ >= 1.f)
		{
			DrumExplode();
			return;
		}

		else if (Phase_ > 0.75f)
		{
			mainSpriteRender_->ChangeAnimation("oildrum4", std::string("oildrum4"));

			mainSpriteRender_->SetAnimationCurrentFrame(mainSpriteRender_->GetCurAnimationFrame());
		}
		else if (Phase_ > 0.5f)
		{
			mainSpriteRender_->ChangeAnimation("oildrum3", std::string("oildrum3"));
			mainSpriteRender_->SetAnimationCurrentFrame(mainSpriteRender_->GetCurAnimationFrame());
		}
		else if (Phase_ > 0.25f)
		{
			mainSpriteRender_->ChangeAnimation("oildrum2", std::string("oildrum2"));
			mainSpriteRender_->SetAnimationCurrentFrame(mainSpriteRender_->GetCurAnimationFrame());
		}
	}

	if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		SetMove(0.f,500.f* deltaTime_);
	}
}

void DrumActor::UpdateAfter()
{
}


void DrumActor::Render()
{
#ifdef _DEBUG
	//if (GetLevel<PlayLevel>()->GetDebug())
	//{
	//	BodyCollision_->DebugRender();
	//	groundCollision_->DebugRender();
	//}
#endif // DEBUG
	mainSpriteRender_->AnimationUpdate();
}

void DrumActor::initCollision()
{
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::DRUM), CollisionCheckType::POINT);
	groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCollision_->SetPivot({ 0.f, 17.f });

	BodyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::DRUM), CollisionCheckType::RECT);
	BodyCollision_->SetSize({ 30.f, 40.f });

}

void DrumActor::DrumExplode()
{
	WindSpeed_ = GetLevel<PlayLevel>()->GetGameController()->GetWindController()->GetCurrentWindSpeed();

	// 촘촘히 약 5방향으로 나누어, 군집되도록 생성하기
	GetLevel<PlayLevel>()->CreateExplosion75(pos_,100);

	float RandomFloat;
	float4 RandomRot = { 1.f,0.f,0.f };

	for (int i = 0; i < 5; ++i)
	{
		RandomFloat = random_.RandomFloat(-20.f, 20.f);
		degree_ = (360.f * 0.2f * i) + RandomFloat;

		for (int j = 0; j < (COUNT / 5); ++j)
		{
			RandomRot = { 1.f,0.f,0.f }; //초기화
			RandomFloat = random_.RandomFloat(-20.f, 20.f);
			float degree__ = degree_ + RandomFloat;

			RandomRot = RandomRot.DegreeTofloat2(degree__);

			RandomRot.x *= PetroleumSpeed+ RandomFloat;
			RandomRot.y *= PetroleumSpeed+ RandomFloat;

			Petroleum* _Petroleum = parentLevel_->CreateActor<Petroleum>(pos_);
			GetLevel<PlayLevel>()->GetGameController()->IncresePetroleumCount();

			_Petroleum->SetRenderOrder((int)RenderOrder::Effect);
			_Petroleum->SetDir(RandomRot);
			_Petroleum->SetWindSpeed(WindSpeed_);
		}
	}
	Death();
}



