#include "EffectFlame.h"
#include "EffectSmkdrk.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineTime.h>



Effect::Flame1::Flame1() :
	Dir_{},
	GravityAcc(0.f),
	GravitySpeed(0.f),
	ExplodeSpeed(0.f),
	gentime_(0.f),
	deltaTime_(0.f),
	smkdrk30_(nullptr)
{
}
Effect::Flame1::~Flame1()
{



}
Effect::Flame1::Flame1(Flame1&& _other) noexcept :
	Dir_{},
	GravityAcc(0.f),
	GravitySpeed(0.f),
	ExplodeSpeed(0.f),
	gentime_(0.f),
	deltaTime_(0.f),
	smkdrk30_(nullptr)
{
}

void Effect::Flame1::Start()
{
	GravityAcc = 6.f;
	ExplodeSpeed = 300.f;

	mainSpriteRender_ = CreateRenderer("flame1");
	mainSpriteRender_->CreateAnimation("flame1", "flame1", 0, 31, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("flame1");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("flame1", this, &EffectActor::Death);

	GameEngineMath::Random random;
	int randint = random.RandomInt(0, 15);

	mainSpriteRender_->SetAnimationCurrentFrame("flame1", randint);
}

void Effect::Flame1::UpdateBefore()
{
}

void Effect::Flame1::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();
	gentime_ += deltaTime_;
	if (gentime_ >0.07f)
	{
		smkdrk30_ = parentLevel_->CreateActor<Smkdrk30>(pos_);
		smkdrk30_->SetRenderOrder(static_cast<int>(RenderOrder::Effect));
		gentime_ = 0.f;
	}

	SetMove(Dir_ * (ExplodeSpeed * deltaTime_));
	ExplodeSpeed -= deltaTime_;
	//gravity
	{
		GravitySpeed += GravityAcc;
		SetMove(0.f,(GravitySpeed * deltaTime_));
	}
}

void Effect::Flame1::UpdateAfter()
{
}

void Effect::Flame1::Render()
{
	EffectActor::Render();
}


Effect::Flame2::Flame2() :
	Dir_{},
	GravityAcc(0.f),
	GravitySpeed(0.f),
	ExplodeSpeed(0.f),
	gentime(0.f),
	deltaTime_(0.f),
	smkdrk30_(nullptr)
{
}
Effect::Flame2::~Flame2()
{
}
Effect::Flame2::Flame2(Flame2&& _other) noexcept :
	Dir_{},
	GravityAcc(0.f),
	GravitySpeed(0.f),
	ExplodeSpeed(0.f),
	gentime(0.f),
	deltaTime_(0.f),
	smkdrk30_(nullptr)
{
}

void Effect::Flame2::Start()
{
	GravityAcc = 6.f;
	ExplodeSpeed = 300.f;

	mainSpriteRender_ = CreateRenderer("flame2");
	mainSpriteRender_->CreateAnimation("flame2", "flame2", 0, 31, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("flame2");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("flame2", this, &EffectActor::Death);

	GameEngineMath::Random random;
	int randint = random.RandomInt(0, 15);

	mainSpriteRender_->SetAnimationCurrentFrame("flame2", randint);
}

void Effect::Flame2::UpdateBefore()
{
}

void Effect::Flame2::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	gentime += deltaTime_;
	if (gentime > 0.07f)
	{
		smkdrk30_ = parentLevel_->CreateActor<Smkdrk30>(pos_);
		smkdrk30_->SetRenderOrder(static_cast<int>(RenderOrder::Effect));
		gentime = 0.f;
	}

	SetMove(Dir_ * (ExplodeSpeed * deltaTime_));
	ExplodeSpeed -= deltaTime_;
	//gravity
	{
		GravitySpeed += GravityAcc;
		SetMove(0.f, (GravitySpeed * deltaTime_));
	}
}

void Effect::Flame2::UpdateAfter()
{
}

void Effect::Flame2::Render()
{
	EffectActor::Render();
}