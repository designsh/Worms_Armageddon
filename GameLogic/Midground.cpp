#include "Midground.h"
#include <GameEngineRenderer.h>
Midground::Midground() // default constructer ����Ʈ ������
	: mainRender_(nullptr)
{
	SetPos({1350, 1400 });
	SetRenderOrder((int)RenderOrder::BackGround);
}

Midground::~Midground() // default destructer ����Ʈ �Ҹ���
{

}

Midground::Midground(Midground&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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