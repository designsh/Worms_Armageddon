#include "Explosion.h"
#include "GameEngineLevel.h"

#include "eCollisionGroup.h"

#include <GameEngineCollision.h>
#include <GameEngineTime.h>
#include <typeinfo>

#include "Worm.h"
#include "PlayLevel.h"
#include "DrumActor.h"

#include "UIController.h"
#include "BottomStateUI.h"


Explosion::Explosion():
	Damage_(0),
	Life_(true),
	DamageToDist_(false),
	ExplosionCollision_(nullptr)
{
}

Explosion::~Explosion()
{
}

Explosion::Explosion(Explosion&& _other) noexcept :
	Damage_(0),
	Life_(false),
	DamageToDist_(false),
	ExplosionCollision_(nullptr)
{
}

void Explosion::Start()
{
	GameEngineSoundManager::GetInstance().PlaySoundByName("Explosion1.wav");
	ExplosionCollision_ = CreateCollision
	(static_cast<int>(eCollisionGroup::WEAPON), CollisionCheckType::CIRCLE);
}

void Explosion::UpdateBefore()
{
}

void Explosion::Update()
{	
	if (true == Life_)
	{
		std::list<GameEngineCollision*> ColList_ = ExplosionCollision_->CollisionGroupCheck(static_cast<int>(eCollisionGroup::PLAYER_HITBOX));

		if (false == ColList_.empty())
		{
			auto iter0 = ColList_.begin();
			auto iter1 = ColList_.end();

			for (; iter0 != iter1;)
			{
#ifdef _DEBUG
				std::string name = (*iter0)->GetActor()->GetName();
				name = name.substr(0, 4);

				if (name != "Worm")
				{
					GameEngineDebug::MsgBoxError("Worm이 아닌 충돌체가 eCollisionGroup::PLAYER로 설정되었습니다.");
				}
#endif // _DEBUG

				float4 Dir = (*iter0)->GetCollisionPoint() - pos_;
				Dir.Normalize2D();

				if (true == DamageToDist_)
				{
					float4 Wormpos = (*iter0)->GetCollisionPoint();
					float dist = pos_.DistanceTo(Wormpos);
					float size = ExplosionCollision_->GetSize().x/2;
					//dist = size - dist;

					// 중심 보정치
					dist-= 20;

					if (dist <= 0)
						dist = 1;
					//거리가 작을수록 데미지가 커져야함
					float Damage = Damage_ - ((dist / (size-20.f)) * Damage_);

					dynamic_cast<Worm*>((*iter0)->GetActor())->Damage(static_cast<int>(Damage), Dir);
				}

				else
				{
					dynamic_cast<Worm*>((*iter0)->GetActor())->Damage(static_cast<int>(Damage_), Dir);
				}

				++iter0;
			}
		}

		Life_ = false;
	}
	else
	{
		Death();
	}
}

void Explosion::UpdateAfter()
{
}

void Explosion::Render()
{
#ifdef _DEBUG
	if (GetLevel<PlayLevel>()->GetDebug())
	{
		ExplosionCollision_->DebugRender();
	}
#endif // DEBUG
}

