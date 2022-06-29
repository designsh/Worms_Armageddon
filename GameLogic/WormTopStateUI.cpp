#include "WormTopStateUI.h"
#include "GameOptionInfo.h"

#include "Worm.h"
#include "UIController.h"
#include "TopHPText.h"
#include "BottomStateUI.h"

#include <EngineEnum.h>
#include <GameEngineRenderer.h>
#include <GameEngineLevel.h>

WormTopStateUI::WormTopStateUI() :
	ParentWorm_(nullptr),
	ParentUI_(nullptr),
	WormLinked_(false),
	WormIndex_(-1),
	PlayerColorIndex_(-1),
	NameRenderer_(nullptr),
	ArrowRenderer_(nullptr),
	HPBoxRenderer_(nullptr),
	HPText_(nullptr),
	isHPTextNeedChange_(false)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

WormTopStateUI::~WormTopStateUI()
{
}

Worm* WormTopStateUI::GetParentWorm() const
{
	return ParentWorm_;
}

int WormTopStateUI::GetWormIndex() const
{
	return WormIndex_;
}

int WormTopStateUI::GetPlayerColorIndex() const
{
	return PlayerColorIndex_;
}

void WormTopStateUI::Start()
{
	// 플레이어 닉네임
	NameRenderer_ = CreateRenderer("WormName1");
	NameRenderer_->SetCameraEffectOn();
}

void WormTopStateUI::UpdateBefore()
{

}

void WormTopStateUI::Update()
{
	// 플레이어 위치에 따라서 이동
	if (true == WormLinked_)
	{
		UpdateTextAnimation();

		if (nullptr != NameRenderer_)
		{
			NameRenderer_->SetPivotPos(float4(ParentWorm_->GetPos().x, ParentWorm_->GetPos().y - 50.f));
		}

		if (nullptr != HPBoxRenderer_)
		{
			HPBoxRenderer_->SetPivotPos(float4(ParentWorm_->GetPos().x, ParentWorm_->GetPos().y - 32.f));
		}

		if (nullptr != ArrowRenderer_)
		{
			if (true == ParentWorm_->isFocused())
			{
				ArrowRenderer_->SetPivotPos(float4(ParentWorm_->GetPos().x, ParentWorm_->GetPos().y - 90.0f));
			}

			if (false == ParentWorm_->isFocused())
			{
				ArrowRenderer_->SetPivotMove(float4::UP * 600.0f * GameEngineTime::GetInst().GetDeltaTime());
			}
		}
	}
}

void WormTopStateUI::UpdateAfter()
{
}

void WormTopStateUI::Render()
{
	if (nullptr != NameRenderer_)
	{
		NameRenderer_->Render();
	}

	if (nullptr != HPBoxRenderer_)
	{
		HPBoxRenderer_->Render();
	}

	if (nullptr != ArrowRenderer_)
	{
		ArrowRenderer_->AnimationUpdate();
	}
}

void WormTopStateUI::SetParentWorm(Worm* _Parent)
{
	ParentWorm_ = _Parent;

	// 링크 완료
	WormLinked_ = true;
}

void WormTopStateUI::SetParentUIController(UIController* _ParentUI)
{
	ParentUI_ = _ParentUI;
}

void WormTopStateUI::GameStartInit(int _WormIndex)
{	
	// 현재 생성된 하단바의 주인이 누구인지 저장
	WormIndex_ = _WormIndex;

	// 렌더러를 셋팅한다.
	SettingRenderer();

	// 렌더러의 위치를 셋팅한다.
	SettingRendererPos();
}

void WormTopStateUI::SettingRenderer()
{
	// 플레이어 닉네임 렌더러 세팅
	SetPlayerName();

	// 플레이어 화살표 렌더러 세팅
	SetPlayerArrow();

	// 플레이어 HP Box 렌더러 세팅
	SetHPBox();
}

void WormTopStateUI::SetPlayerName()
{
	std::string CurPlayerName = GameOptionInfo::CurPlayerName[WormIndex_];
	char PlayerIndex = CurPlayerName[0];
	int PlayerNumber = (static_cast<int>(PlayerIndex) - '0');
	PlayerNumber -= 1;
	PlayerColorIndex_ = PlayerNumber;
	switch (PlayerColorIndex_)
	{
		case 0:
		{
			NameRenderer_ = CreateRenderer("WormName1");
			break;
		}
		case 1:
		{
			NameRenderer_ = CreateRenderer("WormName2");
			break;
		}
		case 2:
		{
			NameRenderer_ = CreateRenderer("WormName3");
			break;
		}
		case 3:
		{
			NameRenderer_ = CreateRenderer("WormName4");
			break;
		}
		case 4:
		{
			NameRenderer_ = CreateRenderer("WormName5");
			break;
		}
		case 5:
		{
			NameRenderer_ = CreateRenderer("WormName6");
			break;
		}
		default:
		{
			NameRenderer_ = CreateRenderer("WormName1");
			break;
		}
	}
}

