#include "WindBarBlank.h"
#include <GameEngineRenderer.h>
#include <EngineEnum.h>

WindBarBlank::WindBarBlank() // default constructer ����Ʈ ������
{
	SetRenderOrder((int)RenderOrder::UI);
	SetPos({1180,700});
}

WindBarBlank::~WindBarBlank() // default destructer ����Ʈ �Ҹ���
{

}

WindBarBlank::WindBarBlank(WindBarBlank&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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