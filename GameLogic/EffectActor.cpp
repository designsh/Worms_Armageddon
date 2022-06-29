#include <GameEngineRenderer.h>
#include "EffectActor.h"

EffectActor::EffectActor() :
	mainSpriteRender_(nullptr),
	Dir_{}
{
}

EffectActor::~EffectActor()
{
}

EffectActor::EffectActor(EffectActor&& _other) noexcept :
	mainSpriteRender_(nullptr),
	Dir_{}
{
}

void EffectActor::Start()
{

}

void EffectActor::UpdateBefore()
{
}

void EffectActor::Update()
{
}

void EffectActor::UpdateAfter()
{
}

void EffectActor::Render()
{
	mainSpriteRender_->AnimationUpdate();
}
