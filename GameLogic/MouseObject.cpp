#include "MouseObject.h"
#include "eCollisionGroup.h"
#include "GameController.h"
#include "Worm.h"
#include "UIController.h"
#include "WeaponSheet.h"
#include "WeaponIcon.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <EngineEnum.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>
#include <GameEngineInput.h>

MouseObject::MouseObject() :
	mainrenderer_(nullptr),
	mouseAimRenderer_(nullptr),
	maincollision_(nullptr),
	gamecontroller_(nullptr),
	weaponsheeton_(false),
	finalpos_(float4::ZERO),
	startrange_(float4::ZERO),
	endrange_(float4::ZERO),
	mouseMoveBlock(false)
{
}

MouseObject::~MouseObject() // default destructer 디폴트 소멸자
{

}

MouseObject::MouseObject(MouseObject&& _other) noexcept :
	mainrenderer_(_other.mainrenderer_),
	mouseAimRenderer_(_other.mouseAimRenderer_),
	maincollision_(_other.maincollision_),
	gamecontroller_(_other.gamecontroller_),
	weaponsheeton_(_other.weaponsheeton_),
	finalpos_(_other.finalpos_),
	startrange_(_other.startrange_),
	endrange_(_other.endrange_),
	mouseMoveBlock(_other.mouseMoveBlock)
{

}

GameEngineCollision* MouseObject::GetMouseCol()
{
	return maincollision_;
}

void MouseObject::SetMoveRange(const float4& _Start, const float4& _End)
{
	startrange_ = _Start;
	endrange_ = _End;
}

void MouseObject::SetFinalPos(const float4& _FinalPos)
{
	finalpos_ = _FinalPos;
}

void MouseObject::MoveMousePos(bool _Flag)
{
	if (true == _Flag)
	{
		int x = finalpos_.ix();
		int y = finalpos_.iy();

		GameEngineWindow::GetInst().SetMousePos(x, y);
	}
}

void MouseObject::MouseBlock(bool _bool)
{
	mouseMoveBlock = _bool;

	mouseAimRenderer_->ChangeAnimation("mouseAim", std::string("markerr.bmp"));
	mouseAimRenderer_->SetPivotPos(GetLevel()->GetCamPos());
}

void MouseObject::SetGameController(GameController* _MainController)
{
	gamecontroller_ = _MainController;
}

void MouseObject::Start()
{
	// 마우스 커서생성
	SetRenderOrder(static_cast<int>(RenderOrder::Mouse));
	mainrenderer_ = CreateRenderer("Cursor");
	mainrenderer_->SetRenderSize(float4(32.f, 32.f));
	mainrenderer_->SetCameraEffectOff();

	mouseAimRenderer_ = CreateRenderer("markerr.bmp");
	mouseAimRenderer_->CreateAnimation("mouseAim", "markerr.bmp", 0, 9, true, 0.03f);

	float4 HarfIamgeSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(HarfIamgeSize);

	// 마우스 충돌체 생성
	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::MOUSE), CollisionCheckType::POINT);
	rendersize_ = mainrenderer_->GetImageSize();

	// 마우스 커서 off
	ShowCursor(false);

	if (false == GameEngineInput::GetInst().IsKey("Select_Weapon"))
	{
		GameEngineInput::GetInst().CreateKey("Select_Weapon", VK_LBUTTON);
	}
}

void MouseObject::UpdateBefore()
{
	// 무기창 활성화되었을때 무기아이콘과 충돌상태일때
	// 마우스왼쪽버튼 클릭시 해당 무기 선택으로판단하여 현재채택무기를 변경하고
	// 무기창을 비활성화시킨다.
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::UI));
	if (nullptr != ColUI)
	{
		WeaponIcon* CollisionWeapon = dynamic_cast<WeaponIcon*>(ColUI->GetActor());
		if (nullptr != CollisionWeapon)
		{
			// 마우스왼쪽버튼클릭이라면
			if (true == GameEngineInput::GetInst().IsDown("Select_Weapon"))
			{
				if (true == CollisionWeapon->GetParentSheet()->IsActive())
				{
					Worm* CurPlayer = CollisionWeapon->GetParentSheet()->GetParentController()->GetCurPlayer();
					if (nullptr != CurPlayer)
					{
						// 현재 충돌한 아이콘이 활성화 상태일때만 선택가능
						if (true == CollisionWeapon->IsMainrendererOn())
						{
							// 현재 플레이어 현재무기 변경
							CurPlayer->SetCurWeapon(CollisionWeapon->GetWeaponType());

							// 현재 플레이어의 무기창 비활성화
							CurPlayer->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetActive();
						}
					}
				}
			}
		}
	}
}

