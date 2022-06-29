#include "TimerDigit.h"
#include "TimerManager.h"
#include "Worm.h"
#include <GameEngineRenderer.h>

TimerDigit::TimerDigit() // default constructer 디폴트 생성자
	: mainRender_(nullptr), timerManager_(nullptr), curCount_(0.0f), parent_(nullptr), isWormLinked_(false)
{

}

TimerDigit::~TimerDigit() // default destructer 디폴트 소멸자
{

}

TimerDigit::TimerDigit(TimerDigit&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr), timerManager_(nullptr), curCount_(0.0f), parent_(nullptr), isWormLinked_(false)
{

}

void TimerDigit::AnimationInit()
{
	mainRender_ = CreateRenderer("TimerNum");
	mainRender_->CreateAnimation("0", "TimerNum", 0, 0, false, 1.0f);
	mainRender_->CreateAnimation("1", "TimerNum", 1, 1, false, 1.0f);
	mainRender_->CreateAnimation("2", "TimerNum", 2, 2, false, 1.0f);
	mainRender_->CreateAnimation("3", "TimerNum", 3, 3, false, 1.0f);
	mainRender_->CreateAnimation("4", "TimerNum", 4, 4, false, 1.0f);
	mainRender_->CreateAnimation("5", "TimerNum", 5, 5, false, 1.0f);
	mainRender_->CreateAnimation("6", "TimerNum", 6, 6, false, 1.0f);
	mainRender_->CreateAnimation("7", "TimerNum", 7, 7, false, 1.0f);
	mainRender_->CreateAnimation("8", "TimerNum", 8, 8, false, 1.0f);
	mainRender_->CreateAnimation("9", "TimerNum", 9, 9, false, 1.0f);
	mainRender_->ChangeAnimation("0");
}


void TimerDigit::Start()
{
	AnimationInit();
	SetRenderOrder(static_cast<int>(RenderOrder::UI1));
	mainRender_->SetCameraEffectOff();
}
void TimerDigit::UpdateBefore()
{

}
void TimerDigit::Update()
{
	// 숫자는 표시만 해 줄 뿐이며 카운트는 게임컨트롤러가 해 줄 수 있도록 합니다.
}

void TimerDigit::SetNumber(int _number)
{
	mainRender_->ChangeAnimation(std::to_string(_number));
}

void TimerDigit::UpdateAfter()
{

}
void TimerDigit::Render()
{
	if (true == isWormLinked_)
	{
		if (true == parent_->isFocused())
		{

			mainRender_->AnimationUpdate();
		}
	}
}

void TimerDigit::SetTenDigitTime(float _time)
{
	int remain = _time / 10;

	mainRender_->ChangeAnimation(std::to_string(remain));
}
void TimerDigit::SetDigitTime(float _time)
{
	int remain = static_cast<int>(_time) % 10;
	mainRender_->ChangeAnimation(std::to_string(remain));
}