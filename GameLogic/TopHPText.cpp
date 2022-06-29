#include "TopHPText.h"
#include "GameOptionInfo.h"

#include "Worm.h"
#include "UIController.h"
#include "WormTopStateUI.h"

#include <EngineEnum.h>
#include <GameEngineRenderer.h>

TopHPText::TopHPText() :
	ParentHPBoxUI_(nullptr),
	WormIndex_(-1),
	PlayerColorIndex_(-1),
	ImageStartIndex_(-1),
	PrevHP_(0),
	CurHP_(0),
	HPUpdateStart_(false),
	HPUpdateEnd_(false),
	UpdateHundredNum(0),
	UpdateTenNum(0),
	UpdateNum(0),
	HundredFlag_(false),
	TenFlag_(false),
	NumFlag_(false),
	HPHundredNumRenderer_(nullptr),
	HPTenNumRenderer_(nullptr),
	HPNumRenderer_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI1));
}

TopHPText::~TopHPText()
{
}

void TopHPText::Start()
{
}

void TopHPText::UpdateBefore()
{
}

void TopHPText::Update()
{
	// 
	if (true == HundredFlag_ && true == TenFlag_ && true == NumFlag_)
	{
		if (nullptr != HPHundredNumRenderer_ && nullptr != HPTenNumRenderer_ && nullptr != HPNumRenderer_)
		{
			HPHundredNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x - 10.f, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
			HPTenNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
			HPNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x + 10.f, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
		}
	}

	// 
	if (false == HundredFlag_ && true == TenFlag_ && true == NumFlag_)
	{
		if (nullptr != HPTenNumRenderer_ && nullptr != HPNumRenderer_)
		{
			HPTenNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x - 5.f, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
			HPNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x + 5.0f, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
		}
	}

	// 
	if (false == HundredFlag_ && false == TenFlag_ && true == NumFlag_)
	{
		if (nullptr != HPNumRenderer_)
		{
			HPNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
		}
	}
}

void TopHPText::UpdateAfter()
{
}

void TopHPText::Render()
{
	if (true == HundredFlag_)
	{
		if (nullptr != HPHundredNumRenderer_)
		{
			HPHundredNumRenderer_->AnimationUpdate();
		}
	}

	if (true == TenFlag_)
	{
		if (nullptr != HPTenNumRenderer_)
		{
			HPTenNumRenderer_->AnimationUpdate();
		}
	}

	if (true == NumFlag_)
	{
		if (nullptr != HPNumRenderer_)
		{
			HPNumRenderer_->AnimationUpdate();
		}
	}
}

void TopHPText::CreateHPText(WormTopStateUI* _Parent, int _WormIndex)
{
	// 부모와 링크
	ParentHPBoxUI_ = _Parent;
	if (nullptr != ParentHPBoxUI_)
	{
		WormIndex_ = ParentHPBoxUI_->GetWormIndex();
		PlayerColorIndex_ = ParentHPBoxUI_->GetPlayerColorIndex();
	}

	// Text의 Color를 셋팅한다.
	SetTextColor();

	// 생성시 플레이어의 체력을 셋팅한다.
	HPTextInit();
}

void TopHPText::SetTextColor()
{
	std::string AnimationName = "TimerNum";
	int ImageIndex = 0;

	std::string CurPlayerName = GameOptionInfo::CurPlayerName[WormIndex_];
	char PlayerIndex = CurPlayerName[0];
	int PlayerNumber = (static_cast<int>(PlayerIndex) - '0');
	PlayerNumber -= 1;
	PlayerColorIndex_ = PlayerNumber;
	switch (PlayerColorIndex_)
	{
		case 0:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageStartIndex_ = 20;
				ImageIndex = i + ImageStartIndex_;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 1:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageStartIndex_ = 30;
				ImageIndex = i + ImageStartIndex_;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 2:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageStartIndex_ = 40;
				ImageIndex = i + ImageStartIndex_;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 3:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageStartIndex_ = 50;
				ImageIndex = i + ImageStartIndex_;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 4:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageStartIndex_ = 70;
				ImageIndex = i + ImageStartIndex_;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 5:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageStartIndex_ = 60;
				ImageIndex = i + ImageStartIndex_;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		default:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageStartIndex_ = 20;
				ImageIndex = i + ImageStartIndex_;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
	}
}

void TopHPText::HPTextInit()
{
	int InitHP = GameOptionInfo::WormEnergy;
	if (0 != InitHP)
	{
		// 각 자릿수의 Number를 찾아낸다.
		int HundredNum = 0;
		int TenNum = 0;
		int Num = 0;
		if (0 != (InitHP /100))
		{
			HundredFlag_ = true;

			HundredNum = InitHP / 100;
			HPHundredNumRenderer_->ChangeAnimation(std::to_string(HundredNum));
		}

		if (0 != (InitHP / 10))
		{
			TenFlag_ = true;

			TenNum = InitHP / 10;
			TenNum = TenNum % 10;
			HPTenNumRenderer_->ChangeAnimation(std::to_string(TenNum));
		}

		if (0 != (InitHP / 1))
		{
			NumFlag_ = true;

			Num = InitHP % 10;
			HPNumRenderer_->ChangeAnimation(std::to_string(Num));
		}

		PrevHP_ = CurHP_ = InitHP;
	}
}

void TopHPText::ChangeHPText()
{
	// 현재 플레이어의 체력을 갱신
	Worm* CurWorm = ParentHPBoxUI_->GetParentWorm();
	if (nullptr != CurWorm)
	{
		// 플레이어가 사망하지않았고 이전 체력과 달라진 경우 갱신
		CurHP_ = CurWorm->GetCurHP();

		if (PrevHP_ == CurHP_)
		{
			return;
		}

		if (PrevHP_ > CurHP_)
		{
			deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

			if (deltaTime_ >= NUMBER_CHANGE_TIME)
			{
				ChangeTextAnimation(PrevHP_);
				deltaTime_ = 0.0f;
				return;
			}
		}
	}
}

void TopHPText::ChangeTextAnimation(int _prevHp)
{
	if (-1 != _prevHp)
	{
		HPHundredNumRenderer_->ChangeAnimation(std::to_string(_prevHp / 100));
		HPTenNumRenderer_->ChangeAnimation(std::to_string((_prevHp / 10) % 10));
		HPNumRenderer_->ChangeAnimation(std::to_string(_prevHp % 10));
		PrevHP_--;
		CheckHPTextZero();
	}
}

void TopHPText::CheckHPTextZero()
{
	if (true == HPHundredNumRenderer_->IsCurAnimationName("0"))
	{
		HundredFlag_ = false;
	}

	if (true == HPTenNumRenderer_->IsCurAnimationName("0") && false == HundredFlag_)
	{
		TenFlag_ = false;
	}

	if (PrevHP_ <= 1 && CurHP_ <= 0)
	{
		HPNumRenderer_->ChangeAnimation("0");
	}

}