void WormTopStateUI::SetPlayerArrow()
{
	std::string CurPlayerName = GameOptionInfo::CurPlayerName[WormIndex_];
	char PlayerIndex = CurPlayerName[0];
	int PlayerNumber = (static_cast<int>(PlayerIndex) - '0');
	PlayerNumber -= 1;
	PlayerColorIndex_ = PlayerNumber;
	switch (PlayerColorIndex_)
	{
		case 0:
		{
			ArrowRenderer_ = CreateRenderer("arrowdnr");
			ArrowRenderer_->CreateAnimation("arrowdnr", "arrowdnr", 0, 29, true, 0.022f);
			ArrowRenderer_->ChangeAnimation("arrowdnr");
			break;
		}
		case 1:
		{
			ArrowRenderer_ = CreateRenderer("arrowdnb");
			ArrowRenderer_->CreateAnimation("arrowdnb", "arrowdnb", 0, 29, true, 0.022f);
			ArrowRenderer_->ChangeAnimation("arrowdnb");
			break;
		}
		case 2:
		{
			ArrowRenderer_ = CreateRenderer("arrowdng");
			ArrowRenderer_->CreateAnimation("arrowdng", "arrowdng", 0, 29, true, 0.022f);
			ArrowRenderer_->ChangeAnimation("arrowdng");
			break;
		}
		case 3:
		{
			ArrowRenderer_ = CreateRenderer("arrowdny");
			ArrowRenderer_->CreateAnimation("arrowdny", "arrowdny", 0, 29, true, 0.022f);
			ArrowRenderer_->ChangeAnimation("arrowdny");
			break;
		}
		case 4:
		{
			ArrowRenderer_ = CreateRenderer("arrowdnp");
			ArrowRenderer_->CreateAnimation("arrowdnp", "arrowdnp", 0, 29, true, 0.022f);
			ArrowRenderer_->ChangeAnimation("arrowdnp");
			break;
		}
		case 5:
		{
			ArrowRenderer_ = CreateRenderer("arrowdnc");
			ArrowRenderer_->CreateAnimation("arrowdnc", "arrowdnc", 0, 29, true, 0.022f);
			ArrowRenderer_->ChangeAnimation("arrowdnc");
			break;
		}
		default:
		{
			ArrowRenderer_ = CreateRenderer("arrowdnr");
			ArrowRenderer_->CreateAnimation("arrowdnr", "arrowdnr", 0, 29, true, 0.022f);
			ArrowRenderer_->ChangeAnimation("arrowdnr");
			break;
		}
	}

	ArrowRenderer_->SetPivotPos(float4(ParentWorm_->GetPos().x, ParentWorm_->GetPos().y - 90.0f));
}

void WormTopStateUI::SetHPBox()
{
	// 플레이어 HP Box
	HPBoxRenderer_ = CreateRenderer("WormHP");
	HPBoxRenderer_->SetCameraEffectOn();

	// HP Box가 만들어진 후 HP Text 액터를 만들어낸다.
	CreateHPText();
}

void WormTopStateUI::CreateHPText()
{
	// TopHPText의 생성 호출(CreateHPText())
	HPText_ = GetLevel()->CreateActor<TopHPText>();
	if (nullptr != HPText_)
	{
		HPText_->CreateHPText(this, WormIndex_);
	}
}

void WormTopStateUI::SettingRendererPos()
{
	// 플레이어 닉네임 렌더러 위치 세팅
	SetPlayerNamePos();
}

void WormTopStateUI::SetPlayerNamePos()
{
	// 초기 위치 자신이 속한 Worm의 상단에 위치 시킨다.
	NameRenderer_->SetPivotPos(float4(ParentWorm_->GetPos().x, ParentWorm_->GetPos().y - 50.f));
}


void WormTopStateUI::CurWormHPTextDeath()
{
	HPText_->Death();
}
void WormTopStateUI::UpdateTextAnimation()
{
	HPText_->ChangeHPText();
	return;
}