#include "WeaponIcon.h"
#include "WeaponSheet.h"
#include "eCollisionGroup.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <EngineEnum.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

WeaponIcon::WeaponIcon() :
	parentsheet_(nullptr),
	indexX_(-1),
	indexY_(-1),
	active_(false),
	prevstate_(false),
	weapontype_(eItemList::MAX),
	activetargetpos_(float4::ZERO),
	disabletargetpos_(float4::ZERO),
	moving_(false),
	movingspeed(2.f),
	movepos_(float4::ZERO),
	mainrenderer_(nullptr),
	selectrenderer_(nullptr),
	maincollision_(nullptr)
{
}

WeaponIcon::~WeaponIcon() // default destructer ����Ʈ �Ҹ���
{

}

WeaponIcon::WeaponIcon(WeaponIcon&& _other) noexcept :
	parentsheet_(_other.parentsheet_),
	indexX_(_other.indexX_),
	indexY_(_other.indexY_),
	active_(_other.active_),
	prevstate_(_other.prevstate_),
	weapontype_(_other.weapontype_),
	activetargetpos_(_other.activetargetpos_),
	disabletargetpos_(_other.disabletargetpos_),
	moving_(_other.moving_),
	movingspeed(_other.movingspeed),
	movepos_(_other.movepos_),
	mainrenderer_(_other.mainrenderer_),
	selectrenderer_(_other.selectrenderer_),
	maincollision_(_other.maincollision_)
{
}

void WeaponIcon::SetWeaponName(const std::string& _Name)
{
	// �̸��� �����ɶ� ��������ü�� ����
	weaponname_ = _Name;
	SetName(_Name);

	// �ش� ���� ���� ��Ȱ��ȭ���·� ����
	if (nullptr == mainrenderer_)
	{
		SetRenderOrder(static_cast<int>(RenderOrder::UI3));
		mainrenderer_ = CreateRenderer(weaponname_);
		mainrenderer_->SetRenderSize({ 28.f, 28.f });
		mainrenderer_->SetCameraEffectOff();
		mainrenderer_->Off();
	}
}

void WeaponIcon::SetWeaponType(eItemList _Type)
{
	weapontype_ = _Type;
}

void WeaponIcon::SetWeaponRenderPos(const float4& _DisableRenderPos, const float4& _ActiveRenderPos)
{
	disabletargetpos_ = _DisableRenderPos;
	activetargetpos_ = _ActiveRenderPos;

	// �ʱ���ġ(��Ȱ��ȭ)
	SetPos(disabletargetpos_);
}

void WeaponIcon::SetWeaponIndex(int _X, int _Y)
{
	if (0 > _X)
	{
		return;
	}
	indexX_ = _X;

	if (0 > _Y)
	{
		return;
	}
	indexY_ = _Y;
}

GameEngineCollision* WeaponIcon::GetCurIconCol() const
{
	return maincollision_;
}

eItemList WeaponIcon::GetWeaponType() const
{
	return weapontype_;
}

const std::string& WeaponIcon::GetWeaponName() const
{
	return weaponname_;
}

WeaponSheet* WeaponIcon::GetParentSheet() const
{
	return parentsheet_;
}

void WeaponIcon::SetParentSheet(WeaponSheet* _Sheet)
{
	parentsheet_ = _Sheet;
}

void WeaponIcon::SetActive(bool _Active)
{
	prevstate_ = active_;
	active_ = _Active;
}

void WeaponIcon::SelWeapon()
{
	// ���� ���콺�� �浹�� ���⼱�ùڽ� Ȱ��ȭ
	selectrenderer_->On();
}

void WeaponIcon::SetMainRendererOn()
{
	mainrenderer_->On();
}

void WeaponIcon::SetMainRendererOff()
{
	mainrenderer_->Off();
}

bool WeaponIcon::IsMainrendererOn()
{
	return mainrenderer_->IsOn();
}

void WeaponIcon::SetTernTimeOff()
{
	SetPos(disabletargetpos_);

	prevstate_ = active_;
	active_ = false;
	moving_ = false;
}

void WeaponIcon::Start()
{
	// ���÷����� ����
	selectrenderer_ = CreateRenderer("WeaponSelector");
	selectrenderer_->SetRenderSize({ 26.f, 26.f });
	selectrenderer_->SetImagePivot({ 15.f, 15.f });
	selectrenderer_->SetCameraEffectOff();
	selectrenderer_->Off();

	// �浹ü ����
	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize({ 26.f, 26.f });
}

void WeaponIcon::UpdateBefore()
{
	// ���콺�� �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		selectrenderer_->On();
	}
	else
	{
		selectrenderer_->Off();
	}
}

void WeaponIcon::Update()
{
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
		}
	}
	else if(true == prevstate_ && false == active_) // Ȱ��ȭ -> ��Ȱ��ȭ
	{
		if (disabletargetpos_.x >= GetPos().x)
		{
			movepos_ += float4::RIGHT * GameEngineTime::GetInst().GetDeltaTime();
			SetMove(movepos_ * movingspeed);

			moving_ = true;
		}
		else
		{
			moving_ = false;
		}
	}

	if (false == moving_)
	{
		movepos_ = float4::ZERO;
	}
}

void WeaponIcon::UpdateAfter()
{
}

void WeaponIcon::Render()
{
	// ���콺�� �浹�������� ���û��� ������
	if (nullptr != selectrenderer_)
	{
		// ���û��ڴ� �ʱ� off����
		if (true == selectrenderer_->IsOn())
		{
			selectrenderer_->Render();
		}
	}

	if (nullptr != mainrenderer_)
	{
		// �ӽ��ּ� : �����۾������� �⺻�� off���·� ��������
		if (true == mainrenderer_->IsOn())
		{
			mainrenderer_->Render();
		}
	}
}

