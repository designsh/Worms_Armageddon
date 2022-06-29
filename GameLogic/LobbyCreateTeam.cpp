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

LobbyCreateTeam::~LobbyCreateTeam() // default destructer ����Ʈ �Ҹ���
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

	// ���� ���õ� �÷��̾� ��Ϲڽ�
	playerboxSpriteRender_ = CreateRenderer("Lobby_PlayerBox");
	ImageHarfSize = playerboxSpriteRender_->GetImageSize().halffloat4();
	playerboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 10.f));
	playerboxSpriteRender_->SetRenderSize(float4(250.f, 180.f));
	playerboxSpriteRender_->SetCameraEffectOff();

	// ���̸�??? �Է¹ڽ�
	playerselInputSpriteRender_ = CreateRenderer("Lobby_SelPlayerInput");
	ImageHarfSize = playerselInputSpriteRender_->GetImageSize().halffloat4();
	playerselInputSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 200.f));
	playerselInputSpriteRender_->SetRenderSize(float4(250.f, 32.f));
	playerselInputSpriteRender_->SetCameraEffectOff();

	// ���ð����� �÷��̾� ��Ϲڽ�
	playerselboxSpriteRender_ = CreateRenderer("Lobby_SelPlayerBox");
	ImageHarfSize = playerselboxSpriteRender_->GetImageSize().halffloat4();
	playerselboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 232.f));
	playerselboxSpriteRender_->SetRenderSize(float4(250.f, 150.f));
	playerselboxSpriteRender_->SetCameraEffectOff();

	// ���ð����� �÷��̾� ��� ����
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

	// ���� �������� �÷��̾� ����� �ִ� �÷��̾� ǥ�� ������ŭ �÷��̾� On
	for (int i = 0; i < 4; ++i)
	{
		// �� ���� ��ġ ��� �� �÷��̾� ǥ��
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
	// ���� ���õ� �÷��̾� �ڽ�
	playerboxSpriteRender_->Render();

	// ���ð����� �÷��̾� �ڽ�
	playerselboxSpriteRender_->Render();

	// �����ϴ� �� �̸� �Է¹ڽ�
	playerselInputSpriteRender_->Render();

	// ���õ� �÷��̾��� ������
	if (!SelectPlayerNameList.empty())
	{
		int PlayerListSize = static_cast<int>(SelectPlayerRendererList.size());
		for (int i = 0; i < PlayerListSize; ++i)
		{
			if (true == SelectPlayerRendererList[i]->IsOn())
			{
				SelectPlayerRendererList[i]->Render();

				// �÷��̾� �̸��� ǥ��
				float4 NamePos = SelectPlayerNamePosList[i];
				TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), NamePos.ix(), NamePos.iy(), SelectPlayerNameList[i].c_str(), lstrlen(SelectPlayerNameList[i].c_str()));
			}
		}
	}
}

