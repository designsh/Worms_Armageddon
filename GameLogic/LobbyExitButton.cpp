#include "LobbyExitButton.h"
#include "ChattingInput.h"

#include <EngineEnum.h>
#include "eCollisionGroup.h"
#include <GameEngineInput.h>
#include <GameEngineWindow.h>
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>
#include <GameEngineLevelManager.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyExitButton::LobbyExitButton():
	mainrenderer_(nullptr),
	maincollision_(nullptr),
	mouseover_(false)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyExitButton::~LobbyExitButton()
{

}

LobbyExitButton::LobbyExitButton(LobbyExitButton&& _other) noexcept :
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_),
	mouseover_(_other.mouseover_)
{
}

void LobbyExitButton::Start()
{
	float4 ImageHarfSize = float4::ZERO;

	// 버튼 렌더러 생성
	mainrenderer_ = CreateRenderer("Lobby_ButtonNormal");
	ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 1020.f, ImageHarfSize.y + 688.f));
	mainrenderer_->SetRenderSize(float4(250.f, 32.f));
	mainrenderer_->SetCameraEffectOff();

	// 버튼 충돌체 생성
	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(float4(250.f, 32.f));
	maincollision_->SetPivot(float4(125.f + 1020.f, 16.f + 688.f));

	// 버튼 Text 생성(임시)
	ExitText_ = "Exit";
}

void LobbyExitButton::UpdateBefore()
{
	// 마우스와 충돌체크
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		// 최초 충돌시에만 이미지 전환
		if (false == mouseover_)
		{
			// Flag On
			mouseover_ = true;

			// Button Box Image Change
			mainrenderer_->SetImage("Lobby_ButtonMouseOn");
			float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
			mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 1020.f, ImageHarfSize.y + 688.f));
			mainrenderer_->SetRenderSize(float4(250.f, 32.f));

			// Button Text Image Change

		}
	}
	else
	{
		mouseover_ = false;
	}
}

void LobbyExitButton::Update()
{
	// 마우스와 버튼이 충돌중이라면
	if (true == mouseover_)
	{
		// 마우스와 충돌중에 클릭되었을때
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// 메뉴선택화면 이동
			GameEngineLevelManager::GetInst().ChangeLevel("MenuSelectLevel", true);
		}
	}
	else
	{
		mainrenderer_->SetImage("Lobby_ButtonNormal");
		float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
		mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 1020.f, ImageHarfSize.y + 688.f));
		mainrenderer_->SetRenderSize(float4(250.f, 32.f));
	}
}

void LobbyExitButton::UpdateAfter()
{
}

void LobbyExitButton::Render()
{
	if (true == mainrenderer_->IsOn())
	{
		mainrenderer_->Render();
	}

	// 임시 추후 이미지로 변경
	if (!ExitText_.empty())
	{
		TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), 1130, 696, ExitText_.c_str(), lstrlen(ExitText_.c_str()));
	}
}

