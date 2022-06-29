#include "EndingText.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include <GameEngineTime.h>

EndingText::EndingText() :
	TextRendererSize_(0),
	Text_{},
	TextSize_(-1),
	TextStartPos_(float4::ZERO),
	TextScale_(float4::ZERO),
	Move_(false),
	MoveSpeed_(50.f)
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround1));
}

EndingText::~EndingText()
{
}

void EndingText::Start()
{
}

void EndingText::UpdateBefore()
{
}

void EndingText::Update()
{
	if (true == Move_)
	{
		// 이동 시작
		SetMove(float4::UP * GameEngineTime::GetInst().GetDeltaTime() * MoveSpeed_);
	}
}

void EndingText::UpdateAfter()
{
}

void EndingText::Render()
{
	if (0 != TextRendererSize_)
	{
		for (int i = 0; i < TextRendererSize_; ++i)
		{
			if (nullptr != TextRenderer_[i])
			{
				TextRenderer_[i]->AnimationUpdate();
			}
		}
	}
}

void EndingText::EndingTextInit(const std::string& _Text, const float4& _Pos)
{
	Text_ = _Text;
	TextSize_ = static_cast<int>(Text_.size());
	TextStartPos_ = _Pos;

	// 대문자로 변환
	std::transform(Text_.begin(), Text_.end(), Text_.begin(), std::toupper);

	int CurIndex = 0;
	bool Blank = false;
	for (int i = 0; i < TextSize_; ++i)
	{
		CurIndex = i;

		// 렌더러 생성 및 위치 지정
		char ChkChar = Text_[i];
		std::string AniName = "";
		AniName.push_back(ChkChar);

		if (' ' == ChkChar && false == Blank)
		{
			Blank = true;
		}

		GameEngineRenderer* NewRender = CreateRenderer("Ending_Alphabet");
		NewRender->CreateAnimation("A", "Ending_Alphabet", 0, 0, false, 1.0f);
		NewRender->CreateAnimation("B", "Ending_Alphabet", 1, 1, false, 1.0f);
		NewRender->CreateAnimation("C", "Ending_Alphabet", 2, 2, false, 1.0f);
		NewRender->CreateAnimation("D", "Ending_Alphabet", 3, 3, false, 1.0f);
		NewRender->CreateAnimation("E", "Ending_Alphabet", 4, 4, false, 1.0f);
		NewRender->CreateAnimation("F", "Ending_Alphabet", 5, 5, false, 1.0f);
		NewRender->CreateAnimation("G", "Ending_Alphabet", 6, 6, false, 1.0f);
		NewRender->CreateAnimation("H", "Ending_Alphabet", 7, 7, false, 1.0f);
		NewRender->CreateAnimation("I", "Ending_Alphabet", 8, 8, false, 1.0f);
		NewRender->CreateAnimation("J", "Ending_Alphabet", 9, 9, false, 1.0f);
		NewRender->CreateAnimation("K", "Ending_Alphabet", 10, 10, false, 1.0f);
		NewRender->CreateAnimation("L", "Ending_Alphabet", 11, 11, false, 1.0f);
		NewRender->CreateAnimation("M", "Ending_Alphabet", 12, 12, false, 1.0f);
		NewRender->CreateAnimation("N", "Ending_Alphabet", 13, 13, false, 1.0f);
		NewRender->CreateAnimation("O", "Ending_Alphabet", 14, 14, false, 1.0f);
		NewRender->CreateAnimation("P", "Ending_Alphabet", 15, 15, false, 1.0f);
		NewRender->CreateAnimation("Q", "Ending_Alphabet", 16, 16, false, 1.0f);
		NewRender->CreateAnimation("R", "Ending_Alphabet", 17, 17, false, 1.0f);
		NewRender->CreateAnimation("S", "Ending_Alphabet", 18, 18, false, 1.0f);
		NewRender->CreateAnimation("T", "Ending_Alphabet", 19, 19, false, 1.0f);
		NewRender->CreateAnimation("U", "Ending_Alphabet", 20, 20, false, 1.0f);
		NewRender->CreateAnimation("V", "Ending_Alphabet", 21, 21, false, 1.0f);
		NewRender->CreateAnimation("W", "Ending_Alphabet", 22, 22, false, 1.0f);
		NewRender->CreateAnimation("X", "Ending_Alphabet", 23, 23, false, 1.0f);
		NewRender->CreateAnimation("Y", "Ending_Alphabet", 24, 24, false, 1.0f);
		NewRender->CreateAnimation("Z", "Ending_Alphabet", 25, 25, false, 1.0f);
		NewRender->CreateAnimation("BLANK", "Ending_Alphabet", 26, 26, false, 1.0f);

		// 초기 이미지 지정
		if (false == Blank)
		{
			NewRender->ChangeAnimation(AniName);
		}
		else // 여백이 있으면
		{
			NewRender->ChangeAnimation("BLANK");
			Blank = false;
		}

		NewRender->SetCameraEffectOff();
		NewRender->Off();

		// 위치 지정
		float4 CalcPos = TextStartPos_;
		CalcPos.x = TextStartPos_.x + (CurIndex * 32.f);
		NewRender->SetPivotPos(CalcPos);

		TextRenderer_.push_back(NewRender);
		++TextRendererSize_;
	}
}

void EndingText::MoveStart()
{
	Move_ = true;
}
