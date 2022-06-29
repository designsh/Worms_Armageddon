#include "LobbyCreateTeam.h"
#include "LobbySelectablePlayer.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineLevel.h>
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>

#include <algorithm>

int LobbyCreateTeam::PlayWormCount = 0;

LobbyCreateTeam::LobbyCreateTeam() :
	playerselInputSpriteRender_(nullptr),
	playerboxSpriteRender_(nullptr),
	playerselboxSpriteRender_(nullptr),
	ActiveStartIndex_(0),
	ActiveEndIndex_(3)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyCreateTeam::~LobbyCreateTeam() // default destructer 디폴트 소멸자
{

}

LobbyCreateTeam::LobbyCreateTeam(LobbyCreateTeam&& _other) noexcept :
	playerselInputSpriteRender_(_other.playerselInputSpriteRender_),
	playerselboxSpriteRender_(_other.playerselboxSpriteRender_),
	playerboxSpriteRender_(_other.playerboxSpriteRender_),
	ActiveStartIndex_(_other.ActiveStartIndex_),
	ActiveEndIndex_(_other.ActiveEndIndex_)
{
}

void LobbyCreateTeam::Start()
{
	float4 ImageHarfSize = float4::ZERO;

	// 현재 선택된 플레이어 목록박스
	playerboxSpriteRender_ = CreateRenderer("Lobby_PlayerBox");
	ImageHarfSize = playerboxSpriteRender_->GetImageSize().halffloat4();
	playerboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 10.f));
	playerboxSpriteRender_->SetRenderSize(float4(250.f, 180.f));
	playerboxSpriteRender_->SetCameraEffectOff();

	// 팀이름??? 입력박스
	playerselInputSpriteRender_ = CreateRenderer("Lobby_SelPlayerInput");
	ImageHarfSize = playerselInputSpriteRender_->GetImageSize().halffloat4();
	playerselInputSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 200.f));
	playerselInputSpriteRender_->SetRenderSize(float4(250.f, 32.f));
	playerselInputSpriteRender_->SetCameraEffectOff();

	// 선택가능한 플레이어 목록박스
	playerselboxSpriteRender_ = CreateRenderer("Lobby_SelPlayerBox");
	ImageHarfSize = playerselboxSpriteRender_->GetImageSize().halffloat4();
	playerselboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 232.f));
	playerselboxSpriteRender_->SetRenderSize(float4(250.f, 150.f));
	playerselboxSpriteRender_->SetCameraEffectOff();

	// 선택가능한 플레이어 목록 생성
	int Index = 0;
	for (int i = 0; i < 6; ++i)
	{
		std::string PlayerName = std::to_string(i + 1);
		PlayerName += "-UP";

		LobbySelectablePlayer* NewPlayer = GetLevel()->CreateActor<LobbySelectablePlayer>();
		NewPlayer->CreatePlayer(PlayerName, i, 0);
		SelectablePlayerList.push_back(NewPlayer);
	}

	for (int i = 0; i < static_cast<int>(SelectablePlayerList.size()); ++i)
	{
		SelectablePlayerList[i]->SetPlayerInfo(this, float4(272.f, (245.f + (i * 36.f))), float4(230.f, (236.f + (i * 34.f))), float4(32.f, 32.f));
	}

	// 현재 관리중인 플레이어 목록중 최대 플레이어 표시 갯수만큼 플레이어 On
	for (int i = 0; i < 4; ++i)
	{
		// 각 액터 위치 계산 후 플레이어 표시
		SelectablePlayerList[i]->SetPlayerOn(i);
	}
}

void LobbyCreateTeam::UpdateBefore()
{
}

void LobbyCreateTeam::Update()
{
}

void LobbyCreateTeam::UpdateAfter()
{
}

