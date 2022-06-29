#include "Effectkamismk.h"
#include "EffectActor.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineTime.h>

Effect::kamismk::kamismk()
{
}

Effect::kamismk::~kamismk()
{
}

Effect::kamismk::kamismk(kamismk&& _other) noexcept
{
}

void Effect::kamismk::Start()
{
	mainSpriteRender_ = CreateRenderer("kamismk");
	mainSpriteRender_->CreateAnimation("kamismk", "kamismk", 0, 9, false, 0.1f);
	mainSpriteRender_->ChangeAnimation("kamismk");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("kamismk", this, &EffectActor::Death);
}

void Effect::kamismk::UpdateBefore()
{
}

void Effect::kamismk::Update()
{
}

void Effect::kamismk::UpdateAfter()
{
}

void Effect::kamismk::Render()
{
	EffectActor::Render();
}
