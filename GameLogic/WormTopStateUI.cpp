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
	// �÷��̾� �г���
	NameRenderer_ = CreateRenderer("WormName1");
	NameRenderer_->SetCameraEffectOn();
}

void WormTopStateUI::UpdateBefore()
{

}

void WormTopStateUI::Update()
{
	// �÷��̾� ��ġ�� ���� �̵�
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

	// ��ũ �Ϸ�
	WormLinked_ = true;
}

void WormTopStateUI::SetParentUIController(UIController* _ParentUI)
{
	ParentUI_ = _ParentUI;
}

void WormTopStateUI::GameStartInit(int _WormIndex)
{	
	// ���� ������ �ϴܹ��� ������ �������� ����
	WormIndex_ = _WormIndex;

	// �������� �����Ѵ�.
	SettingRenderer();

	// �������� ��ġ�� �����Ѵ�.
	SettingRendererPos();
}

void WormTopStateUI::SettingRenderer()
{
	// �÷��̾� �г��� ������ ����
	SetPlayerName();

	// �÷��̾� ȭ��ǥ ������ ����
	SetPlayerArrow();

	// �÷��̾� HP Box ������ ����
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
	// �÷��̾� HP Box
	HPBoxRenderer_ = CreateRenderer("WormHP");
	HPBoxRenderer_->SetCameraEffectOn();

	// HP Box�� ������� �� HP Text ���͸� ������.
	CreateHPText();
}

void WormTopStateUI::CreateHPText()
{
	// TopHPText�� ���� ȣ��(CreateHPText())
	HPText_ = GetLevel()->CreateActor<TopHPText>();
	if (nullptr != HPText_)
	{
		HPText_->CreateHPText(this, WormIndex_);
	}
}

void WormTopStateUI::SettingRendererPos()
{
	// �÷��̾� �г��� ������ ��ġ ����
	SetPlayerNamePos();
}

void WormTopStateUI::SetPlayerNamePos()
{
	// �ʱ� ��ġ �ڽ��� ���� Worm�� ��ܿ� ��ġ ��Ų��.
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