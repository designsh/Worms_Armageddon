
#include "EffectCircle.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>



Effect::Circle25::Circle25()
{
}
Effect::Circle25::~Circle25()
{
}
Effect::Circle25::Circle25(Circle25&& _other) noexcept 
{
}

void Effect::Circle25::Start()
{
	mainSpriteRender_ = CreateRenderer("circle25");
	mainSpriteRender_->CreateAnimation("circle25", "circle25", 0, 7, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("circle25");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>("circle25", this, &EffectActor::Death);
}

void Effect::Circle25::UpdateBefore()
{
}

void Effect::Circle25::Update()
{
}

void Effect::Circle25::UpdateAfter()
{
}

void Effect::Circle25::Render()
{
	EffectActor::Render();
}

Effect::Circle50::Circle50()
{
}
Effect::Circle50::~Circle50()
{
}
Effect::Circle50::Circle50(Circle50&& _other) noexcept 
{
}

void Effect::Circle50::Start()
{
	mainSpriteRender_ = CreateRenderer("circle50");
	mainSpriteRender_->CreateAnimation("circle50", "circle50", 0, 7, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("circle50");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>("circle50", this, &EffectActor::Death);
}

void Effect::Circle50::UpdateBefore()
{
}

void Effect::Circle50::Update()
{
}

void Effect::Circle50::UpdateAfter()
{
}

void Effect::Circle50::Render()
{
	EffectActor::Render();
}

Effect::Circle75::Circle75()
{
}
Effect::Circle75::~Circle75()
{
}
Effect::Circle75::Circle75(Circle75&& _other) noexcept
{
}

void Effect::Circle75::Start()
{
	mainSpriteRender_ = CreateRenderer("circle75");
	mainSpriteRender_->CreateAnimation("circle75", "circle75", 0, 3, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("circle75");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>("circle75", this, &EffectActor::Death);
}

void Effect::Circle75::UpdateBefore()
{
}

void Effect::Circle75::Update()
{
}

void Effect::Circle75::UpdateAfter()
{
}

void Effect::Circle75::Render()
{
	EffectActor::Render();
}

Effect::Circle100::Circle100() 
{
}
Effect::Circle100::~Circle100() 
{
}
Effect::Circle100::Circle100(Circle100&& _other) noexcept 
{
}

void Effect::Circle100::Start()
{
	mainSpriteRender_ = CreateRenderer("circle100");
	mainSpriteRender_->CreateAnimation("circle100", "circle100", 0, 3, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("circle100");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>("circle100", this, &EffectActor::Death);
}

void Effect::Circle100::UpdateBefore()
{
}

void Effect::Circle100::Update()
{
}

void Effect::Circle100::UpdateAfter()
{
}

void Effect::Circle100::Render()
{
	EffectActor::Render();
}