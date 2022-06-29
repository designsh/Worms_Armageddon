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
#include "UziBullet.h"
Uzi::Uzi() // default constructer 디폴트 생성자
{

}

Uzi::~Uzi() // default destructer 디폴트 소멸자
{

}

Uzi::Uzi(Uzi&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



void Uzi::Start()
{
	deltaTime_ = 0.0f;

}

void Uzi::UpdateBefore()
{
	if (curShot_ == 25)
	{
		this->Death();
	}
}

void Uzi::Update()
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (0.05f <= deltaTime_) // 발사속도 0.2초
	{
		parentForward_ = parentWorm_->GetForward();
		UziBullet* curBullet = GetLevel()->CreateActor<UziBullet>(); // 총알 1발 생성
		curBullet->SetParentUzi(this);
		curBullet->SetPos(this->GetPos());
		curBullet->SetUziBulletShotBox(parentForward_);
		curBullet->StartFly();
	//	bulletList_.push_back(curBullet_);
		deltaTime_ = 0.0f; // 발사속도 초기화
		curShot_++;
	}
}

void Uzi::UpdateAfter()
{
}

void Uzi::Render()
{
}


