#include "WeaponSheet.h"
#include "eCollisionGroup.h"

#include "MouseObject.h"
#include "WeaponIcon.h"
#include "Weapon.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <EngineEnum.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

bool WeaponSheet::weaponsheetactive_ = false;

bool WeaponSheet::isweaponsheet()
{
	return weaponsheetactive_;
}

WeaponSheet::WeaponSheet() :
	parentcontroller_(nullptr),
	active_(false),
	prevstate_(false),
	forceternoff_(false),
	mainrenderer(nullptr),
	mouseobject_(nullptr),
	activetargetpos_(float4::ZERO),
	disabletargetpos_(float4::ZERO),
	moving_(false),
	movingspeed(2.f),
	movepos_(float4::ZERO)
{
}

WeaponSheet::~WeaponSheet() // default destructer 디폴트 소멸자
{
	// 사용된 무기목록 제거
	std::map<eItemList, Weapon*>::iterator StartIter = weaponlist_.begin();
	std::map<eItemList, Weapon*>::iterator EndIter = weaponlist_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		delete StartIter->second;
		StartIter->second = nullptr;
	}
	weaponlist_.clear();
}

WeaponSheet::WeaponSheet(WeaponSheet&& _other) noexcept :
	parentcontroller_(_other.parentcontroller_),
	active_(_other.active_),
	forceternoff_(_other.forceternoff_),
	prevstate_(_other.prevstate_),
	mainrenderer(_other.mainrenderer),
	mouseobject_(_other.mouseobject_),
	activetargetpos_(_other.activetargetpos_),
	disabletargetpos_(_other.disabletargetpos_),
	moving_(_other.moving_),
	movingspeed(_other.movingspeed),
	movepos_(_other.movepos_)
{

}

void WeaponSheet::Start()
{
	// 렌더러 생성 및 카메라영향 제거
	SetRenderOrder(static_cast<int>(RenderOrder::UI2));
	mainrenderer = CreateRenderer("WeaponSheet");
	mainrenderer->SetCameraEffectOff();

	// 아이콘 기본위치 설정 및 아이콘액터 생성
	CreateIconDefaultPos();
}

void WeaponSheet::UpdateBefore()
{

}

void WeaponSheet::Update()
{
	// 어딘가로부터 키입력시 활성화/비활성화
	if (true == active_) // 비활성화 -> 활성화
	{
		// 만약 활성화 타겟위치까지 이동했다면 중단
		if (activetargetpos_.x <= GetPos().x)
		{
			movepos_ += float4::LEFT * GameEngineTime::GetInst().GetDeltaTime();
			SetMove(movepos_ * movingspeed);

			moving_ = true;
		}
		else
		{
			moving_ = false;
			weaponsheetactive_ = true;
		}

		// 마우스커서 위치 강제 범위지정
		// 윈도우 커서가 해당 범위를 벗어나면 MAX값으로 이동하도록 설정
		float4 MousePos = GameEngineWindow::GetInst().GetMousePos();
		float4 LeftTop = activetargetpos_ - mainrenderer->GetImageSize().halffloat4();
		float4 RightBot = activetargetpos_ + mainrenderer->GetImageSize().halffloat4();
	}
	else if(true == prevstate_ && false == active_) // 활성화 -> 비활성화
	{
		// 비활성시에는 바로 마우스위치 제자리로돌린다.
		weaponsheetactive_ = false;

		if (disabletargetpos_.x > GetPos().x)
		{
			movepos_ += float4::RIGHT * GameEngineTime::GetInst().GetDeltaTime();
			SetMove(movepos_ * movingspeed);

			moving_ = true;
		}
		else
		{
			moving_ = false;
			forceternoff_ = false;
		}

		// 비활성화시에는 바로 Off시킴
		if (true == prevstate_)
		{
			mouseobject_->SetFinalPos(mouseobject_->GetPos());
		}
	}

	// 이동중이 아닐때 이전상태와 현재 상태가 다를때 처리
	if (false == moving_)
	{
		movepos_ = float4::ZERO;

		if (prevstate_ != active_)
		{
			prevstate_ = active_;
		}
	}
}

void WeaponSheet::UpdateAfter()
{
}

void WeaponSheet::Render()
{
	mainrenderer->Render();
}