void LobbyCreateTeam::Render()
{
	// 현재 선택된 플레이어 박스
	playerboxSpriteRender_->Render();

	// 선택가능한 플레이어 박스
	playerselboxSpriteRender_->Render();

	// 생성하는 팀 이름 입력박스
	playerselInputSpriteRender_->Render();

	// 선택된 플레이어목록 렌더링
	if (!SelectPlayerNameList.empty())
	{
		int PlayerListSize = static_cast<int>(SelectPlayerRendererList.size());
		for (int i = 0; i < PlayerListSize; ++i)
		{
			if (true == SelectPlayerRendererList[i]->IsOn())
			{
				SelectPlayerRendererList[i]->Render();

				// 플레이어 이름을 표시
				float4 NamePos = SelectPlayerNamePosList[i];
				TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), NamePos.ix(), NamePos.iy(), SelectPlayerNameList[i].c_str(), lstrlen(SelectPlayerNameList[i].c_str()));
			}
		}
	}
}

void LobbyCreateTeam::SetSelectPlayer(const std::string& _Name, int _Index)
{
	// 넘겨받은 플레이어명으로 플레이어인지 CPU인지 판단한다.
	std::string CurSelPlayerName = _Name;
	
	// 플레이어(사람)이라면
	GameEngineRenderer* NewRender = nullptr;
	if (0 != CurSelPlayerName.find("CPU"))
	{
		NewRender = CreateRenderer("Lobby_Player");
	}
	else // CPU(컴퓨터)이라면
	{
		std::string CPURendererName = "Lobby_";
		CPURendererName += CurSelPlayerName;
		NewRender = CreateRenderer(CPURendererName);
	}

	// 최대 표시보다 커지면 렌더러 off
	int RenderListSize = static_cast<int>(SelectPlayerRendererList.size());
	if (4 < RenderListSize)
	{
		NewRender->Off();
	}

	// 렌더러 크기 및 위치 지정
	NewRender->SetRenderSize(float4(32.f, 32.f));
	float4 ImageHarfSize = NewRender->GetImageSize().halffloat4();
	NewRender->SetPivotPos(float4(ImageHarfSize.x + 230.f, ImageHarfSize.y + 18.f + (RenderListSize * 34.f)));

	SelectPlayerRendererList.push_back(NewRender);

	// 현재 선택한 플레이어 수 저장
	// 임시주석 : 테스트 편의로 인해 6으로 고정 추후 가동시 주석해제
	GameOptionInfo::CurWormCnt = static_cast<int>(SelectPlayerRendererList.size());

	// 현재 선택한 플레이어명을 저장 후 정렬
	// 임시주석 : 테스트 편의로 인해 6으로 고정 추후 가동시 주석해제
	GameOptionInfo::CurPlayerName.push_back(_Name);
	std::sort(GameOptionInfo::CurPlayerName.begin(), GameOptionInfo::CurPlayerName.end());

	// 플레이어이름 표시 및 선택한 플레이어이름목록에 추가
	int NameListSize = static_cast<int>(SelectPlayerNameList.size());
	SelectPlayerNameList.push_back(CurSelPlayerName);

	// 플레이어이름 표시를 위한 위치목록 추가
	float4 NamePos = float4::ZERO;
	NamePos.x = 272.f;
	NamePos.y = 28.f + (RenderListSize * 36.f);
	SelectPlayerNamePosList.push_back(NamePos);

	// 선택가능 플레이어목록에서 현재 선택된 플레이어 Off
	SelectablePlayerList[_Index]->SetPlayerOff();
	SelectablePlayerList[_Index]->DelActiveIndex();

	// 현재 활성화해야하는 플레이어 인덱스 저장
	// 선택가능 플레이어 목록에서 첫번째로 On이 되어있는
	// 인덱스를 탐색
	int SelectablePlayerSize = static_cast<int>(SelectablePlayerList.size());
	int FistOnPlayerIdx = -1;
	for (int i = 0; i < SelectablePlayerSize; ++i)
	{
		if (true == SelectablePlayerList[i]->GetCurPlayerShow())
		{
			FistOnPlayerIdx = i;
			break;
		}
	}

	// 기존 선택가능플레이어목록전체 렌더링 Off
	for (int i = 0; i < SelectablePlayerSize; ++i)
	{
		SelectablePlayerList[i]->SetPlayerOff();
		SelectablePlayerList[i]->DelActiveIndex();
	}

	// 최대 4명의 선택가능 플레이어가 표시되므로
	// 전체선택가능 플레이어목록에서 4명인덱스 추출하여
	// 선택가능플레이어 목록 갱신을 위한 인덱스 추출
	// 이미 선택한 목록의 인덱스를 포함하는 경우를 제외하기 위하여 
	// 검사
	ActiveStartIndex_ = FistOnPlayerIdx;
	ActiveEndIndex_ = FistOnPlayerIdx + 4 + static_cast<int>(CurSelectIndex_.size());
	if (ActiveEndIndex_ > static_cast<int>(SelectablePlayerList.size()))
	{
		ActiveEndIndex_ = static_cast<int>(SelectablePlayerList.size());
	}

	// 현재 선택된 플레이어 인덱스 저장
	CurSelectIndex_.push_back(_Index);
}

