#include "WindBarBlank.h"
#include <GameEngineRenderer.h>
#include <EngineEnum.h>

WindBarBlank::WindBarBlank() // default constructer 디폴트 생성자
{
	SetRenderOrder((int)RenderOrder::UI);
	SetPos({1180,700});
}

WindBarBlank::~WindBarBlank() // default destructer 디폴트 소멸자
{

}

WindBarBlank::WindBarBlank(WindBarBlank&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void WindBarBlank::Start()
{
	mainRender_ = CreateRenderer("windGauge");
	mainRender_->SetCameraEffectOff();
}

void WindBarBlank::UpdateBefore()
{

}

void WindBarBlank::Update()
{

}

void WindBarBlank::UpdateAfter()
{

}

void WindBarBlank::Render()
{
	mainRender_->Render();
}