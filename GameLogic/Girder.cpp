#include "Girder.h"

#include <GameEngineCollision.h>
#include <GameEngineRenderer.h>
#include <GameEngineSoundManager.h>
#include <GameEngineInput.h>

#include "PlayLevel.h"

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"
#include "MouseObject.h"
#include "GameController.h"
#include "MapTrain.h"

Girder::Girder()
	: index_(0)
	, mouse_(nullptr)
	, parentWorm_(nullptr)
	, bLeft_(true)
	, soundWhoosh_("GIRDERIMPACT.WAV")

{
	for (size_t i = 0; i < 18; i++)
	{
		mainRender_[i] = nullptr;
		ColRender_[i] = nullptr;
	}
}

Girder::~Girder()
{

}

void Girder::Start()
{
	SetRenderOrder(static_cast<int>(RenderOrder::Weapon));

	mainRender_[0] = CreateRenderer("Grds0");
	mainRender_[1] = CreateRenderer("Grds1");
	mainRender_[2] = CreateRenderer("Grds2");
	mainRender_[3] = CreateRenderer("Grds3");
	mainRender_[4] = CreateRenderer("Grds4");
	mainRender_[5] = CreateRenderer("Grds5");
	mainRender_[6] = CreateRenderer("Grds6");
	mainRender_[7] = CreateRenderer("Grds7");
	mainRender_[8] = CreateRenderer("Grds8");
	mainRender_[9] = CreateRenderer("Grdl0");
	mainRender_[10] = CreateRenderer("Grdl1");
	mainRender_[11] = CreateRenderer("Grdl2");
	mainRender_[12] = CreateRenderer("Grdl3");
	mainRender_[13] = CreateRenderer("Grdl4");
	mainRender_[14] = CreateRenderer("Grdl5");
	mainRender_[15] = CreateRenderer("Grdl6");
	mainRender_[16] = CreateRenderer("Grdl7");
	mainRender_[17] = CreateRenderer("Grdl8");

	ColRender_[0] = CreateRenderer("Grds0b");
	ColRender_[1] = CreateRenderer("Grds1b");
	ColRender_[2] = CreateRenderer("Grds2b");
	ColRender_[3] = CreateRenderer("Grds3b");
	ColRender_[4] = CreateRenderer("Grds4b");
	ColRender_[5] = CreateRenderer("Grds5b");
	ColRender_[6] = CreateRenderer("Grds6b");
	ColRender_[7] = CreateRenderer("Grds7b");
	ColRender_[8] = CreateRenderer("Grds8b");
	ColRender_[9] = CreateRenderer("Grdl0b");
	ColRender_[10] = CreateRenderer("Grdl1b");
	ColRender_[11] = CreateRenderer("Grdl2b");
	ColRender_[12] = CreateRenderer("Grdl3b");
	ColRender_[13] = CreateRenderer("Grdl4b");
	ColRender_[14] = CreateRenderer("Grdl5b");
	ColRender_[15] = CreateRenderer("Grdl6b");
	ColRender_[16] = CreateRenderer("Grdl7b");
	ColRender_[17] = CreateRenderer("Grdl8b");

	if (false == GameEngineInput::GetInst().IsKey("IndexMinus"))
	{
		GameEngineInput::GetInst().CreateKey("IndexMinus", VK_LEFT);
	}

	if (false == GameEngineInput::GetInst().IsKey("IndexPlus"))
	{
		GameEngineInput::GetInst().CreateKey("IndexPlus", VK_RIGHT);
	}

	if (false == GameEngineInput::GetInst().IsKey("BuildGirder"))
	{
		GameEngineInput::GetInst().CreateKey("BuildGirder", VK_LBUTTON);
	}

	mouse_ = (MouseObject*)GetLevel()->FindActor("PlayLevelMouse");
}

void Girder::UpdateBefore()
{
}

void Girder::Update()
{
	SetPos(mouse_->GetPos() + mouse_->GetGameController()->GetCameraPos());

	if (true == GameEngineInput::GetInst().IsDown("IndexMinus"))
	{
		--index_;

		if (index_ == -1)
		{
			index_ = 17;
		}
	}

	if (true == GameEngineInput::GetInst().IsDown("IndexPlus"))
	{
		++index_;

		if (index_ == 18)
		{
			index_ = 0;
		}
	}

	if (true == GameEngineInput::GetInst().IsDown("BuildGirder"))
	{
		GameEngineSoundManager::GetInstance().PlaySoundByName("GIRDERIMPACT.WAV");
		PlayLevel* level = (PlayLevel*)GetLevel();
		level->GetMap()->BuildGirder(pos_ - mainRender_[index_]->GetImageSize() * 0.5f, mainRender_[index_], ColRender_[index_]);
		parentWorm_->SetCurWeapon(eItemList::WEAPON_BAZOOKA);
		Death();
	}

	if (parentWorm_->GetCurrentWeapon() != eItemList::WEAPON_GIRDER)
	{
		Death();
	}
}

void Girder::UpdateAfter()
{
}

void Girder::Render()
{
	mainRender_[index_]->Render();
}

void Girder::Initialize(Worm* _parentWorm, bool _bLeft)
{
	parentWorm_ = _parentWorm;
	bLeft_ = _bLeft;
}
