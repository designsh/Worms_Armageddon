#include "LobbyHost.h"
#include "ChattingHistory.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineImageFile.h>
#include <GameEngineImage.h>

bool LobbyHost::curhostready_ = true;

void LobbyHost::SetCurHostReady(bool _Flag)
{
	curhostready_ = _Flag;
}

bool LobbyHost::SetCurHostReady()
{
	return curhostready_;
}

LobbyHost::LobbyHost() :
	hostnationSpriteRender_(nullptr),
	hostreadystateSpriteRender_(nullptr),
	hostName_{}
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI) + 1);
}

LobbyHost::~LobbyHost()
{

}

LobbyHost::LobbyHost(LobbyHost&& _other) noexcept :
	hostnationSpriteRender_(_other.hostnationSpriteRender_),
	hostreadystateSpriteRender_(_other.hostreadystateSpriteRender_),
	hostName_(_other.hostName_)
{

}

void LobbyHost::Start()
{
	curhostready_ = true;

	// ���� PC�� �̸� ��������
	char ComputerName[256] = {};
	unsigned long ComputerNameLen = 100;
	GetComputerName(ComputerName, &ComputerNameLen);

	// �ش� ��ǻ�͸����� Host�� ����
	hostName_ = ComputerName;
	ChattingHistory::CurHostName(hostName_);

	SetBkMode(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), TRANSPARENT);
	SetTextColor(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), RGB(255, 255, 255));

	// ���� PC�� �����ڵ� ��������
	int iLang = 0;
	char szNation[7];
	if (0 != GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_ICOUNTRY, szNation, 7))
	{
		iLang = atoi(szNation);
	}

	// ���� PC�� ���� ���� �Ǻ�
	switch (iLang)
	{
		case 82: // ���ѹα�
		{
			float4 ImageHarfSize = float4::ZERO;

			// ȣ��Ʈ �غ���� ������ ����
			hostreadystateSpriteRender_ = CreateRenderer("Lobby_HostCurReadyOff");
			ImageHarfSize = hostreadystateSpriteRender_->GetImageSize().halffloat4();
			hostreadystateSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 20.f, ImageHarfSize.y + 16.f));
			hostreadystateSpriteRender_->SetRenderSize(float4(28.f, 28.f));
			hostreadystateSpriteRender_->SetCameraEffectOff();

			// ���� ������ ����
			hostnationSpriteRender_ = CreateRenderer("LobbyNation_Kor");
			ImageHarfSize = hostnationSpriteRender_->GetImageSize().halffloat4();
			hostnationSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 34.f, ImageHarfSize.y + 16.f));
			hostnationSpriteRender_->SetRenderSize(float4(40.f, 28.f));
			hostnationSpriteRender_->SetCameraEffectOff();

			break;
		}
	}
}

void LobbyHost::UpdateBefore()
{
}

void LobbyHost::Update()
{
}

void LobbyHost::UpdateAfter()
{
}

void LobbyHost::Render()
{
	if (true == hostreadystateSpriteRender_->IsOn())
	{
		if (false == curhostready_)
		{
			hostreadystateSpriteRender_->SetImage("Lobby_HostCurReadyOff");
		}
		else
		{
			hostreadystateSpriteRender_->SetImage("Lobby_HostCurReadyOn");
		}

		float4 ImageHarfSize = hostreadystateSpriteRender_->GetImageSize().halffloat4();
		hostreadystateSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 16.f));
		hostreadystateSpriteRender_->SetRenderSize(float4(28.f, 28.f));
		hostreadystateSpriteRender_->Render();
	}

	if (true == hostnationSpriteRender_->IsOn())
	{
		hostnationSpriteRender_->Render();
	}

	// Host��
	if (false == hostName_.empty())
	{
		TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), 76, 20, hostName_.c_str(), lstrlen(hostName_.c_str()));
	}
}