void LobbyCreateTeam::SetSelectablePlayerSort()
{
	if (ActiveStartIndex_ == static_cast<int>(SelectablePlayerList.size()))
	{
		return;
	}
	else if (-1 == ActiveStartIndex_)
	{
		return;
	}

	// ActiveStartIndex_ ~ ActiveEndIndex_ 까지의 선택가능플레이어 목록의 플레이어 활성화
	int CalcIndex = 0;
	int activeidx = -1;
	int addindex = -1;
	int continuecnt = 0;
	bool Flag = false;
	bool SamePlayer = false;
	int i = 0;
	for (i = ActiveStartIndex_; i < ActiveEndIndex_; ++i)
	{
		// 선택가능 플레이어목록의 최대치를 넘어가면 중단
		if (i >= static_cast<int>(SelectablePlayerList.size()))
		{
			break;
		}

		// 현재 선택된 플레이어는 제외
		if (false == SamePlayer)
		{
			for (int j = 0; j < static_cast<int>(CurSelectIndex_.size()); ++j)
			{
				if (i == CurSelectIndex_[j])
				{
					Flag = true;
					SamePlayer = true;
					++continuecnt;
				}
			}

			if (true == SamePlayer)
			{
				SamePlayer = false;
				continue;
			}
		}

		SelectablePlayerList[i]->ChangePlayerPos(float4(272.f, (245.f + (CalcIndex * 36.f))), float4(230.f, (236.f + (CalcIndex * 34.f))), float4(32.f, 32.f));
		SelectablePlayerList[i]->SetPlayerOn(CalcIndex);

		++CalcIndex;

		if (true == Flag)
		{
			addindex = i;
		}
	}
	
	// 현재 선택된 플레이어를 제외한 갱신
	if (true == Flag)
	{
		// 현재 선택가능목록 마지막 인덱스에 있는 플레이어가 선택되었다면
		if (-1 == addindex)
		{
			++CalcIndex;
			addindex = i;
			continuecnt = 0;
		}

		--CalcIndex;
		for (int i = addindex; i <= (addindex + continuecnt); ++i)
		{
			if (i >= static_cast<int>(SelectablePlayerList.size()))
			{
				Flag = false;
				break;
			}

			SelectablePlayerList[i]->ChangePlayerPos(float4(272.f, (245.f + (CalcIndex * 36.f))), float4(230.f, (236.f + (CalcIndex * 34.f))), float4(32.f, 32.f));
			SelectablePlayerList[i]->SetPlayerOn(CalcIndex);

			++CalcIndex;
		}

		Flag = false;
	}
}

void LobbyCreateTeam::CreateSelectPlayerOption()
{
}

