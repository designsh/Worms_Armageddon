#include "UIController.h"
#include "WeaponSheet.h"
#include "Weapon.h"

#include "BottomStateUI.h"

#include "WormTopStateUI.h"
#include "WormName.h"
#include "WormArrow.h"
#include "WormHPBlankWindow.h"
#include "WormHPNumber.h"

#include "TimerBlankWindow.h"
#include "TimerDigit.h"

#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineLevel.h>


UIController::UIController() :
	curplayer_(nullptr),
	weaponsheet_(nullptr),
	bottomstate_(nullptr),
	wormtopstate_(nullptr),
	curTimerWindow_(nullptr),
	curTimerDigitTen_(nullptr),
	curTimerDigit_(nullptr)
{
}

UIController::~UIController()
{
}

void UIController::SetCurPlayer(Worm* _curplayer)
{
	curplayer_ = _curplayer;
}

void UIController::CreateWeaponList(const std::vector<eItemList>& _weaponlist)
{
	// ������ �÷��̾���� ���⸮��Ʈ ����
	weaponsheet_->CreateWeaponIconList(_weaponlist);
}

void UIController::AddWeapon(eItemList _Weapon)
{
	weaponsheet_->AddWeapon(_Weapon);
}

void UIController::UseWeapon(eItemList _Weapon)
{
	weaponsheet_->UseWeapon(_Weapon);
}

Worm* UIController::GetCurPlayer() const
{
	return curplayer_;
}

WeaponSheet* UIController::GetCurWeaponSheet() const
{
	return weaponsheet_;
}

BottomStateUI* UIController::GetCurBottomState() const
{
	return bottomstate_;
}

WormTopStateUI* UIController::GetCurTopState() const
{
	return wormtopstate_;
}

TimerBlankWindow* UIController::GetCurTimerWindow()
{
	return curTimerWindow_;
}

TimerDigit* UIController::GetCurTimerDigitTen()
{
	return curTimerDigitTen_;
}

TimerDigit* UIController::GetCurTimerDigit()
{
	return curTimerDigit_;
}

void UIController::Start()
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	// UI�� ���� ����
	// Weapon Sheet ����
	float4 ActivePos = float4({ Resolution.x - 100.f, Resolution.y - 240.f });		// WeaponSheet ActivePos(Ȱ��ȭ��ġ)
	float4 DisablePos = float4({ Resolution.x + 100.f, Resolution.y - 240.f });	// WeaponSheet DisablePos(��Ȱ��ȭ��ġ)
	weaponsheet_ = GetLevel()->CreateActor<WeaponSheet>();						// WeaponSheet ����
	weaponsheet_->SetRenderPos(ActivePos, DisablePos);									// Ȱ��ȭ/��Ȱ��ȭ ��ġ ����														// �ش� WeaponSheet�� ������ UIController ����

	// �÷��̾� ��� ����
	wormtopstate_ = GetLevel()->CreateActor<WormTopStateUI>();

	// �÷��̾� ��Ÿ�� UI
	curTimerWindow_ = GetLevel()->CreateActor<TimerBlankWindow>();
	curTimerDigitTen_ = GetLevel()->CreateActor<TimerDigit>();
	curTimerDigitTen_->SetPos({ 28,690 });
	curTimerDigit_ = GetLevel()->CreateActor<TimerDigit>();
	curTimerDigit_->SetPos({ 48,690 });

	// �÷��̾� �ϴ� ����
	bottomstate_ = GetLevel()->CreateActor<BottomStateUI>();
}

void UIController::UpdateBefore()
{
}

void UIController::Update()
{
}

void UIController::UpdateAfter()
{
}

void UIController::Render()
{
}

void UIController::CurWormUIControllerDeath()
{
	// Weapon Sheet ����
	if (nullptr != weaponsheet_)
	{
		weaponsheet_->Death();
	}

	// ȭ���ϴ� �� �������ͽ� ����
	if (nullptr != bottomstate_)
	{
		// HPText���� ���̰� �״����� �� ���̰�
		bottomstate_->Death();
	}

	// �÷��̾��� �� �������ͽ� ����
	if (nullptr != wormtopstate_)
	{
		wormtopstate_->CurWormHPTextDeath();
		wormtopstate_->Death();
	}

	// �÷��̾� ��Ÿ�� ����
	if (nullptr != curTimerWindow_)
	{
		curTimerWindow_->Death();
	}

	if (nullptr != curTimerDigitTen_)
	{
		curTimerDigitTen_->Death();
	}

	if (nullptr != curTimerDigit_)
	{
		curTimerDigit_->Death();
	}
}