void MouseObject::Update()
{
	//// 위치 갱신(단, 이동범위를 벗어나면 갱신안함)
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();

	//// 현재 플레이어의 무기창이 활성화 상태라면 지정된범위 밖으로 커서 이동불가
	//// 현재 플레이어의 무기창이 비활성화 상태라면 자유롭게 이동
	//if (nullptr != gamecontroller_)
	//{
	//	// 현재 플레이어 Get
	//	Worm* CurPlayer = gamecontroller_->GetCurWorm();
	//	if (nullptr != CurPlayer)
	//	{
	//		if (true == CurPlayer->GetCurUIController()->GetCurWeaponSheet()->IsActive())
	//		{
	//			weaponsheeton_ = true;
	//		}
	//		else
	//		{
	//			weaponsheeton_ = false;
	//		}
	//	}
	//}

	//if (true == weaponsheeton_)
	//{
	//	// 범위지정이 되있다면
	//	if (MousePos.x >= startrange_.x && MousePos.x <= endrange_.x &&
	//		MousePos.y >= startrange_.y && MousePos.y <= endrange_.y)
	//	{
	//		SetPos(MousePos);
	//	}

	//	if (MousePos.y <= startrange_.y)
	//	{
	//		if (MousePos.x <= startrange_.x)
	//		{
	//			SetPos(float4(startrange_.x, startrange_.y));
	//		}
	//		else if (MousePos.x >= endrange_.x)
	//		{
	//			SetPos(float4(endrange_.x, endrange_.y));
	//		}
	//		else
	//		{
	//			SetPos(float4(MousePos.x, startrange_.y));
	//		}
	//	}

	//	if (MousePos.y >= endrange_.y)
	//	{
	//		if (MousePos.x <= startrange_.x)
	//		{
	//			SetPos(float4(startrange_.x, endrange_.y));
	//		}
	//		else if (MousePos.x >= endrange_.x)
	//		{
	//			SetPos(float4(endrange_.x, endrange_.y));
	//		}
	//		else
	//		{
	//			SetPos(float4(MousePos.x, endrange_.y));
	//		}
	//	}

	//	if (MousePos.x <= startrange_.x)
	//	{
	//		if (MousePos.y <= startrange_.y)
	//		{
	//			SetPos(float4(startrange_.x, startrange_.y));
	//		}
	//		else if (MousePos.y >= endrange_.y)
	//		{
	//			SetPos(float4(startrange_.x, endrange_.y));
	//		}
	//		else
	//		{
	//			SetPos(float4(startrange_.x, MousePos.y));
	//		}
	//	}

	//	if (MousePos.x >= endrange_.x)
	//	{
	//		if (MousePos.y <= startrange_.y)
	//		{
	//			SetPos(float4(endrange_.x, startrange_.y));
	//		}
	//		else if (MousePos.y >= endrange_.y)
	//		{
	//			SetPos(float4(endrange_.x, endrange_.y));
	//		}
	//		else
	//		{
	//			SetPos(float4(endrange_.x, MousePos.y));
	//		}
	//	}
	//}
	//else
	//{
	//	SetPos(MousePos);
	//}

	if (false == mouseMoveBlock)
	{
		SetPos(MousePos);
	}
}

void MouseObject::UpdateAfter()
{

}

void MouseObject::Render()
{
	if (false == mouseMoveBlock)
	{
		mainrenderer_->Render();
	}
	else
	{
		mouseAimRenderer_->AnimationUpdate();
	}
}
