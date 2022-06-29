#include "LobbyWinsreQuiredSet.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyWinsreQuiredSet::LobbyWinsreQuiredSet() :
	ImageIndex_(2),
	MouseOver_(false),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyWinsreQuiredSet::~LobbyWinsreQuiredSet() // default destructer ����Ʈ �Ҹ���
{

}

LobbyWinsreQuiredSet::LobbyWinsreQuiredSet(LobbyWinsreQuiredSet&& _other) noexcept :
	ImageIndex_(_other.ImageIndex_),
	MouseOver_(_other.MouseOver_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{
}

void LobbyWinsreQuiredSet::Start()
{
	mainrenderer_ = CreateRenderer("Lobby_BasicOption_WinSrequired2");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 630.f, ImageHarfSize.y + 314.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot(float4(ImageHarfSize.x + 630.f, ImageHarfSize.y + 314.f));
}

void LobbyWinsreQuiredSet::UpdateBefore()
{
	// ���콺 �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (false == MouseOver_)
		{
			// MouseOver
			std::string ImageName = "Lobby_BasicOption_WinSrequired";
			ImageName += std::to_string(ImageIndex_);
			ImageName += "_MouseOver";
			mainrenderer_->SetImage(ImageName);

			// ���콺 �浹�� On
			MouseOver_ = true;
		}

		// ���� �ɼ��̵�
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// ���� �̹��� �ε��� ����
			++ImageIndex_;

			if (6 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_WinSrequired";
			ImageName += std::to_string(ImageIndex_);
			if (true == MouseOver_)
			{
				ImageName += "_MouseOver";
				MouseOver_ = false;
			}

			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int WinSreuired = GameOptionInfo::WinSreuired;
			if (9 <= WinSreuired)
			{
				WinSreuired = 0;
			}

			if (3 >= ImageIndex_)
			{
				WinSreuired += 1;
			}
			else
			{
				WinSreuired += 2;
			}

			GameOptionInfo::WinSreuired = WinSreuired;
		}

		// �����ɼ��̵�
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseRButton"))
		{
			// ���� �̹��� �ε��� ����
			--ImageIndex_;

			if (0 > ImageIndex_)
			{
				ImageIndex_ = 6;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_WinSrequired";
			ImageName += std::to_string(ImageIndex_);
			if (true == MouseOver_)
			{
				ImageName += "_MouseOver";
				MouseOver_ = false;
			}

			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int WinSreuired = GameOptionInfo::WinSreuired;
			if (3 <= ImageIndex_)
			{
				if (6 == ImageIndex_)
				{
					WinSreuired = 9;
				}
				else
				{
					WinSreuired -= 2;
				}
			}
			else if (0 <= ImageIndex_)
			{
				WinSreuired -= 1;
			}
			GameOptionInfo::WinSreuired = WinSreuired;
		}
	}
	else
	{
		// MouseOver ����
		std::string ImageName = "Lobby_BasicOption_WinSrequired";
		ImageName += std::to_string(ImageIndex_);
		mainrenderer_->SetImage(ImageName);

		MouseOver_ = false;
	}
}

void LobbyWinsreQuiredSet::Update()
{
}

void LobbyWinsreQuiredSet::UpdateAfter()
{
}

void LobbyWinsreQuiredSet::Render()
{
	mainrenderer_->Render();
}

