#include "WormArrow.h"
#include <GameEngineRenderer.h>
#include "Worm.h"
#include <GameEngineTime.h>
#include <GameEngineInput.h>
WormArrow::WormArrow() // default constructer 디폴트 생성자
{
	
}

WormArrow::~WormArrow() // default destructer 디폴트 소멸자
{

}

WormArrow::WormArrow(WormArrow&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{
	SetRenderOrder(static_cast<int>(RenderOrder::Worm));
}

void WormArrow::Start()
{
}
void WormArrow::UpdateBefore()
{

}
void WormArrow::Update()
{
	if (true == isWormLinked_)
	{
		if (true == parent_->isFocused())
		{
			SetPos({ parent_->GetPos().x, (parent_->GetPos().y - 100.0f) });
			SetRenderOrder(static_cast<int>(RenderOrder::Worm));
		}

		if (false == parent_->isFocused())
		{
			SetMove(float4::UP * 600.0f * GameEngineTime::GetInst().GetDeltaTime());
		}
	}
}

void WormArrow::UpdateAfter()
{
	if (-500.0f >= GetPos().y)
	{
		SetRenderOrder(0);
	}
}

void WormArrow::Render()
{
	if (true == isWormLinked_)
	{
		mainRender_->AnimationUpdate();
	}


}


void WormArrow::ColorInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:

		mainRender_ = CreateRenderer("arrowdnr");
		mainRender_->CreateAnimation("arrowdnr", "arrowdnr", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdnr");
		break;
	case 1:
		mainRender_ = CreateRenderer("arrowdnb");
		mainRender_->CreateAnimation("arrowdnb", "arrowdnb", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdnb");
		break;
	case 2:
		mainRender_ = CreateRenderer("arrowdng");
		mainRender_->CreateAnimation("arrowdng", "arrowdng", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdng");
		break;
	case 3:
		mainRender_ = CreateRenderer("arrowdny");
		mainRender_->CreateAnimation("arrowdny", "arrowdny", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdny");
		break;
	case 4:
		mainRender_ = CreateRenderer("arrowdnp");
		mainRender_->CreateAnimation("arrowdnp", "arrowdnp", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdnp");
		break;
	case 5:
		mainRender_ = CreateRenderer("arrowdnc");
		mainRender_->CreateAnimation("arrowdnc", "arrowdnc", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdnc");
		break;
	case 6:

		mainRender_ = CreateRenderer("arrowdnr");
		mainRender_->CreateAnimation("arrowdnr", "arrowdnr", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdnr");
		break;
	case 7:

		mainRender_ = CreateRenderer("arrowdnr");
		mainRender_->CreateAnimation("arrowdnr", "arrowdnr", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdnr");
		break;
	default:

		mainRender_ = CreateRenderer("arrowdnr");
		mainRender_->CreateAnimation("arrowdnr", "arrowdnr", 0, 29, true, 0.022f);
		mainRender_->ChangeAnimation("arrowdnr");
		break;
	}
}