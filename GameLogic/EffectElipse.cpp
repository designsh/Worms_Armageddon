#include "EffectElipse.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>



Effect::Elipse25::Elipse25()
{
}
Effect::Elipse25::~Elipse25()
{
}
Effect::Elipse25::Elipse25(Elipse25&& _other) noexcept
{
}

void Effect::Elipse25::Start()
{
	mainSpriteRender_ = CreateRenderer("elipse25");
	mainSpriteRender_->CreateAnimation("elipse25", "elipse25", 0, 7, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("elipse25");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>("elipse25", this, &EffectActor::Death);
}

void Effect::Elipse25::UpdateBefore()
{
}

void Effect::Elipse25::Update()
{
}

void Effect::Elipse25::UpdateAfter()
{
}

void Effect::Elipse25::Render()
{
	EffectActor::Render();
}

Effect::Elipse50::Elipse50() 
{
}
Effect::Elipse50::~Elipse50()
{
}
Effect::Elipse50::Elipse50(Elipse50&& _other) noexcept
{
}

void Effect::Elipse50::Start()
{
	mainSpriteRender_ = CreateRenderer("elipse50");
	mainSpriteRender_->CreateAnimation("elipse50", "elipse50", 0, 7, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("elipse50");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>("elipse50", this, &EffectActor::Death);
}

void Effect::Elipse50::UpdateBefore()
{
}

void Effect::Elipse50::Update()
{
}

void Effect::Elipse50::UpdateAfter()
{
}

void Effect::Elipse50::Render()
{
	EffectActor::Render();
}

Effect::Elipse75::Elipse75()
{
}
Effect::Elipse75::~Elipse75()
{
}
Effect::Elipse75::Elipse75(Elipse75&& _other) noexcept
{
}

void Effect::Elipse75::Start()
{
	mainSpriteRender_ = CreateRenderer("elipse75");
	mainSpriteRender_->CreateAnimation("elipse75", "elipse75", 0, 9, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("elipse75");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>("elipse75", this, &EffectActor::Death);
}

void Effect::Elipse75::UpdateBefore()
{
}

void Effect::Elipse75::Update()
{
}

void Effect::Elipse75::UpdateAfter()
{
}

void Effect::Elipse75::Render()
{
	EffectActor::Render();
}

Effect::Elipse100::Elipse100() 
{
}
Effect::Elipse100::~Elipse100() 
{
}
Effect::Elipse100::Elipse100(Elipse100&& _other) noexcept
{
}

void Effect::Elipse100::Start()
{
	mainSpriteRender_ = CreateRenderer("elipse100");
	mainSpriteRender_->CreateAnimation("elipse100", "elipse100", 0, 9, false, 0.05f);
	mainSpriteRender_->ChangeAnimation("elipse100");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>("elipse100", this, &EffectActor::Death);
}

void Effect::Elipse100::UpdateBefore()
{
}

void Effect::Elipse100::Update()
{
}

void Effect::Elipse100::UpdateAfter()
{
}

void Effect::Elipse100::Render()
{
	EffectActor::Render();
}