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
Uzi::Uzi() // default constructer ����Ʈ ������
{

}

Uzi::~Uzi() // default destructer ����Ʈ �Ҹ���
{

}

Uzi::Uzi(Uzi&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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

	if (0.05f <= deltaTime_) // �߻�ӵ� 0.2��
	{
		parentForward_ = parentWorm_->GetForward();
		UziBullet* curBullet = GetLevel()->CreateActor<UziBullet>(); // �Ѿ� 1�� ����
		curBullet->SetParentUzi(this);
		curBullet->SetPos(this->GetPos());
		curBullet->SetUziBulletShotBox(parentForward_);
		curBullet->StartFly();
	//	bulletList_.push_back(curBullet_);
		deltaTime_ = 0.0f; // �߻�ӵ� �ʱ�ȭ
		curShot_++;
	}
}

void Uzi::UpdateAfter()
{
}

void Uzi::Render()
{
}


