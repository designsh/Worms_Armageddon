#include "ChattingHistory.h"

#include <EngineEnum.h>
#include <GameEngineInput.h>
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>
#include <GameEngineRenderer.h>

std::list<std::string> ChattingHistory::historychatt_;
std::string ChattingHistory::hostname_ = "";

void ChattingHistory::ChattingHistoryAdd(const std::string& _ChattingText)
{
	// ä�� �̷º����� �Ѵ�.
	// ��, �̷� ���� �ִ�ġ�� �Ѿ�� �տ������� �����.
	size_t CurHistory = historychatt_.size();
	if (MAX_CHATTINGHISTORY <= CurHistory)
	{
		// �Ǿ��� �̷��� ����� �ڿ� ����
		historychatt_.pop_front();
		historychatt_.push_back(_ChattingText);
	}
	else
	{
		historychatt_.push_back(_ChattingText);
	}
}

void ChattingHistory::CurHostName(const std::string& _HostName)
{
	hostname_ = _HostName;
}

ChattingHistory::ChattingHistory() :
	chattingHisBoxSpriteRender_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

ChattingHistory::~ChattingHistory()
{
	// �Ҹ�� �̷��� ��� ����
	if (!historychatt_.empty())
	{
		historychatt_.clear();
	}
}

ChattingHistory::ChattingHistory(ChattingHistory&& _other) noexcept :
	chattingHisBoxSpriteRender_(_other.chattingHisBoxSpriteRender_)
{
}

void ChattingHistory::Start()
{
	chattingHisBoxSpriteRender_ = CreateRenderer("Lobby_ChattingHis");
	float4 ImageHarfSize = chattingHisBoxSpriteRender_->GetImageSize().halffloat4();
	chattingHisBoxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 390.f));
	chattingHisBoxSpriteRender_->SetRenderSize(float4(1260.f, 250.f));
	chattingHisBoxSpriteRender_->SetCameraEffectOff();
}

void ChattingHistory::UpdateBefore()
{
}

void ChattingHistory::Update()
{
}

void ChattingHistory::UpdateAfter()
{
}

void ChattingHistory::Render()
{
	chattingHisBoxSpriteRender_->Render();

	size_t HistCnt = historychatt_.size();
	if (0 < HistCnt)
	{
		std::list<std::string>::iterator StartIter = historychatt_.begin();
		std::list<std::string>::iterator EndIter = historychatt_.end();
		int Index = 0;
		for (; StartIter != EndIter; ++StartIter)
		{
			std::string CurHistoryChatt = hostname_;
			CurHistoryChatt += " : ";
			CurHistoryChatt += (*StartIter);
			TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), 20, 400 + (Index * 18), CurHistoryChatt.c_str(), lstrlen(CurHistoryChatt.c_str()));

			++Index;
		}
	}
}

