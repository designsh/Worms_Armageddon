#include "FadeObject.h"
#include <GameEngineRenderer.h>
#include <GameEngineWindow.h>


// Static Var
// Static Func

// constructer destructer
FadeObject::FadeObject()
	: FadeState(this)
	, Alpha_(255.0f)
	, mainRender_(nullptr)
	, fadeInSpeed_(100.0f)
	, fadeOutSpeed_(100.0f)
{
}

FadeObject::~FadeObject()
{
}

void FadeObject::FadeIn() 
{
	FadeState.ChangeState("FadeIn");
}
void FadeObject::FadeOut() 
{
	FadeState.ChangeState("FadeOut");
}

void FadeObject::Start() 
{
	SetRenderOrder(static_cast<int>(RenderOrder::MAX));
	mainRender_ = CreateRenderer("Fade_Black");
	mainRender_->SetPivotPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	mainRender_->SetCameraEffectOff();

	FadeState.CreateState("FadeIn", &FadeObject::FadeInStart, &FadeObject::FadeInUpdate);
	FadeState.CreateState("FadeOut", &FadeObject::FadeOutStart, &FadeObject::FadeOutUpdate);
	FadeState.CreateState("Default", &FadeObject::DefaultStart, &FadeObject::DefaultUpdate);
	FadeState.ChangeState("Default");
}


void FadeObject::Update() 
{
	FadeState.Update();

}

void FadeObject::Render() 
{
	mainRender_->Render();
}

//member Func
StateInfo FadeObject::DefaultStart(StateInfo _Info)
{
	Alpha_ = 0.0f;
	return "";
}

StateInfo FadeObject::DefaultUpdate(StateInfo _Info)
{
	mainRender_->SetAlpha(static_cast<int>(Alpha_));
	return "";
}


StateInfo FadeObject::FadeInStart(StateInfo _Info)
{
	Alpha_ = 0.0f;
	return "";
}

StateInfo FadeObject::FadeOutStart(StateInfo _Info)
{
	Alpha_ = 255.0f;
	return "";
}

StateInfo FadeObject::FadeInUpdate(StateInfo _Info)
{
	Alpha_ += fadeInSpeed_ * GameEngineTime::GetInst().GetDeltaTime();
	mainRender_->SetAlpha(static_cast<int>(Alpha_));
	return "";
}

StateInfo FadeObject::FadeOutUpdate(StateInfo _Info)
{
	Alpha_ -= fadeOutSpeed_ * GameEngineTime::GetInst().GetDeltaTime();
	mainRender_->SetAlpha(static_cast<int>(Alpha_));
	return "";
}

void FadeObject::UpdateBefore()
{
}

void FadeObject::UpdateAfter()
{
}

void FadeObject::SetFadeInSpeed(float _fadeSpeed)
{
	fadeInSpeed_ = _fadeSpeed;
}

void FadeObject::SetFadeOutSpeed(float _fadeSpeed)
{
	fadeOutSpeed_ = _fadeSpeed;
}