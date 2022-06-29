#include "LobbyTernTimeSet.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"
#include <time.h>

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyTernTimeSet::LobbyTernTimeSet() :
	ImageIndex_(3),
	PrevInfinityRandom_(-1),
	MouseOver_(false),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyTernTimeSet::~LobbyTernTimeSet() // default destructer ����Ʈ �Ҹ���
{

}

LobbyTernTimeSet::LobbyTernTimeSet(LobbyTernTimeSet&& _other) noexcept :
	ImageIndex_(_other.ImageIndex_),
	PrevInfinityRandom_(_other.PrevInfinityRandom_),
	MouseOver_(_other.MouseOver_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void LobbyTernTimeSet::Start()
{
	mainrenderer_ = CreateRenderer("Lobby_BasicOption_TernTime3");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 480.f, ImageHarfSize.y + 314.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot(float4(ImageHarfSize.x + 480.f, ImageHarfSize.y + 314.f));
}

void LobbyTernTimeSet::UpdateBefore()
{
	// ���콺 �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (false == MouseOver_)
		{
			// MouseOver
			std::string ImageName = "Lobby_BasicOption_TernTime";
			ImageName += std::to_string(ImageIndex_);
			ImageName += "_MouseOver";
			mainrenderer_->SetImage(ImageName);

			// ���콺 �浹�� On
			MouseOver_ = true;
		}

		// �����ɼ��̵�
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// ���� �̹��� �ε��� ����
			++ImageIndex_;

			if (6 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_TernTime";
			ImageName += std::to_string(ImageIndex_);
			if (true == MouseOver_)
			{
				ImageName += "_MouseOver";
				MouseOver_ = false;
			}

			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int TernTime = static_cast<int>(GameOptionInfo::TernTime);
			if (3 >= ImageIndex_)
			{
				// ������ ���Ѵ� �ɼ��ΰ��� �����Ͽ� �̸� ���Ѵ�
				if (PrevInfinityRandom_ == TernTime)
				{
					TernTime = 15;
				}

				TernTime = TernTime + (ImageIndex_ * 5);
			}
			else if(5 >= ImageIndex_)
			{
				TernTime = TernTime + ((ImageIndex_ - 3) * 5) + ((ImageIndex_ - 3) * 10);
			}
			else
			{
				// ���Ѵ�(infinity) ���� �� 20~100������ ���������� ����
				srand((unsigned int)time(0));
				PrevInfinityRandom_ = rand() % 100 + 20;
				TernTime = PrevInfinityRandom_;
			}

			GameOptionInfo::TernTime = static_cast<float>(TernTime);
		}

		// �����ɼ��̵�
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseRButton"))
		{
			// ���� �̹��� �ε��� ����
			--ImageIndex_;

			if (-1 == ImageIndex_)
			{
				ImageIndex_ = 6;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_TernTime";
			ImageName += std::to_string(ImageIndex_);
			if (true == MouseOver_)
			{
				ImageName += "_MouseOver";
				MouseOver_ = false;
			}

			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int TernTime = static_cast<int>(GameOptionInfo::TernTime);
			if (6 <= ImageIndex_)
			{
				// ImageIndex�� 0�̸� ���� ��Ÿ�� �ɼ��� ���Ѵ�(infinity)�̹Ƿ� �������
				srand((unsigned int)time(0));
				PrevInfinityRandom_ = (rand() % 100) + 20;
				TernTime = PrevInfinityRandom_;
			}
			else if (4 <= ImageIndex_) // 30
			{
				// ������ ���Ѵ� �ɼ��ΰ��� �����Ͽ� �̸� ���Ѵ�
				if (PrevInfinityRandom_ == TernTime)
				{
					TernTime = 90;
				}
				else
				{
					TernTime = TernTime - (5 - ImageIndex_) * 30;
				}
			}
			else if (2 <= ImageIndex_) // 15
			{
				TernTime = TernTime - 15;
			}
			else if(0 <= ImageIndex_) // 10
			{
				TernTime = TernTime - ((ImageIndex_ + 1) * 5);
			}

			GameOptionInfo::TernTime = static_cast<float>(TernTime);
		}
	}
	else
	{
	// MouseOver ����
	std::string ImageName = "Lobby_BasicOption_TernTime";
	ImageName += std::to_string(ImageIndex_);
	mainrenderer_->SetImage(ImageName);

	MouseOver_ = false;
	}
}

void LobbyTernTimeSet::Update()
{

}

void LobbyTernTimeSet::UpdateAfter()
{
}

void LobbyTernTimeSet::Render()
{
	mainrenderer_->Render();
}

