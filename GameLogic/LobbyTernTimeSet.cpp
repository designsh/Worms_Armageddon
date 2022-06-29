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

LobbyTernTimeSet::~LobbyTernTimeSet() // default destructer 디폴트 소멸자
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
	// 마우스 충돌체크
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

			// 마우스 충돌중 On
			MouseOver_ = true;
		}

		// 다음옵션이동
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// 현재 이미지 인덱스 증가
			++ImageIndex_;

			if (6 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// 이미지 전환
			std::string ImageName = "Lobby_BasicOption_TernTime";
			ImageName += std::to_string(ImageIndex_);
			if (true == MouseOver_)
			{
				ImageName += "_MouseOver";
				MouseOver_ = false;
			}

			mainrenderer_->SetImage(ImageName);

			// 옵션설정 클래스에 전달
			int TernTime = static_cast<int>(GameOptionInfo::TernTime);
			if (3 >= ImageIndex_)
			{
				// 이전에 무한대 옵션인것을 감안하여 미리 더한다
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
				// 무한대(infinity) 셋팅 시 20~100사이의 랜덤값으로 지정
				srand((unsigned int)time(0));
				PrevInfinityRandom_ = rand() % 100 + 20;
				TernTime = PrevInfinityRandom_;
			}

			GameOptionInfo::TernTime = static_cast<float>(TernTime);
		}

		// 이전옵션이동
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseRButton"))
		{
			// 현재 이미지 인덱스 감소
			--ImageIndex_;

			if (-1 == ImageIndex_)
			{
				ImageIndex_ = 6;
			}

			// 이미지 전환
			std::string ImageName = "Lobby_BasicOption_TernTime";
			ImageName += std::to_string(ImageIndex_);
			if (true == MouseOver_)
			{
				ImageName += "_MouseOver";
				MouseOver_ = false;
			}

			mainrenderer_->SetImage(ImageName);

			// 옵션설정 클래스에 전달
			int TernTime = static_cast<int>(GameOptionInfo::TernTime);
			if (6 <= ImageIndex_)
			{
				// ImageIndex가 0이면 다음 턴타임 옵션은 무한대(infinity)이므로 랜덤계산
				srand((unsigned int)time(0));
				PrevInfinityRandom_ = (rand() % 100) + 20;
				TernTime = PrevInfinityRandom_;
			}
			else if (4 <= ImageIndex_) // 30
			{
				// 이전에 무한대 옵션인것을 감안하여 미리 더한다
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
	// MouseOver 해제
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