void WeaponSheet::WeaponSheetActive()
{
	// 객체마다의 활성화/비활성화 여부 설정
	prevstate_ = active_;
	if (false == active_)
	{
		active_ = true;
	}
	else
	{
		active_ = false;
	}

	// 모든 무기아이콘 Active상태 설정
	std::map<std::string, WeaponIcon*>::iterator IconStart = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator IconEnd = weaponiconlist_.end();
	for (; IconStart != IconEnd; ++IconStart)
	{
		IconStart->second->SetActive(active_);
	}
}

void WeaponSheet::WeaponSheetTernOff()
{
	// 턴시간초과로 인한 턴전환시 강제로 무기창 및 무기아이콘리스트 위치 초기화
	forceternoff_ = true;

	prevstate_ = active_;
	active_ = false;

	// 모든 무기아이콘 Active상태 설정
	std::map<std::string, WeaponIcon*>::iterator IconStart = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator IconEnd = weaponiconlist_.end();
	for (; IconStart != IconEnd; ++IconStart)
	{
		IconStart->second->SetTernTimeOff();
	}

	// 위치 강제이동
	SetPos(disabletargetpos_);

	// Flag 초기화
	moving_ = false;
	forceternoff_ = false;
}

void WeaponSheet::SetRenderPos(const float4& _Active, const float4& _Disable)
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	activetargetpos_ = _Active;
	disabletargetpos_ = _Disable;

	SetPos(disabletargetpos_);

	// 마우스 제한된 위치이동 설정 및 마우스 생성
	SetMouseObject();
}

UIController* WeaponSheet::GetParentController() const
{
	return parentcontroller_;
}

void WeaponSheet::SetParentController(UIController* _controller)
{
	parentcontroller_ = _controller;
}

void WeaponSheet::SetMouseObject()
{
	// 마우스 저장
	float4 MouseRange = float4(activetargetpos_.x - (mainrenderer->GetImageSize().x * 0.5f), activetargetpos_.y - (mainrenderer->GetImageSize().y * 0.5f));
	mouseobject_ = dynamic_cast<MouseObject*>( GetLevel()->FindActor("PlayLevelMouse"));
	mouseobject_->SetMoveRange(MouseRange, MouseRange + mainrenderer->GetImageSize());
	mouseobject_->SetFinalPos(MouseRange); // 초기위치
	mouseobject_->SetPos(MouseRange);
}

void WeaponSheet::SetIconName()
{
	// Weapon Icon 이름목록을 생성한다
	weaponnamelist_.resize(static_cast<int>(eItemList::MAX));
	
	// Weapon Sheet Utile Line
	weaponnamelist_[0] = "jetpack";
	weaponnamelist_[1] = "gravity";
	weaponnamelist_[2] = "speed";
	weaponnamelist_[3] = "laser";
	weaponnamelist_[4] = "invisibl";

	// Weapon Sheet F1 Line
	weaponnamelist_[5] = "bazooka";
	weaponnamelist_[6] = "hmissile";
	weaponnamelist_[7] = "mortar";
	weaponnamelist_[8] = "pigeon";
	weaponnamelist_[9] = "launch";

	// Weapon Sheet F2 Line
	weaponnamelist_[10] = "grenade";
	weaponnamelist_[11] = "cluster";
	weaponnamelist_[12] = "banana";
	weaponnamelist_[13] = "axe";
	weaponnamelist_[14] = "quake";

	// Weapon Sheet F3 Line
	weaponnamelist_[15] = "shotgun";
	weaponnamelist_[16] = "handgun";
	weaponnamelist_[17] = "uzi";
	weaponnamelist_[18] = "minigun";
	weaponnamelist_[19] = "longbow";

	// Weapon Sheet F4 Line
	weaponnamelist_[20] = "firepnch";
	weaponnamelist_[21] = "dragball";
	weaponnamelist_[22] = "kamikaze";
	weaponnamelist_[23] = "suicide";
	weaponnamelist_[24] = "prod";

	// Weapon Sheet F5 Line
	weaponnamelist_[25] = "dynamite";
	weaponnamelist_[26] = "mine";
	weaponnamelist_[27] = "sheep";
	weaponnamelist_[28] = "aqua";
	weaponnamelist_[29] = "mole";

	// Weapon Sheet F6 Line
	weaponnamelist_[30] = "airstrke";
	weaponnamelist_[31] = "firestrk";
	weaponnamelist_[32] = "postal";
	weaponnamelist_[33] = "minestrk";
	weaponnamelist_[34] = "molestrk";

	// Weapon Sheet F7 Line
	weaponnamelist_[35] = "blwtorch";
	weaponnamelist_[36] = "drill";
	weaponnamelist_[37] = "girder";
	weaponnamelist_[38] = "baseball";
	weaponnamelist_[39] = "girders";

	// Weapon Sheet F8 Line
	weaponnamelist_[40] = "rope";
	weaponnamelist_[41] = "bungee";
	weaponnamelist_[42] = "parachut";
	weaponnamelist_[43] = "teleport";
	weaponnamelist_[44] = "scales";

	// Weapon Sheet F9 Line
	weaponnamelist_[45] = "sbanana";
	weaponnamelist_[46] = "hgrenade";
	weaponnamelist_[47] = "thrower";
	weaponnamelist_[48] = "tamborin";
	weaponnamelist_[49] = "mbbomb";

	// Weapon Sheet F10 Line
	weaponnamelist_[50] = "petrolbm";
	weaponnamelist_[51] = "skunk";
	weaponnamelist_[52] = "mingvase";
	weaponnamelist_[53] = "shpstrke";
	weaponnamelist_[54] = "carpet";

	// Weapon Sheet F11 Line
	weaponnamelist_[55] = "cow";
	weaponnamelist_[56] = "oldwoman";
	weaponnamelist_[57] = "donkey";
	weaponnamelist_[58] = "nuke";
	weaponnamelist_[59] = "armagedn";

	// Weapon Sheet F12 Line
	weaponnamelist_[60] = "skipgo";
	weaponnamelist_[61] = "surender";
	weaponnamelist_[62] = "select";
	weaponnamelist_[63] = "freeze";
	weaponnamelist_[64] = "bullet";
}

