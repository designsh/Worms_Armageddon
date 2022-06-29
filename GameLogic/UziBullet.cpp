#include "UziBullet.h"
#include "Uzi.h"
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>

#include "WindController.h"
#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"
#include "PlayLevel.h"
#include "Explosion.h"
#include "Worm.h"


UziBullet::UziBullet() // default constructer ����Ʈ ������
	: mainRender_(nullptr)
	, fireCollision_(nullptr)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
	, isFlying_(false)
{

}

UziBullet::~UziBullet() // default destructer ����Ʈ �Ҹ���
{

}

UziBullet::UziBullet(UziBullet&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr)
	, fireCollision_(nullptr)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
	, isFlying_(false)
{

}


void UziBullet::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);
	fireCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::WEAPON), CollisionCheckType::POINT);
	fireCollision_->SetPivot(float4::ZERO);
	fireCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
}

void UziBullet::UpdateBefore()
{

}

void UziBullet::Update()
{
	if (true == isFlying_)
	{
		deltaTime_ = 0.2f;
		if (0.2f <= deltaTime_)
		{
			if (nullptr == fireCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
			{ // ���� ��Ʈ���̰� ������ ������ �ʴ´ٸ�...
				PlayLevel* level = (PlayLevel*)GetLevel();
				SetMove(parentForward_ * 1000.0f);
			}

			if (nullptr != fireCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
			{
				PlayLevel* level = (PlayLevel*)GetLevel();
				level->CreateExplosion25({ pos_.x, pos_.y });
				deltaTime_ = 0.0f;
				Death();
			}
		}
	}
}

void UziBullet::UpdateAfter()
{
}

void UziBullet::Render()
{
}


