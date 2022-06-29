#include "BackGroundGradation.h"
#include <GameEngineRenderer.h>
#include <GameEngineWindow.h>
BackGroundGradation::BackGroundGradation() // default constructer 디폴트 생성자
{
	SetRenderOrder((int)RenderOrder::MIN);
}

BackGroundGradation::~BackGroundGradation() // default destructer 디폴트 소멸자
{

}

BackGroundGradation::BackGroundGradation(BackGroundGradation&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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