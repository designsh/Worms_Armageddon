#include "WindBarHider.h"
#include <GameEngineRenderer.h>
#include "WindController.h"
WindBarHider::WindBarHider() // default constructer 디폴트 생성자
{
	SetRenderOrder((int)RenderOrder::UI2);
}

WindBarHider::~WindBarHider() // default destructer 디폴트 소멸자
{

}

WindBarHider::WindBarHider(WindBarHider&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void WindBarHider::WindBarUpdate()
{
	switch (parentController_->windDir_)
	{
	case WindDir::TOLEFT:
	{
		this->SetPos({ 1223, 700 });
		break;
	}
	case WindDir::TORIGHT:
	{
		this->SetPos({ 1137 , 700 });
		break;
	}
	case WindDir::NONE:
	{
		SetPos({ 1180,700 });
		break;
	}

	default:
		break;
	}

}
void WindBarHider::Start()
{
	mainRender_ = CreateRenderer("windBarHider");
	mainRender_->SetCameraEffectOff();
}
void WindBarHider::UpdateBefore()
{

}
void WindBarHider::Update()
{
	WindBarUpdate();
}
void WindBarHider::UpdateAfter()
{

}
void WindBarHider::Render()
{
	mainRender_->Render();
}