#include "WindBar.h"
#include <GameEngineRenderer.h>
#include "WindController.h"

WindBar::WindBar() // default constructer 디폴트 생성자
	: originalSizeX_(87.0f)
{
	SetRenderOrder((int)RenderOrder::UI1);
}

WindBar::~WindBar() // default destructer 디폴트 소멸자
{

}

WindBar::WindBar(WindBar&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: originalSizeX_(87.0f)
{

}

void WindBar::Start()
{
	mainRender_ = CreateRenderer("windBar");
	mainRender_->CreateAnimation("windToLeft", "windBar", 0, 7, true, 0.051f);
	mainRender_->CreateAnimation("windToRight", "windBar", 8, 15, true, 0.051f);
	mainRender_->CreateAnimation("default", "windBar", 18,18, false, 0.102f);
	mainRender_->ChangeAnimation("default");
	mainRender_->SetCameraEffectOff();

}
void WindBar::UpdateBefore()
{

}
void WindBar::Update()
{
	WindBarUpdate();
}
void WindBar::UpdateAfter()
{

}
void WindBar::Render()
{
	mainRender_->AnimationUpdate();
}

void WindBar::WindBarUpdate()
{
	switch (parentController_->windDir_)
	{
	case WindDir::TOLEFT:
	{
		mainRender_->ChangeAnimation("windToLeft");
		float curWindSpeed = parentController_->GetCurrentWindSpeed(); // 현재 풍속 받기 (-500~0)
		float fixedWindSpeed = -1 * curWindSpeed / 500.0f;
		this->SetPos({ 1135 + (100 - fixedWindSpeed * 100), 700 });
		break;
	}
	case WindDir::TORIGHT:
	{
		mainRender_->ChangeAnimation("windToRight");
		float curWindSpeed = parentController_->GetCurrentWindSpeed(); // 현재 풍속 받기 (0~ 500)
		float fixedWindSpeed = curWindSpeed / 500.0f;
		this->SetPos({ 1225 - (100 - fixedWindSpeed * 100), 700 });
		break;
	}
	case WindDir::NONE:
	{
		SetPos({ 1180,700 });
		mainRender_->ChangeAnimation("default");
		break;
	}

	default:
		break;
	}

}