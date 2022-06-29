#include "LobbySelectablePlayer.h"
#include "LobbyCreateTeam.h"
#include "eCollisionGroup.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbySelectablePlayer::LobbySelectablePlayer() :
	parent_(nullptr),
	ActiveIndex_(-1),
	SelectPlayerEnd_(false),
	ShowPlayer_(false),
	Index_(-1),
	NamePos_(float4::ZERO),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI1));
}

LobbySelectablePlayer::~LobbySelectablePlayer()
{
}

LobbySelectablePlayer::LobbySelectablePlayer(LobbySelectablePlayer&& _other) noexcept :
	parent_(_other.parent_),
	ActiveIndex_(_other.ActiveIndex_),
	SelectPlayerEnd_(_other.SelectPlayerEnd_),
	ShowPlayer_(_other.ShowPlayer_),
	Index_(_other.Index_), 
	NamePos_(_other.NamePos_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{
}

void LobbySelectablePlayer::Start()
{
}

void LobbySelectablePlayer::UpdateBefore()
{
	// ���콺�� �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			if (true == ShowPlayer_)
			{
				// ������ �÷��̾� �߰� �� ���ô��� �÷��̾ ���ð����� �÷��̾��Ͽ��� Off
				// �Ŀ� ���ð����� �÷��̾��� ��ĭ�������(��, ��ġ����)
				// ���� ���õ� �÷��̾�� �浹ü�� �������� ��� Off ��Ų��.
				parent_->SetSelectPlayer(Name_, Index_);
			}
		}
	}
}

void LobbySelectablePlayer::Update()
{
}

void LobbySelectablePlayer::UpdateAfter()
{
}

void LobbySelectablePlayer::Render()
{
	// ȭ��� ǥ���ϴ� �͸� ǥ��
	if (true == ShowPlayer_)
	{
		// �÷��̾� �̹��� ǥ��
		if (nullptr != mainrenderer_)
		{
			mainrenderer_->Render();

			// �÷��̾� ��Ī ǥ��
			if (!Name_.empty())
			{
				TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), NamePos_.ix(), NamePos_.iy(), Name_.c_str(), lstrlen(Name_.c_str()));
			}
		}
	}

	//maincollision_->DebugRender();
}

void LobbySelectablePlayer::Collision()
{
	if (true == SelectPlayerEnd_)
	{
		// ���⼭ ���ð��� �÷��̾����� ����
		parent_->SetSelectablePlayerSort();
		SelectPlayerEnd_ = false;
	}
}

std::string LobbySelectablePlayer::GetPlayerName() const
{
	return Name_;
}

int LobbySelectablePlayer::GetIndex() const
{
	return Index_;
}

int LobbySelectablePlayer::GetActiveIndex() const
{
	return ActiveIndex_;
}

bool LobbySelectablePlayer::GetCurPlayerShow() const
{
	return ShowPlayer_;
}

GameEngineCollision* LobbySelectablePlayer::GetMainCollision() const
{
	return maincollision_;
}

void LobbySelectablePlayer::SetPlayerInfo(LobbyCreateTeam* _Parent, const float4& _NamePos, const float4& _RenderPos, const float4& _RenderSize)
{
	// ������ ��ġ ����
	if (nullptr == mainrenderer_)
	{
		return;
	}

	float4 HarfSize = mainrenderer_->GetImageSize().halffloat4();
	float4 RenderSize = _RenderSize;

	mainrenderer_->SetPivotPos(float4(HarfSize.x + _RenderPos.x, HarfSize.y + _RenderPos.y));

	// ����ũ�Ⱑ ���������ʾҴٸ� �������� �̹��� ũ��� �����ȴ�.
	if (RenderSize == float4::ZERO)
	{
		RenderSize = mainrenderer_->GetImageSize();
		mainrenderer_->SetRenderSize(RenderSize);
	}
	else
	{
		mainrenderer_->SetRenderSize(RenderSize);
	}

	// �浹ü ��ġ ���� �� �浹ü On
	if (nullptr == maincollision_)
	{
		return;
	}

	maincollision_->SetSize(RenderSize);
	maincollision_->SetPivot(float4((RenderSize.x * 0.5f) + _RenderPos.x, (RenderSize.y * 0.5f) + _RenderPos.y));

	// Index���� ����
	NamePos_ = _NamePos;
	parent_ = _Parent;
}

void LobbySelectablePlayer::ChangePlayerPos(const float4& _NamePos, const float4& _RenderPos, const float4& _RenderSize)
{
	// ������ ��ġ ����
	if (nullptr == mainrenderer_)
	{
		return;
	}

	float4 ImageSize = mainrenderer_->GetImageSize();
	float4 HarfSize = ImageSize.halffloat4();
	float4 RenderSize = _RenderSize;

	mainrenderer_->SetPivotPos(float4(HarfSize.x + _RenderPos.x, HarfSize.y + _RenderPos.y));

	// ����ũ�Ⱑ ���������ʾҴٸ� �������� �̹��� ũ��� �����ȴ�.
	if (RenderSize == float4::ZERO)
	{
		mainrenderer_->SetRenderSize(ImageSize);
	}
	else
	{
		mainrenderer_->SetRenderSize(_RenderSize);
	}

	// �浹ü ��ġ ���� �� �浹ü On
	if (nullptr == maincollision_)
	{
		return;
	}

	maincollision_->SetSize(_RenderSize);
	maincollision_->SetPivot(float4((_RenderSize.x * 0.5f) + _RenderPos.x, (_RenderSize.y * 0.5f) + _RenderPos.y));

	// �÷��̾� �� ��ġ ����
	NamePos_ = _NamePos;
}

void LobbySelectablePlayer::SetPlayerOn(int _ActiveIndex)
{
	// ���� ShowPlayer_���� On
	ShowPlayer_ = true;

	// �浹ü On
	if (nullptr == maincollision_)
	{
		return;
	}
	maincollision_->On();
	mainrenderer_->On();

	// Ȱ��ȭ �ε��� ����
	ActiveIndex_ = _ActiveIndex;
}

void LobbySelectablePlayer::SetPlayerOff()
{
	// ���� ShowPlayer_���� Off
	ShowPlayer_ = false;

	// �浹ü Off
	if (nullptr == maincollision_)
	{
		return;
	}

	// �浹ü�� ������ ȭ������� �������� ũ�⸦ 1�� �ٲ۴�.
	maincollision_->SetSize(float4(1.f, 1.f));
	maincollision_->SetPivot(float4(-1200.f, -1200.f));

	maincollision_->Off();
	mainrenderer_->Off();

	// �÷��̾�ÿϷ� Flag On
	SelectPlayerEnd_ = true;
}

void LobbySelectablePlayer::DelActiveIndex()
{
	ActiveIndex_ = -1;
}

void LobbySelectablePlayer::CreatePlayer(const std::string& _PlayerName, int _Index, int _CPUIndex, bool _PlayerAndCPU)
{
	// �⺻���� ����
	Index_ = _Index;
	Name_ = _PlayerName;
	ShowPlayer_ = false;

	// ������ ����
	if (true == _PlayerAndCPU) // �÷��̾�
	{
		mainrenderer_ = CreateRenderer("Lobby_Player");
	}
	else // CPU
	{
		std::string CPUName = "Lobby_CPU";
		CPUName += std::to_string(_CPUIndex + 1);
		mainrenderer_ = CreateRenderer(CPUName);
	}
	mainrenderer_->Off();
	mainrenderer_->SetCameraEffectOff();

	// �浹ü ���� �� OFF
	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->Off();
}

