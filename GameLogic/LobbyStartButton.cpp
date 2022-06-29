#include "LobbyStartButton.h"
#include "ChattingInput.h"
#include "LobbyHost.h"
#include "GameOptionInfo.h"

#include <EngineEnum.h>
#include "eCollisionGroup.h"
#include <GameEngineInput.h>
#include <GameEngineWindow.h>
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>
#include <GameEngineLevelManager.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyStartButton::LobbyStartButton() :
	mainrenderer_(nullptr),
	maincollision_(nullptr),
	mouseover_(false)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyStartButton::~LobbyStartButton()
{

}

LobbyStartButton::LobbyStartButton(LobbyStartButton&& _other) noexcept :
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_),
	mouseover_(_other.mouseover_)
{

}

void LobbyStartButton::Start()
{
	float4 ImageHarfSize = float4::ZERO;

	// ��ư ������ ����
	mainrenderer_ = CreateRenderer("Lobby_ButtonNormal");
	ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 1020.f, ImageHarfSize.y + 650.f));
	mainrenderer_->SetRenderSize(float4(250.f, 34.f));
	mainrenderer_->SetCameraEffectOff();

	// ��ư �浹ü ����
	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(float4(250.f, 34.f));
	maincollision_->SetPivot(float4(125.f + 1020.f, 17.f + 650.f));

	// ��ư Text ����(�ӽ�)
	GameStartText_ = "Start the Game";
}

void LobbyStartButton::UpdateBefore()
{
	// ���콺�� �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		// ���� �浹�ÿ��� �̹��� ��ȯ
		if (false == mouseover_)
		{
			// Flag On
			mouseover_ = true;

			// Button Box Image Change
			mainrenderer_->SetImage("Lobby_ButtonMouseOn");
			float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
			mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 1020.f, ImageHarfSize.y + 650.f));
			mainrenderer_->SetRenderSize(float4(250.f, 34.f));

			// Button Text Image Change

		}
	}
	else
	{
		mouseover_ = false;
	}
}

void LobbyStartButton::Update()
{
	// ���콺�� ��ư�� �浹���̶��
	if (true == mouseover_)
	{
		// ���콺�� �浹�߿� Ŭ���Ǿ�����
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// Host�� Ready �����̸� �����ϴ� ������ �÷��̾� ���� 2���̻��� �� ���ӽ��� ����
			if (true == LobbyHost::SetCurHostReady() && 2 <= GameOptionInfo::CurWormCnt)
			{
				// ����ȯ
				GameEngineLevelManager::GetInst().ChangeLevel("PlayLevel", true);

				// ĳ�� �ݳ� �� Flag ����
				ChattingInput::SetCurCaretState(false);
				SetCaretBlinkTime(500);
				HideCaret(GameEngineWindow::GetInst().GetMainWindowHandle());
				DestroyCaret();
			}
		}
	}
	else
	{
		mainrenderer_->SetImage("Lobby_ButtonNormal");
		float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
		mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 1020.f, ImageHarfSize.y + 650.f));
		mainrenderer_->SetRenderSize(float4(250.f, 34.f));
	}
}

void LobbyStartButton::UpdateAfter()
{
}

void LobbyStartButton::Render()
{
	if (true == mainrenderer_->IsOn())
	{
		mainrenderer_->Render();
	}

	// �ӽ� ���� �̹����� ����
	if (!GameStartText_.empty())
	{
		TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), 1100, 658, GameStartText_.c_str(), lstrlen(GameStartText_.c_str()));
	}
}

