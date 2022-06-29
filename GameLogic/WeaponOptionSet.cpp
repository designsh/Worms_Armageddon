#include "WeaponOptionSet.h"
#include "eCollisionGroup.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

WeaponOptionSet::WeaponOptionSet() :
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

WeaponOptionSet::~WeaponOptionSet() // default destructer 디폴트 소멸자
{

}

WeaponOptionSet::WeaponOptionSet(WeaponOptionSet&& _other) noexcept :
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void WeaponOptionSet::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 ImageHarfSize = float4::ZERO;

	mainrenderer_ = CreateRenderer("Lobby_SetWeaponOption");
	ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 1135.f, ImageHarfSize.y + 315.f));

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot({ ImageHarfSize.x + 1135.f, ImageHarfSize.y + 315.f });
}

void WeaponOptionSet::UpdateBefore()
{
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// 현재 구현안함
			int a = 0;
		}
	}
}

void WeaponOptionSet::Update()
{
}

void WeaponOptionSet::UpdateAfter()
{
}

void WeaponOptionSet::Render()
{
	mainrenderer_->Render();
}

