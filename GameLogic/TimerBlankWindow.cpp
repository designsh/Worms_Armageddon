#include "TimerBlankWindow.h"
#include "Worm.h"
#include <GameEngineRenderer.h>

TimerBlankWindow::TimerBlankWindow() // default constructer 디폴트 생성자
	: mainRender_(nullptr), parent_(nullptr), isWormLinked_(false)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

TimerBlankWindow::~TimerBlankWindow() // default destructer 디폴트 소멸자
{

}

TimerBlankWindow::TimerBlankWindow(TimerBlankWindow&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr), parent_(nullptr), isWormLinked_(false)
{

}


void TimerBlankWindow::Start()
{
	mainRender_ = CreateRenderer("TimerWindowR");
	SetPos({40,690});
	mainRender_->SetCameraEffectOff();
}
void TimerBlankWindow::UpdateBefore()
{

}
void TimerBlankWindow::Update()
{

}
void TimerBlankWindow::UpdateAfter()
{

}
void TimerBlankWindow::Render()
{
	if (true == isWormLinked_)
	{
		if (true == parent_->isFocused())
		{
			mainRender_->Render();
		}
	}
}

void TimerBlankWindow::RenderColorInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:
		mainRender_ = CreateRenderer("TimerWindowR");
		break;
	case 1:
		mainRender_ = CreateRenderer("TimerWindowB");
		break;
	case 2:
		mainRender_ = CreateRenderer("TimerWindowG");
		break;
	case 3:
		mainRender_ = CreateRenderer("TimerWindowY");
		break;
	case 4:
		mainRender_ = CreateRenderer("TimerWindowP");
		break;
	case 5:
		mainRender_ = CreateRenderer("TimerWindowC");
		break;
	case 6:
		mainRender_ = CreateRenderer("TimerWindowR");
		break;
	case 7:
		mainRender_ = CreateRenderer("TimerWindowR");
		break;
	default:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	}
	mainRender_->SetCameraEffectOff();
}
