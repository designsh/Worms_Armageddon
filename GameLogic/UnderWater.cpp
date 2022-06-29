#include "UnderWater.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
UnderWater::UnderWater() // default constructer 디폴트 생성자
	:mainSpriteRender_(nullptr)
{
}

UnderWater::~UnderWater() // default destructer 디폴트 소멸자
{

}

UnderWater::UnderWater(UnderWater&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	:mainSpriteRender_(nullptr)
{
}

void UnderWater::Start()
{
	mainSpriteRender_ = CreateRenderer("Under_Water");
	float4 imageSize = mainSpriteRender_->GetImageSize();
	mainSpriteRender_->SetPivotPos(imageSize.halffloat4());
}

void UnderWater::UpdateBefore()
{

}

void UnderWater::Update()
{
}

void UnderWater::UpdateAfter()
{
}


void UnderWater::Render()
{
	mainSpriteRender_->Render();
}

