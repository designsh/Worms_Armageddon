#include "MenuSelBackDrop.h"
#include <EngineEnum.h>

#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>

MenuSelBackDrop::MenuSelBackDrop() :
	mainrenderer_(nullptr),
	titlerenderer_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround));
}

MenuSelBackDrop::~MenuSelBackDrop() // default destructer 디폴트 소멸자
{

}

MenuSelBackDrop::MenuSelBackDrop(MenuSelBackDrop&& _other) noexcept :
	mainrenderer_(_other.mainrenderer_),
	titlerenderer_(_other.titlerenderer_)
{

}

void MenuSelBackDrop::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	// BackDrop
	mainrenderer_ = CreateRenderer("MenuSel_BackDrop");
	float4 ImageSizeHarf = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(ImageSizeHarf);
	mainrenderer_->SetRenderSize(WindowSize);
	mainrenderer_->SetCameraEffectOff();

	// Title Text
	titlerenderer_ = CreateRenderer("MenuSel_Title");
	ImageSizeHarf = titlerenderer_->GetImageSize().halffloat4();
	titlerenderer_->SetPivotPos(float4(ImageSizeHarf.x + 320.f, ImageSizeHarf.y));
	titlerenderer_->SetRenderSize(float4(600.f, 206.f));
	titlerenderer_->SetCameraEffectOff();
}

void MenuSelBackDrop::UpdateBefore()
{
}

void MenuSelBackDrop::Update()
{
}

void MenuSelBackDrop::UpdateAfter()
{
}

void MenuSelBackDrop::Render()
{
	mainrenderer_->Render();

	titlerenderer_->Render();
}
