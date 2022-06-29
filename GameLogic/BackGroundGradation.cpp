#include "BackGroundGradation.h"
#include <GameEngineRenderer.h>
#include <GameEngineWindow.h>
BackGroundGradation::BackGroundGradation() // default constructer ����Ʈ ������
{
	SetRenderOrder((int)RenderOrder::MIN);
}

BackGroundGradation::~BackGroundGradation() // default destructer ����Ʈ �Ҹ���
{

}

BackGroundGradation::BackGroundGradation(BackGroundGradation&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void BackGroundGradation::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	mainRender_ = CreateRenderer("Gradient");
	float4 ImageSize = mainRender_->GetImageSize();
	mainRender_->SetPivotPos(ImageSize.halffloat4());
	mainRender_->SetCameraEffectOff();
	mainRender_->SetRenderSize(WindowSize);
}
void BackGroundGradation::UpdateBefore()
{

}
void BackGroundGradation::Update()
{

}
void BackGroundGradation::UpdateAfter()
{

}
void BackGroundGradation::Render()
{
	mainRender_->Render();
}