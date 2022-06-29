#include "LobbyImage.h"
#include "eCollisionGroup.h"
#include "LobbyHost.h"

#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyImage::LobbyImage() :
	hostready_(true),
	mouseover_(false),
	backdropSpriteRender_(nullptr),
	hostboxSpriteRender_(nullptr),
	hostreadySpriteRender_(nullptr),
	hostreadyCollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround));
}

LobbyImage::~LobbyImage() // default destructer 디폴트 소멸자
{
	LobbyHost::SetCurHostReady(false);
}

LobbyImage::LobbyImage(LobbyImage&& _other) noexcept :
	hostready_(_other.hostready_),
	mouseover_(_other.mouseover_),
	backdropSpriteRender_(_other.backdropSpriteRender_),
	hostboxSpriteRender_(_other.hostboxSpriteRender_),
	hostreadySpriteRender_(_other.hostreadySpriteRender_),
	hostreadyCollision_(_other.hostreadyCollision_)
{
}

void LobbyImage::Start()
{
	float4 Resoultion = GameEngineWindow::GetInst().GetSize();

	// 배경
	backdropSpriteRender_ = CreateRenderer("Lobby_Backdrop");
	backdropSpriteRender_->SetRenderSize(Resoultion);
	backdropSpriteRender_->SetPivotPos({ 16.f, 250.f });
	backdropSpriteRender_->SetCameraEffectOff();

	// Host Display Box
	hostboxSpriteRender_ = CreateRenderer("Lobby_HostBox");
	float4 ImageHarfSize = hostboxSpriteRender_->GetImageSize().halffloat4();
	hostboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 10.f));
	hostboxSpriteRender_->SetRenderSize(float4(200.f, 210.f));
	hostboxSpriteRender_->SetCameraEffectOff();

	// Host Ready Button Image
	hostreadySpriteRender_ = CreateRenderer("Lobby_HostReadyOn");
	ImageHarfSize = hostreadySpriteRender_->GetImageSize().halffloat4();
	hostreadySpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 230.f));
	hostreadySpriteRender_->SetRenderSize(float4(200.f, 150.f));
	hostreadySpriteRender_->SetCameraEffectOff();

	hostreadyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	hostreadyCollision_->SetSize(float4(200.f, 150.f));
	hostreadyCollision_->SetPivot(float4(100.f + 10.f, 75.f + 250.f));

	// 키생성
	if (false == GameEngineInput::GetInst().IsKey("Host_Ready"))
	{
		GameEngineInput::GetInst().CreateKey("Host_Ready", VK_LBUTTON);
	}
}

void LobbyImage::UpdateBefore()
{
	// Host Ready
	GameEngineCollision* ColUI = hostreadyCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (false == mouseover_)
		{
			// 마우스오버 이미지로 변경
			std::string ImageName = "";
			if (true == hostready_)
			{
				ImageName = "Lobby_HostReadyOn";
			}
			else
			{
				ImageName = "Lobby_HostReadyOff";
			}

			ImageName += "_MouseOver";

			hostreadySpriteRender_->SetImage(ImageName);
			float4 ImageHarfSize = hostreadySpriteRender_->GetImageSize().halffloat4();
			hostreadySpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 230.f));
			hostreadySpriteRender_->SetRenderSize(float4(200.f, 150.f));

			// MouseOver Flag On
			mouseover_ = true;
		}

		if (true == GameEngineInput::GetInst().IsDown("Host_Ready"))
		{
			if (true == hostready_)
			{
				// 마우스오버 이미지로 변경
				std::string ImageName = "Lobby_HostReadyOff";
				if (true == mouseover_)
				{
					ImageName += "_MouseOver";
					mouseover_ = false;
				}

				hostreadySpriteRender_->SetImage(ImageName);
				float4 ImageHarfSize = hostreadySpriteRender_->GetImageSize().halffloat4();
				hostreadySpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 230.f));
				hostreadySpriteRender_->SetRenderSize(float4(200.f, 150.f));
				hostready_ = false;

				// 현재 호스트에게 전달
				LobbyHost::SetCurHostReady(hostready_);
			}
			else
			{
				std::string ImageName = "Lobby_HostReadyOn";
				if (true == mouseover_)
				{
					ImageName += "_MouseOver";
					mouseover_ = false;
				}

				hostreadySpriteRender_->SetImage(ImageName);

				hostreadySpriteRender_->SetImage("Lobby_HostReadyOn");
				float4 ImageHarfSize = hostreadySpriteRender_->GetImageSize().halffloat4();
				hostreadySpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 230.f));
				hostreadySpriteRender_->SetRenderSize(float4(200.f, 150.f));
				hostready_ = true;

				// 현재 호스트에게 전달
				LobbyHost::SetCurHostReady(hostready_);
			}
		}
	}
	else
	{
		// 마우스일반 이미지로 변경
		std::string ImageName = "";
		if (true == hostready_)
		{
			ImageName = "Lobby_HostReadyOn";
		}
		else
		{
			ImageName = "Lobby_HostReadyOff";
		}

		hostreadySpriteRender_->SetImage(ImageName);
		float4 ImageHarfSize = hostreadySpriteRender_->GetImageSize().halffloat4();
		hostreadySpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 230.f));
		hostreadySpriteRender_->SetRenderSize(float4(200.f, 150.f));

		// MouseOver Flag On
		mouseover_ = false;
	}

	// Player Select

	// Game Option Select

}

void LobbyImage::Update()
{
}

void LobbyImage::UpdateAfter()
{
}


void LobbyImage::Render()
{
	// 배경
	backdropSpriteRender_->Render();

	// 그밖 박스
	hostboxSpriteRender_->Render();

	// Host Ready Button
	hostreadySpriteRender_->Render();
}