void LobbyCreateTeam::SetSelectPlayer(const std::string& _Name, int _Index)
{
	// �Ѱܹ��� �÷��̾������ �÷��̾����� CPU���� �Ǵ��Ѵ�.
	std::string CurSelPlayerName = _Name;
	
	// �÷��̾�(���)�̶��
	GameEngineRenderer* NewRender = nullptr;
	if (0 != CurSelPlayerName.find("CPU"))
	{
		NewRender = CreateRenderer("Lobby_Player");
	}
	else // CPU(��ǻ��)�̶��
	{
		std::string CPURendererName = "Lobby_";
		CPURendererName += CurSelPlayerName;
		NewRender = CreateRenderer(CPURendererName);
	}

	// �ִ� ǥ�ú��� Ŀ���� ������ off
	int RenderListSize = static_cast<int>(SelectPlayerRendererList.size());
	if (4 < RenderListSize)
	{
		NewRender->Off();
	}

	// ������ ũ�� �� ��ġ ����
	NewRender->SetRenderSize(float4(32.f, 32.f));
	float4 ImageHarfSize = NewRender->GetImageSize().halffloat4();
	NewRender->SetPivotPos(float4(ImageHarfSize.x + 230.f, ImageHarfSize.y + 18.f + (RenderListSize * 34.f)));

	SelectPlayerRendererList.push_back(NewRender);

	// ���� ������ �÷��̾� �� ����
	// �ӽ��ּ� : �׽�Ʈ ���Ƿ� ���� 6���� ���� ���� ������ �ּ�����
	GameOptionInfo::CurWormCnt = static_cast<int>(SelectPlayerRendererList.size());

	// ���� ������ �÷��̾���� ���� �� ����
	// �ӽ��ּ� : �׽�Ʈ ���Ƿ� ���� 6���� ���� ���� ������ �ּ�����
	GameOptionInfo::CurPlayerName.push_back(_Name);
	std::sort(GameOptionInfo::CurPlayerName.begin(), GameOptionInfo::CurPlayerName.end());

	// �÷��̾��̸� ǥ�� �� ������ �÷��̾��̸���Ͽ� �߰�
	int NameListSize = static_cast<int>(SelectPlayerNameList.size());
	SelectPlayerNameList.push_back(CurSelPlayerName);

	// �÷��̾��̸� ǥ�ø� ���� ��ġ��� �߰�
	float4 NamePos = float4::ZERO;
	NamePos.x = 272.f;
	NamePos.y = 28.f + (RenderListSize * 36.f);
	SelectPlayerNamePosList.push_back(NamePos);

	// ���ð��� �÷��̾��Ͽ��� ���� ���õ� �÷��̾� Off
	SelectablePlayerList[_Index]->SetPlayerOff();
	SelectablePlayerList[_Index]->DelActiveIndex();

	// ���� Ȱ��ȭ�ؾ��ϴ� �÷��̾� �ε��� ����
	// ���ð��� �÷��̾� ��Ͽ��� ù��°�� On�� �Ǿ��ִ�
	// �ε����� Ž��
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

	// ���� ���ð����÷��̾�����ü ������ Off
	for (int i = 0; i < SelectablePlayerSize; ++i)
	{
		SelectablePlayerList[i]->SetPlayerOff();
		SelectablePlayerList[i]->DelActiveIndex();
	}

	// �ִ� 4���� ���ð��� �÷��̾ ǥ�õǹǷ�
	// ��ü���ð��� �÷��̾��Ͽ��� 4���ε��� �����Ͽ�
	// ���ð����÷��̾� ��� ������ ���� �ε��� ����
	// �̹� ������ ����� �ε����� �����ϴ� ��츦 �����ϱ� ���Ͽ� 
	// �˻�
	ActiveStartIndex_ = FistOnPlayerIdx;
	ActiveEndIndex_ = FistOnPlayerIdx + 4 + static_cast<int>(CurSelectIndex_.size());
	if (ActiveEndIndex_ > static_cast<int>(SelectablePlayerList.size()))
	{
		ActiveEndIndex_ = static_cast<int>(SelectablePlayerList.size());
	}

	// ���� ���õ� �÷��̾� �ε��� ����
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

	// ActiveStartIndex_ ~ ActiveEndIndex_ ������ ���ð����÷��̾� ����� �÷��̾� Ȱ��ȭ
	int CalcIndex = 0;
	int activeidx = -1;
	int addindex = -1;
	int continuecnt = 0;
	bool Flag = false;
	bool SamePlayer = false;
	int i = 0;
	for (i = ActiveStartIndex_; i < ActiveEndIndex_; ++i)
	{
		// ���ð��� �÷��̾����� �ִ�ġ�� �Ѿ�� �ߴ�
		if (i >= static_cast<int>(SelectablePlayerList.size()))
		{
			break;
		}

		// ���� ���õ� �÷��̾�� ����
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
	
	// ���� ���õ� �÷��̾ ������ ����
	if (true == Flag)
	{
		// ���� ���ð��ɸ�� ������ �ε����� �ִ� �÷��̾ ���õǾ��ٸ�
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

