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

WeaponSheet::~WeaponSheet() // default destructer ����Ʈ �Ҹ���
{
	// ���� ������ ����
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
	// ������ ���� �� ī�޶��� ����
	SetRenderOrder(static_cast<int>(RenderOrder::UI2));
	mainrenderer = CreateRenderer("WeaponSheet");
	mainrenderer->SetCameraEffectOff();

	// ������ �⺻��ġ ���� �� �����ܾ��� ����
	CreateIconDefaultPos();
}

void WeaponSheet::UpdateBefore()
{

}

void WeaponSheet::Update()
{
	// ��򰡷κ��� Ű�Է½� Ȱ��ȭ/��Ȱ��ȭ
	if (true == active_) // ��Ȱ��ȭ -> Ȱ��ȭ
	{
		// ���� Ȱ��ȭ Ÿ����ġ���� �̵��ߴٸ� �ߴ�
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

		// ���콺Ŀ�� ��ġ ���� ��������
		// ������ Ŀ���� �ش� ������ ����� MAX������ �̵��ϵ��� ����
		float4 MousePos = GameEngineWindow::GetInst().GetMousePos();
		float4 LeftTop = activetargetpos_ - mainrenderer->GetImageSize().halffloat4();
		float4 RightBot = activetargetpos_ + mainrenderer->GetImageSize().halffloat4();
	}
	else if(true == prevstate_ && false == active_) // Ȱ��ȭ -> ��Ȱ��ȭ
	{
		// ��Ȱ���ÿ��� �ٷ� ���콺��ġ ���ڸ��ε�����.
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

		// ��Ȱ��ȭ�ÿ��� �ٷ� Off��Ŵ
		if (true == prevstate_)
		{
			mouseobject_->SetFinalPos(mouseobject_->GetPos());
		}
	}

	// �̵����� �ƴҶ� �������¿� ���� ���°� �ٸ��� ó��
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
	// ��ü������ Ȱ��ȭ/��Ȱ��ȭ ���� ����
	prevstate_ = active_;
	if (false == active_)
	{
		active_ = true;
	}
	else
	{
		active_ = false;
	}

	// ��� ��������� Active���� ����
	std::map<std::string, WeaponIcon*>::iterator IconStart = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator IconEnd = weaponiconlist_.end();
	for (; IconStart != IconEnd; ++IconStart)
	{
		IconStart->second->SetActive(active_);
	}
}

void WeaponSheet::WeaponSheetTernOff()
{
	// �Ͻð��ʰ��� ���� ����ȯ�� ������ ����â �� ��������ܸ���Ʈ ��ġ �ʱ�ȭ
	forceternoff_ = true;

	prevstate_ = active_;
	active_ = false;

	// ��� ��������� Active���� ����
	std::map<std::string, WeaponIcon*>::iterator IconStart = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator IconEnd = weaponiconlist_.end();
	for (; IconStart != IconEnd; ++IconStart)
	{
		IconStart->second->SetTernTimeOff();
	}

	// ��ġ �����̵�
	SetPos(disabletargetpos_);

	// Flag �ʱ�ȭ
	moving_ = false;
	forceternoff_ = false;
}

void WeaponSheet::SetRenderPos(const float4& _Active, const float4& _Disable)
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	activetargetpos_ = _Active;
	disabletargetpos_ = _Disable;

	SetPos(disabletargetpos_);

	// ���콺 ���ѵ� ��ġ�̵� ���� �� ���콺 ����
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
	// ���콺 ����
	float4 MouseRange = float4(activetargetpos_.x - (mainrenderer->GetImageSize().x * 0.5f), activetargetpos_.y - (mainrenderer->GetImageSize().y * 0.5f));
	mouseobject_ = dynamic_cast<MouseObject*>( GetLevel()->FindActor("PlayLevelMouse"));
	mouseobject_->SetMoveRange(MouseRange, MouseRange + mainrenderer->GetImageSize());
	mouseobject_->SetFinalPos(MouseRange); // �ʱ���ġ
	mouseobject_->SetPos(MouseRange);
}

