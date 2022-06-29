#include "WormHPBlankWindow.h"
#include "Worm.h"
#include <GameEngineRenderer.h>
WormHPBlankWindow::WormHPBlankWindow() // default constructer 디폴트 생성자
	: mainRender_(nullptr), parent_(nullptr), isWormLinked_(false)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

WormHPBlankWindow::~WormHPBlankWindow() // default destructer 디폴트 소멸자
{

}

WormHPBlankWindow::WormHPBlankWindow(WormHPBlankWindow&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr), parent_(nullptr), isWormLinked_(false)
{

}


void WormHPBlankWindow::Start()
{
	mainRender_ = CreateRenderer("WormHP");
	mainRender_->SetCameraEffectOn();
}
void WormHPBlankWindow::UpdateBefore()
{

}
void WormHPBlankWindow::Update()
{
	if (true == isWormLinked_)
	{
		SetPos({ parent_->GetPos().x, (parent_->GetPos().y - 32.0f) });
	}
}
void WormHPBlankWindow::UpdateAfter()
{

}
void WormHPBlankWindow::Render()
{
	if (true == isWormLinked_)
	{
			mainRender_->Render();
	}
}

void WormHPBlankWindow::StartPosInit(int _wormNumber)
{

}