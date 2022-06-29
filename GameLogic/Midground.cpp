#include "Midground.h"
#include <GameEngineRenderer.h>
Midground::Midground() // default constructer 디폴트 생성자
	: mainRender_(nullptr)
{
	SetPos({1350, 1400 });
	SetRenderOrder((int)RenderOrder::BackGround);
}

Midground::~Midground() // default destructer 디폴트 소멸자
{

}

Midground::Midground(Midground&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr)
{

}

void Midground::Start()
{
	mainRender_ = CreateRenderer("Midground");
	mainRender_->SetCameraEffectOn();
}

void Midground::UpdateBefore()
{

}

void Midground::Update()
{

}

void Midground::UpdateAfter()
{

}

void Midground::Render()
{
	mainRender_->Render();
}