void WeaponSheet::SetIconName()
{
	// Weapon Icon �̸������ �����Ѵ�
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

	// Weapon Icon �̸� ����
	SetIconName();

	// Weapon Icon ����� �����Ѵ�
	int Count = 0;
	int Index = 0;
	for (int x = 0; x < static_cast<int>(weaponnamelist_.size()); ++x)
	{
		if (x % 5 == 0 && x != 0)
		{
			++Count;	// 5�� ������ y�� ����
			Index = 0;	// y�� ����Ǹ� �ε��� �ʱ�ȭ
		}

		// �ű� �����۾����� �����ϸ� �⺻ Off���·μ�����
		WeaponIcon* NewIcon = GetLevel()->CreateActor<WeaponIcon>();
		NewIcon->SetWeaponName(weaponnamelist_[x]);			// MainRender ����
		NewIcon->SetParentSheet(this);												// �ڽ��� ���� WeaponSheet ����
		NewIcon->SetWeaponType(static_cast<eItemList>(x));		// ����Ÿ�Լ���
		NewIcon->SetWeaponIndex(Index, Count);							// ��������� �ε��� ����

		// Weapon Icon�� �ε��������� ��Ȱ��/Ȱ�� ��ġ �ʱ�ȭ
		float4 ActivePos = float4({ Resolution.x - 141.f + ((float)Index * 28.f) + (Index + 1), Resolution.y - 422.f + (Count * 28.f) + (Count + 1) }); // Ȱ��ȭ�Ǿ����� ��ġ���
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
			// Ȱ��ȭ�� ������ Ÿ���̰���, �ش� ����������� ��Ȱ��ȭ���¶��
			if (ActiveWeapon[i] == StartIter->second->GetWeaponType() && false == StartIter->second->IsMainrendererOn())
			{
				// �ش� ��������� Ȱ��ȭ����
				StartIter->second->SetMainRendererOn();

				// ���� ����������� ����(�ʱ����)
				// ������ ������ �ϴ� 3�� ����
				Weapon* NewWeapon = new Weapon();
				NewWeapon->SetItemSpec(StartIter->first, ActiveWeapon[i], 3, true);
				weaponlist_.insert(std::pair<eItemList, Weapon*>(ActiveWeapon[i], NewWeapon));
			}
		}
	}
}

void WeaponSheet::AddWeapon(eItemList _Weapon)
{
	// ��������ܸ�Ͽ� ���� �߰��Ǵ� ���Ⱑ ���ٸ� (�ϴ� ����)
	// ���� ��� ��������ܸ���� ����Ʈ�� ����Ǿ������Ƿ�
	// ���ο� ���Ⱑ �߰��Ǵ°��� �����Ѵ�.
	// ��, ���ʻ����� ����������Ͽ��� ������, ��������ܸ�Ͽ�
	// �����ϴ� ����� ���ο�Ⱑ �ƴϹǷ� ������������ �����Ѵ�.

	// ��������ܸ���Ʈ���� �ش� ���� Ž��
	bool search = false;
	std::map<std::string, WeaponIcon*>::iterator StartIter = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator EndIter = weaponiconlist_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// ������ ����������� ������
		eItemList CurItemType = StartIter->second->GetWeaponType();
		if (_Weapon == CurItemType)
		{
			// �ش� ����������� ��Ȱ��ȭ���¶��
			if (false == StartIter->second->IsMainrendererOn())
			{
				// ������ Ȱ��ȭ
				StartIter->second->SetMainRendererOn();
			}

			// �ش� �����Ͽ��� �ش� ����Ÿ���� Ž��
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

	// ������ ��������(weaponlist_)�� ���������ʴٸ� �������� ����
	if (false == search)
	{
		Weapon* NewWeaponInfo = new Weapon();
		NewWeaponInfo->SetItemSpec(weaponnamelist_[static_cast<int>(_Weapon)], _Weapon, 1, true);
		weaponlist_.insert(std::pair<eItemList, Weapon*>(_Weapon, NewWeaponInfo));
	}
}

void WeaponSheet::UseWeapon(eItemList _Weapon)
{
	// ��������ܸ���Ʈ���� �ش� ���� Ž��
	std::map<std::string, WeaponIcon*>::iterator StartIter = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator EndIter = weaponiconlist_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// �ش� ����������� �̹� Ȱ��ȭ�����϶�
		eItemList CurWeaponType = StartIter->second->GetWeaponType();
		if (_Weapon == CurWeaponType && true == StartIter->second->IsMainrendererOn())
		{
			// �ش� �����ܿ� ���ϴ� �������� Ž���Ͽ� �ش� �������� ����
			// ��, ����������� Ȱ��ȭ���ִ� ��츸 ����� �� �ֵ��� �����ȴ�.
			std::map<eItemList, Weapon*>::iterator WeaponStart = weaponlist_.begin();
			std::map<eItemList, Weapon*>::iterator WeaponEnd = weaponlist_.end();
			for (; WeaponStart != WeaponEnd; ++WeaponStart)
			{
				if (CurWeaponType == WeaponStart->first)
				{
					// ���������� �������� -1�� �ϰ�
					WeaponStart->second->WeaponUse();

					// ���� �ش� ���Ⱑ ��� ���Ǿ��ٸ�
					// ����������� ��Ȱ��ȭ�Ѵ�.
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
	// ������
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

