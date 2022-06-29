#include "PurpleStar.h"
#include "Effectkamismk.h"
#include <GameEngineTime.h>

PurpleStar::PurpleStar() :
	deltaTime_(0.f),
	LifeTime_(0.f),
	SpawnIntervalTime_(0.f)
{

}

PurpleStar::~PurpleStar() // default destructer ����Ʈ �Ҹ���
{

}

PurpleStar::PurpleStar(PurpleStar&& _other) noexcept :
	deltaTime_(0.f),
	LifeTime_(0.f),
	SpawnIntervalTime_(0.f)
{
}

void PurpleStar::Start()
{
}

void PurpleStar::UpdateBefore()
{
}

void PurpleStar::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();


	SpawnIntervalTime_ += deltaTime_;

	if (SpawnIntervalTime_ > 0.5f)
	{
		Effect::kamismk* effect = parentLevel_->CreateActor<Effect::kamismk>();
		effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect0));

		SpawnIntervalTime_ = 0.f;
	}

	LifeTime_ += deltaTime_;

	if (LifeTime_ > 4.f)
	{
		Death();
	}
}

void PurpleStar::UpdateAfter()
{
}

void PurpleStar::Render()
{
}
