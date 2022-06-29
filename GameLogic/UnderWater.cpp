#include "UnderWater.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
UnderWater::UnderWater() // default constructer ����Ʈ ������
	:mainSpriteRender_(nullptr)
{
}

UnderWater::~UnderWater() // default destructer ����Ʈ �Ҹ���
{

}

UnderWater::UnderWater(UnderWater&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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