void WeaponSheet::CreateIconDefaultPos()
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	// Weapon Icon 이름 설정
	SetIconName();

	// Weapon Icon 목록을 생성한다
	int Count = 0;
	int Index = 0;
	for (int x = 0; x < static_cast<int>(weaponnamelist_.size()); ++x)
	{
		if (x % 5 == 0 && x != 0)
		{
			++Count;	// 5개 단위로 y값 변경
			Index = 0;	// y값 변경되면 인덱스 초기화
		}

		// 신규 아이템아이콘 생성하며 기본 Off상태로설정됨
		WeaponIcon* NewIcon = GetLevel()->CreateActor<WeaponIcon>();
		NewIcon->SetWeaponName(weaponnamelist_[x]);			// MainRender 생성
		NewIcon->SetParentSheet(this);												// 자신이 속한 WeaponSheet 저장
		NewIcon->SetWeaponType(static_cast<eItemList>(x));		// 무기타입설정
		NewIcon->SetWeaponIndex(Index, Count);							// 무기아이콘 인덱스 설정

		// Weapon Icon의 인덱스에따라 비활성/활성 위치 초기화
		float4 ActivePos = float4({ Resolution.x - 141.f + ((float)Index * 28.f) + (Index + 1), Resolution.y - 422.f + (Count * 28.f) + (Count + 1) }); // 활성화되었을때 위치계산
		float4 disEnablePos = ActivePos;
		disEnablePos.x = ActivePos.x + 200.f;
		NewIcon->SetWeaponRenderPos(disEnablePos, ActivePos);

		weaponiconlist_.insert(std::pair<std::string, WeaponIcon*>(weaponnamelist_[x], NewIcon));

		++Index;
	}
}

void WeaponSheet::CreateWeaponIconList(const std::vector<eItemList>& _WeaponList)
{
	std::vector<eItemList> ActiveWeapon = _WeaponList;
	size_t ActiveWeaponCnt = ActiveWeapon.size();
	for (size_t i = 0; i < ActiveWeaponCnt; ++i)
	{
		std::map<std::string, WeaponIcon*>::iterator StartIter = weaponiconlist_.begin();
		std::map<std::string, WeaponIcon*>::iterator EndIter = weaponiconlist_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			// 활성화된 무기의 타입이같고, 해당 무기아이콘이 비활성화상태라면
			if (ActiveWeapon[i] == StartIter->second->GetWeaponType() && false == StartIter->second->IsMainrendererOn())
			{
				// 해당 무기아이콘 활성화상태
				StartIter->second->SetMainRendererOn();

				// 실제 무기정보목록 생성(초기생성)
				// 아이템 개수는 일단 3개 고정
				Weapon* NewWeapon = new Weapon();
				NewWeapon->SetItemSpec(StartIter->first, ActiveWeapon[i], 3, true);
				weaponlist_.insert(std::pair<eItemList, Weapon*>(ActiveWeapon[i], NewWeapon));
			}
		}
	}
}

