#include "WormName.h"
#include "Worm.h"
#include <GameEngineRenderer.h>
WormName::WormName() // default constructer 디폴트 생성자
	: isWormLinked_(false)
{
	SetRenderOrder(static_cast<int>(RenderOrder::Worm));
}

WormName::~WormName() // default destructer 디폴트 소멸자
{

}

WormName::WormName(WormName&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: isWormLinked_(false)
{

}

void WormName::Start()
{
	mainRender_ = CreateRenderer("WormName1");
	mainRender_->SetCameraEffectOn();
}

void WormName::UpdateBefore()
{

}

void WormName::Update()
{
	if (true == isWormLinked_)
	{
		SetPos({ parent_->GetPos().x, (parent_->GetPos().y - 50.0f) });
	}

}

void WormName::UpdateAfter()
{

}

void WormName::Render()
{
	mainRender_->Render();
}

void WormName::NameInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:
		mainRender_ = CreateRenderer("WormName1");
		break;
	case 1:
		mainRender_ = CreateRenderer("WormName2");
		break;
	case 2:
		mainRender_ = CreateRenderer("WormName3");
		break;
	case 3:
		mainRender_ = CreateRenderer("WormName4");
		break;
	case 4:
		mainRender_ = CreateRenderer("WormName5");
		break;
	case 5:
		mainRender_ = CreateRenderer("WormName6");
		break;
	case 6:
		mainRender_ = CreateRenderer("WormName1");
		break;
	case 7:
		mainRender_ = CreateRenderer("WormName1");
		break;
	default:
		mainRender_ = CreateRenderer("WormName1");
		break;
	}
}

void WormName::StartPosInit(int _wormNumber)
{


}