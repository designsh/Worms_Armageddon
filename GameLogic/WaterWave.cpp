#include "WaterWave.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
WaterWave::WaterWave() // default constructer 디폴트 생성자
	:mainSpriteRender_(nullptr)
{
	//this->SetPos(float4(0.f,700.f,0.f));
	//SetRenderOrder(1);
}

WaterWave::~WaterWave() // default destructer 디폴트 소멸자
{

}

WaterWave::WaterWave(WaterWave&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	:mainSpriteRender_(nullptr)
{

}

void WaterWave::Start()
{
	mainSpriteRender_ = CreateRenderer("Water_sprite");
	float4 imageSize = mainSpriteRender_->GetImageSize();
	mainSpriteRender_->SetPivotPos(imageSize.halffloat4());
	mainSpriteRender_->CreateAnimation("Start", "Water_sprite", 0, 10, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Start");


}

void WaterWave::UpdateBefore()
{

}

void WaterWave::Update()
{
}

void WaterWave::UpdateAfter()
{
}


void WaterWave::Render()
{
	mainSpriteRender_->AnimationUpdate();
}

void WaterWave::SetAnimationCurrentFrame(const int _index)
{
	mainSpriteRender_->SetAnimationCurrentFrame(_index);
}