void WeaponSheet::AddWeapon(eItemList _Weapon)
{
	// 무기아이콘목록에 현재 추가되는 무기가 없다면 (일단 보류)
	// 현재 모든 무기아이콘목록이 디폴트로 저장되어있으므로
	// 새로운 무기가 추가되는것은 보류한다.
	// 단, 최초생성된 무기정보목록에는 없으나, 무기아이콘목록에
	// 존재하는 무기는 새로운무기가 아니므로 무기정보만을 생성한다.

	// 무기아이콘리스트에서 해당 무기 탐색
	bool search = false;
	std::map<std::string, WeaponIcon*>::iterator StartIter = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator EndIter = weaponiconlist_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// 동일한 무기아이콘이 있을때
		eItemList CurItemType = StartIter->second->GetWeaponType();
		if (_Weapon == CurItemType)
		{
			// 해당 무기아이콘이 비활성화상태라면
			if (false == StartIter->second->IsMainrendererOn())
			{
				// 아이콘 활성화
				StartIter->second->SetMainRendererOn();
			}

			// 해당 무기목록에서 해당 무기타입을 탐색
			std::map<eItemList, Weapon*>::iterator WeaponStart = weaponlist_.begin();
			std::map<eItemList, Weapon*>::iterator WeaponEnd = weaponlist_.end();
			for (; WeaponStart != WeaponEnd; ++WeaponStart)
			{
				if (_Weapon == WeaponStart->first)
				{
					WeaponStart->second->WeaponAdd();
					search = true;
					break;
				}
			}

			break;
		}
	}

	// 동일한 무기정보(weaponlist_)가 존재하지않다면 무기정보 생성
	if (false == search)
	{
		Weapon* NewWeaponInfo = new Weapon();
		NewWeaponInfo->SetItemSpec(weaponnamelist_[static_cast<int>(_Weapon)], _Weapon, 1, true);
		weaponlist_.insert(std::pair<eItemList, Weapon*>(_Weapon, NewWeaponInfo));
	}
}

void WeaponSheet::UseWeapon(eItemList _Weapon)
{
	// 무기아이콘리스트에서 해당 무기 탐색
	std::map<std::string, WeaponIcon*>::iterator StartIter = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator EndIter = weaponiconlist_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// 해당 무기아이콘이 이미 활성화상태일때
		eItemList CurWeaponType = StartIter->second->GetWeaponType();
		if (_Weapon == CurWeaponType && true == StartIter->second->IsMainrendererOn())
		{
			// 해당 아이콘에 속하는 무기정보 탐색하여 해당 무기정보 갱신
			// 단, 무기아이콘이 활성화되있는 경우만 사용할 수 있도록 설정된다.
			std::map<eItemList, Weapon*>::iterator WeaponStart = weaponlist_.begin();
			std::map<eItemList, Weapon*>::iterator WeaponEnd = weaponlist_.end();
			for (; WeaponStart != WeaponEnd; ++WeaponStart)
			{
				if (CurWeaponType == WeaponStart->first)
				{
					// 무기정보의 남은갯수 -1을 하고
					WeaponStart->second->WeaponUse();

					// 만약 해당 무기가 모두 사용되었다면
					// 무기아이콘을 비활성화한다.
					if (0 >= WeaponStart->second->GetWeaponRemainCount())
					{
						StartIter->second->SetMainRendererOff();
					}

					break;
				}
			}
		}
	}
}

Weapon* WeaponSheet::GetCurWeapon(eItemList _SearchWeapon)
{
	// 무기목록
	std::map<eItemList, Weapon*>::iterator StartIter = weaponlist_.begin();
	std::map<eItemList, Weapon*>::iterator EndIter = weaponlist_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (_SearchWeapon == StartIter->first)
		{
			return StartIter->second;
		}
	}

	return nullptr;
}

float4 WeaponSheet::GetSheetActivePos()
{
	return activetargetpos_;
}

float4 WeaponSheet::GetSheetDisablePos()
{
	return disabletargetpos_;
}

