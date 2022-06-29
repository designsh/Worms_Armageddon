#include "EndingImage.h"
#include "EndingText.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineLevelManager.h>
#include <GameEngineTime.h>

EndingImage::EndingImage() :
	EndingImageRender_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround));
}

EndingImage::~EndingImage()
{
}

void EndingImage::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 ImageHarf = float4::ZERO;

	// 엔딩 이미지 생성 및 Off
	EndingImageRender_ = CreateRenderer("Ending_BackDrop");
	ImageHarf = EndingImageRender_->GetImageSize().halffloat4();
	EndingImageRender_->SetPivotPos(ImageHarf);
	EndingImageRender_->SetRenderSize(WindowSize);
	EndingImageRender_->SetCameraEffectOff();
	//EndingImageRender_->Off();
}

void EndingImage::UpdateBefore()
{
}

void EndingImage::Update()
{
	// 커서 On
	ShowCursor(true);
}

void EndingImage::UpdateAfter()
{
}

void EndingImage::Render()
{
	if (true == EndingImageRender_->IsOn())
	{
		EndingImageRender_->Render();
	}
}
