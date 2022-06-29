#include "LobbySelectMapImage.h"
#include "eCollisionGroup.h"
#include "GlobalValue.h"
#include "GameOptionInfo.h"

#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineCollision.h>
#include <GameEngineRenderer.h>
#include <EngineEnum.h>

LobbySelectMapImage::LobbySelectMapImage() :
	curmapimage_(0),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbySelectMapImage::~LobbySelectMapImage() // default destructer ����Ʈ �Ҹ���
{
}

LobbySelectMapImage::LobbySelectMapImage(LobbySelectMapImage&& _other) noexcept :
	curmapimage_(_other.curmapimage_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{
}

void LobbySelectMapImage::CreateSelMapImageNameList(const std::vector<std::string>& _NameList)
{
	mapimagenamelist_ = _NameList;
}

void LobbySelectMapImage::SetCurMapIndex(int _Index)
{
	curmapimage_ = _Index;
}

void LobbySelectMapImage::Start()
{
	float4 HarfResolution = GameEngineWindow::GetInst().GetSize().halffloat4();

	mainrenderer_ = CreateRenderer("LobbyMap_MapTrain");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x, ImageHarfSize.y));
	mainrenderer_->SetRenderSize(float4(520.f, 160.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize({ 520.f, 160.f });
	maincollision_->SetPivot({ 260.f, 80.f });
}

void LobbySelectMapImage::UpdateBefore()
{
	// �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		// ���콺 �����ʹ�ư üũ
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseRButton"))
		{
			// ���η����� �̹��� ����
			++curmapimage_;
			if (curmapimage_ > mapimagenamelist_.size() - 1)
			{
				curmapimage_ = 0;
			}

			mainrenderer_->SetImage(mapimagenamelist_[curmapimage_]);
			float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
			mainrenderer_->SetPivotPos(float4(ImageHarfSize.x, ImageHarfSize.y));
			mainrenderer_->SetRenderSize(float4(520.f, 160.f));

			// ���������� ���缱�õ� ���̸� ����
			// ��, ���̸��� �Ѱ��ٶ� LobbyMap_ ���ڿ��� ������ ���ڿ��� �ѱ��.
			std::string CurMapName = mapimagenamelist_[curmapimage_];
			CurMapName = CurMapName.substr(9);
			GameOptionInfo::CurPlayMap = CurMapName;

			// ���缱�õ� ��Ÿ���� �浹�� �̸� ����
			// ��, ���̸��� �Ѱ��ٶ� LobbyMap_ ���ڿ��� ������ ���ڿ��� _Ground ���ڿ��� �̾���� �̸� ����
			std::string CurColMapName = mapimagenamelist_[curmapimage_];
			CurColMapName = CurColMapName.substr(9);
			CurColMapName += "_Ground";
			GameOptionInfo::CurPlayColMap = CurColMapName;
		}
	}
}

void LobbySelectMapImage::Update()
{
}

void LobbySelectMapImage::UpdateAfter()
{
}

void LobbySelectMapImage::Render()
{
	mainrenderer_->Render();
}

