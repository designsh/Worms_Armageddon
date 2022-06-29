#include "LobbyTeleportinSet.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyTeleportinSet::LobbyTeleportinSet() :
	ImageIndex_(0),
	MouseOver_(false),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyTeleportinSet::~LobbyTeleportinSet() // default destructer 디폴트 소멸자
{

}

LobbyTeleportinSet::LobbyTeleportinSet(LobbyTeleportinSet&& _other) noexcept :
	ImageIndex_(_other.ImageIndex_),
	MouseOver_(_other.MouseOver_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void LobbyTeleportinSet::Start()
{
	mainrenderer_ = CreateRenderer("Lobby_BasicOption_Teleportin0");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 855.f, ImageHarfSize.y + 314.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot(float4(ImageHarfSize.x + 855.f, ImageHarfSize.y + 314.f));
}

void LobbyTeleportinSet::UpdateBefore()
{
	// 마우스 충돌체크
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (false == MouseOver_)
		{
			// MouseOver
			std::string ImageName = "Lobby_BasicOption_Teleportin";
			ImageName += std::to_string(ImageIndex_);
			ImageName += "_MouseOver";
			mainrenderer_->SetImage(ImageName);

			// 마우스 충돌중 On
			MouseOver_ = true;
		}

		// 다음옵션이동
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// 현재 이미지 인덱스 증가
			++ImageIndex_;

			if (1 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// 이미지 전환
			std::string ImageName = "Lobby_BasicOption_Teleportin";
			ImageName += std::to_string(ImageIndex_);
			if (true == MouseOver_)
			{
				ImageName += "_MouseOver";
				MouseOver_ = false;
			}

			mainrenderer_->SetImage(ImageName);

			// 옵션설정 클래스에 전달
			bool Teleportin = GameOptionInfo::Teleportin;
			if (false == Teleportin)
			{
				Teleportin = true;
			}
			else
			{
				Teleportin = false;
			}

			GameOptionInfo::Teleportin = Teleportin;
		}

		// 이전옵션이동
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseRButton"))
		{
			// 현재 이미지 인덱스 감소
			--ImageIndex_;

			if (0 > ImageIndex_)
			{
				ImageIndex_ = 1;
			}

			// 이미지 전환
			std::string ImageName = "Lobby_BasicOption_Teleportin";
			ImageName += std::to_string(ImageIndex_);
			if (true == MouseOver_)
			{
				ImageName += "_MouseOver";
				MouseOver_ = false;
			}

			mainrenderer_->SetImage(ImageName);

			// 옵션설정 클래스에 전달
			bool Teleportin = GameOptionInfo::Teleportin;
			if (false == Teleportin)
			{
				Teleportin = true;
			}
			else
			{
				Teleportin = false;
			}

			GameOptionInfo::Teleportin = Teleportin;
		}
	}
	else
	{
		// MouseOver 해제
		std::string ImageName = "Lobby_BasicOption_Teleportin";
		ImageName += std::to_string(ImageIndex_);
		mainrenderer_->SetImage(ImageName);

		MouseOver_ = false;
	}
}

void LobbyTeleportinSet::Update()
{
}

void LobbyTeleportinSet::UpdateAfter()
{
}

void LobbyTeleportinSet::Render()
{
	mainrenderer_->Render();
}

