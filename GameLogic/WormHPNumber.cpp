#include "WormHPNumber.h"
#include <GameEngineRenderer.h>
#include <GameEngineTime.h>

#include "GameOptionInfo.h"
#include "Worm.h"
WormHPNumber::WormHPNumber() // default constructer 디폴트 생성자
	: mainRender_(nullptr), isDigitTen_(false), parent_(nullptr), isWormLinked_(false), deltaTime_(0.0f)
{

}

WormHPNumber::~WormHPNumber() // default destructer 디폴트 소멸자
{

}

WormHPNumber::WormHPNumber(WormHPNumber&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr), isDigitTen_(false), parent_(nullptr), isWormLinked_(false), deltaTime_(0.0f)
{

}



void WormHPNumber::StartPosInit(int _wormNumber)
{

}



void WormHPNumber::ColorInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:

		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 20, 20, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 21, 21, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 22, 22, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 23, 23, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 24, 24, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 25, 25, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 26, 26, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 27, 27, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 28, 28, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 29, 29, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;
	case 1:
		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 30, 30, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 31, 31, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 32, 32, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 33, 33, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 34, 34, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 35, 35, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 36, 36, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 37, 37, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 38, 38, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 39, 39, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;
	case 2:
		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 40, 40, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 41, 41, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 42, 42, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 43, 43, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 44, 44, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 45, 45, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 46, 46, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 47, 47, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 48, 48, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 49, 49, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;
	case 3:
		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 50, 50, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 51, 51, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 52, 52, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 53, 53, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 54, 54, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 55, 55, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 56, 56, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 57, 57, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 58, 58, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 59, 59, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;
	case 4:
		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 70, 70, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 71, 71, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 72, 72, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 73, 73, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 74, 74, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 75, 75, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 76, 76, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 77, 77, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 78, 78, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 79, 79, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;

	case 5:
		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 60, 60, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 61, 61, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 62, 62, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 63, 63, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 64, 64, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 65, 65, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 66, 66, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 67, 67, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 68, 68, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 69, 69, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;
	case 6:
		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 20, 20, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 21, 21, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 22, 22, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 23, 23, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 24, 24, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 25, 25, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 26, 26, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 27, 27, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 28, 28, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 29, 29, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;
	case 7:
		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 20, 20, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 21, 21, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 22, 22, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 23, 23, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 24, 24, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 25, 25, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 26, 26, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 27, 27, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 28, 28, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 29, 29, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;
	default:
		mainRender_ = CreateRenderer("HPnumber");
		mainRender_->CreateAnimation("0", "TimerNum", 20, 20, false, 1.0f);
		mainRender_->CreateAnimation("1", "TimerNum", 21, 21, false, 1.0f);
		mainRender_->CreateAnimation("2", "TimerNum", 22, 22, false, 1.0f);
		mainRender_->CreateAnimation("3", "TimerNum", 23, 23, false, 1.0f);
		mainRender_->CreateAnimation("4", "TimerNum", 24, 24, false, 1.0f);
		mainRender_->CreateAnimation("5", "TimerNum", 25, 25, false, 1.0f);
		mainRender_->CreateAnimation("6", "TimerNum", 26, 26, false, 1.0f);
		mainRender_->CreateAnimation("7", "TimerNum", 27, 27, false, 1.0f);
		mainRender_->CreateAnimation("8", "TimerNum", 28, 28, false, 1.0f);
		mainRender_->CreateAnimation("9", "TimerNum", 29, 29, false, 1.0f);
		mainRender_->ChangeAnimation("0");
		break;
	}

	SetRenderOrder(static_cast<int>(RenderOrder::UI1));
	mainRender_->SetCameraEffectOn();
}

void WormHPNumber::Start()
{

}


void WormHPNumber::UpdateBefore()
{

}
void WormHPNumber::Update()
{
	if (true == isWormLinked_)
	{
		if (true == isDigitHundred_)
		{
			SetPos({ parent_->GetPos().x - 10.0f , (parent_->GetPos().y - 32.0f) });
			return;
		}
		if (true == isDigitTen_)
		{
			SetPos({ parent_->GetPos().x - 0.0f , (parent_->GetPos().y - 32.0f) });
			return;
		}
		{
			SetPos({ parent_->GetPos().x + 10.0f , (parent_->GetPos().y - 32.0f) });
			return;
		}
	}
}

void WormHPNumber::UpdateAfter()
{

}

void WormHPNumber::Render()
{
	if (true == isDigitHundred_ && parent_->GetCurHP() < 100) 
	{
		return;
	}

	if (true == isDigitTen_ && parent_->GetCurHP() < 10)
	{
		return;
	}

	if (true == isWormLinked_)
	{
		mainRender_->AnimationUpdate();
	}
}

void WormHPNumber::HPInit()
{
	int defaultHP = GameOptionInfo::WormEnergy;

	if (true == isDigitHundred_)
	{
		if (parent_->GetCurHP() < 100)
		{
			return;
		}
		defaultHP /= 100;
		mainRender_->ChangeAnimation(std::to_string(defaultHP));
		return;
	}
	if (true == isDigitTen_)
	{
		defaultHP /= 10;
		if (20 <= defaultHP)
		{
			defaultHP -= 20;
		}
		else if (10 <= defaultHP)
		{
			defaultHP -= 10;
		}
		mainRender_->ChangeAnimation(std::to_string(defaultHP));
		return;
	}
	{
		defaultHP %= 10;
		mainRender_->ChangeAnimation(std::to_string(defaultHP));
		return;
	}
}

void WormHPNumber::UpdateHP(int _hp)
{
	// 세틀먼트 스테이트의 델타타임 시간동안 숫자가 쫘라락 - 하고 가는 애니메이션 연출을 해 줍니다.
	int parentCurHP = parent_->GetCurHP();

	if (true == isDigitHundred_)
	{
		parentCurHP /= 100;
		mainRender_->ChangeAnimation(std::to_string(parentCurHP));
		return;
	}
	if (true == isDigitTen_)
	{
		parentCurHP /= 10;
		if (20 <= parentCurHP)
		{
			parentCurHP -= 20;
		}
		else if (10 <= parentCurHP)
		{
			parentCurHP -= 10;
		}
		mainRender_->ChangeAnimation(std::to_string(parentCurHP));
		return;
	}
	{
		parentCurHP %= 10;
		mainRender_->ChangeAnimation(std::to_string(parentCurHP));
		return;
	}
}