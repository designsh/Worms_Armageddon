#include "EndingFade.h"
#include "EndingText.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include <GameEngineTime.h>

EndingFade::EndingFade() :
	alpha_(0.0f),
	castalpha_(0),
	fadestop_(false),
	fadeBlackSpriteRender_(nullptr),
	EndingTimer_{},
	CreditTextListCnt_(0),
	mainsound_("Worms_TitleScreen.mp3")
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround2));
}

EndingFade::~EndingFade() // default destructer 디폴트 소멸자
{
}

void EndingFade::Start()
{	
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 ImageHarf = float4::ZERO;

	// Fade In/Out 렌더러 생성
	fadeBlackSpriteRender_ = CreateRenderer("Fade_Black");
	ImageHarf = fadeBlackSpriteRender_->GetImageSize().halffloat4();
	fadeBlackSpriteRender_->SetPivotPos(ImageHarf);
	fadeBlackSpriteRender_->Off();

	// 엔딩 FadeInOut
	EndingTimer_.CreateTimeEvent(10.f, this, nullptr, &EndingFade::EndingFadeStart, &EndingFade::EndingFadeStay, &EndingFade::EndingFadeEnd);
}

void EndingFade::UpdateBefore()
{
}

void EndingFade::Update()
{
	EndingTimer_.Update();
}

void EndingFade::UpdateAfter()
{
}

void EndingFade::Render()
{
	if (true == fadeBlackSpriteRender_->IsOn())
	{
		fadeBlackSpriteRender_->Render();
	}
}


void EndingFade::EndingFadeStart()
{
	fadeBlackSpriteRender_->On();

	alpha_ = 2.55f;
	castalpha_ = 255;
	fadestop_ = false;

	fadeBlackSpriteRender_->SetAlpha(castalpha_);

	// 배경음악 실행
	mainsound_.Play();
	mainsound_.SetVolume(0.2f);
}

void EndingFade::EndingFadeStay()
{
	alpha_ -= GameEngineTime::GetInst().GetDeltaTime() * 0.09f;

	if (0.0f >= alpha_)
	{
		alpha_ = 0.0f;
		castalpha_ = 0;
		fadestop_ = true;
		fadeBlackSpriteRender_->Off();
	}
	else
	{
		castalpha_ = static_cast<unsigned char>(alpha_ * 100.f);
	}

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

bool EndingFade::EndingFadeEnd()
{
	// 현재 크레딧 텍스트 무브 시작
	for (int i = 0; i < CreditTextListCnt_; ++i)
	{
		CreditTextList_[i]->MoveStart();
	}

	return fadestop_;
}

void EndingFade::PushCreditText(EndingText* _EndingText)
{
	CreditTextList_.push_back(_EndingText);
	++CreditTextListCnt_;
}
