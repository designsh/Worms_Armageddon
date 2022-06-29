#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"
#include "PlayLevel.h"
#include "FirePunch.h"

FirePunch::FirePunch() // default constructer ����Ʈ ������
{

}

FirePunch::~FirePunch() // default destructer ����Ʈ �Ҹ���
{

}

FirePunch::FirePunch(FirePunch&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void FirePunch::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);
	mainRender_ = CreateRenderer("Bazooka");

	checkCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::WEAPON), CollisionCheckType::RECT);
	checkCollision_->SetSize({ 30.0f, 30.0f });
}

void FirePunch::UpdateBefore()
{

}

void FirePunch::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (nullptr != checkCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::PLAYER)))
	{
		
	}
}

void FirePunch::UpdateAfter()
{
	if (deltaTime_ > 3.0f)
	{
		this->Death();
	}
}

void FirePunch::Render()
{
	mainRender_->Render();
}
