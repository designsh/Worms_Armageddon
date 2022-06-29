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
	// 각각의 플레이어마다의 무기리스트 생성
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

	// UI별 액터 생성
	// Weapon Sheet 생성
	float4 ActivePos = float4({ Resolution.x - 100.f, Resolution.y - 240.f });		// WeaponSheet ActivePos(활성화위치)
	float4 DisablePos = float4({ Resolution.x + 100.f, Resolution.y - 240.f });	// WeaponSheet DisablePos(비활성화위치)
	weaponsheet_ = GetLevel()->CreateActor<WeaponSheet>();						// WeaponSheet 생성
	weaponsheet_->SetRenderPos(ActivePos, DisablePos);									// 활성화/비활성화 위치 설정														// 해당 WeaponSheet를 생성한 UIController 저장

	// 플레이어 상단 상태
	wormtopstate_ = GetLevel()->CreateActor<WormTopStateUI>();

	// 플레이어 턴타임 UI
	curTimerWindow_ = GetLevel()->CreateActor<TimerBlankWindow>();
	curTimerDigitTen_ = GetLevel()->CreateActor<TimerDigit>();
	curTimerDigitTen_->SetPos({ 28,690 });
	curTimerDigit_ = GetLevel()->CreateActor<TimerDigit>();
	curTimerDigit_->SetPos({ 48,690 });

	// 플레이어 하단 상태
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
	// Weapon Sheet 관련
	if (nullptr != weaponsheet_)
	{
		weaponsheet_->Death();
	}

	// 화면하단 웜 스테이터스 관련
	if (nullptr != bottomstate_)
	{
		// HPText먼저 죽이고 그다음에 얘 죽이고
		bottomstate_->Death();
	}

	// 플레이어상단 웜 스테이터스 관련
	if (nullptr != wormtopstate_)
	{
		wormtopstate_->CurWormHPTextDeath();
		wormtopstate_->Death();
	}

	// 플레이어 턴타임 관련
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
