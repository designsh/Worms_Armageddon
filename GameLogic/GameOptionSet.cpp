#include "GameOptionSet.h"
#include "eCollisionGroup.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

GameOptionSet::GameOptionSet() :
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

GameOptionSet::~GameOptionSet()
{

}

GameOptionSet::GameOptionSet(GameOptionSet&& _other) noexcept :
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void GameOptionSet::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 ImageHarfSize = float4::ZERO;

	mainrenderer_ = CreateRenderer("Lobby_SetGameOption");
	ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 1135.f, ImageHarfSize.y + 237.f));

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot({ ImageHarfSize.x + 1135.f, ImageHarfSize.y + 237.f });
}

void GameOptionSet::UpdateBefore()
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

void GameOptionSet::Update()
{
	
}

void GameOptionSet::UpdateAfter()
{
}

void GameOptionSet::Render()
{
	mainrenderer_->Render();
}

