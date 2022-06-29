#include "Effectex.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineMath.h>

Effect::ex::ex()
{
}

Effect::ex::~ex()
{
}

Effect::ex::ex(ex&& _other) noexcept
{
}

void Effect::ex::Start()
{
	GameEngineMath::Random random;
	int ranint = random.RandomInt(0, 3);

	switch (ranint)
	{
	case 0:
		mainSpriteRender_ = CreateRenderer("exbiff");
		mainSpriteRender_->CreateAnimation("exbiff", "exbiff", 0, 11, false, 0.041f);
		mainSpriteRender_->ChangeAnimation("exbiff");

		mainSpriteRender_->SetAnimationEndFunction<EffectActor>
			("exbiff", this, &EffectActor::Death);
		return;
	case 1:
		mainSpriteRender_ = CreateRenderer("expoot");
		mainSpriteRender_->CreateAnimation("expoot", "expoot", 0, 17, false, 0.027f);
		mainSpriteRender_->ChangeAnimation("expoot");

		mainSpriteRender_->SetAnimationEndFunction<EffectActor>
			("expoot", this, &EffectActor::Death);
		return;
	case 2:
		mainSpriteRender_ = CreateRenderer("expow");
		mainSpriteRender_->CreateAnimation("expow", "expow", 0, 11, false, 0.041f);
		mainSpriteRender_->ChangeAnimation("expow");

		mainSpriteRender_->SetAnimationEndFunction<EffectActor>
			("expow", this, &EffectActor::Death);
		return;
	case 3:
		mainSpriteRender_ = CreateRenderer("exfoom");
		mainSpriteRender_->CreateAnimation("exfoom", "exfoom", 0, 19, false, 0.025f);
		mainSpriteRender_->ChangeAnimation("exfoom");

		mainSpriteRender_->SetAnimationEndFunction<EffectActor>
			("exfoom", this, &EffectActor::Death);
		return;
	default:
		GameEngineDebug::MsgBoxError("무작위 난수 오류");
		return;
	}

}

void Effect::ex::UpdateBefore()
{
}

void Effect::ex::Update()
{
}

void Effect::ex::UpdateAfter()
{
}

void Effect::ex::Render()
{
	EffectActor::Render();
}
