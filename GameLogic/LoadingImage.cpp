#include "LoadingImage.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineLevelManager.h>

LoadingImage::LoadingImage() // default constructer 디폴트 생성자
	:mainSpriteRender_(nullptr), backRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder((int)RenderOrder::Mouse);
	
}

LoadingImage::~LoadingImage() // default destructer 디폴트 소멸자
{

}

LoadingImage::LoadingImage(LoadingImage&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	:mainSpriteRender_(nullptr), backRender_(nullptr)
{

}

void LoadingImage::Start()
{
	backRender_ = CreateRenderer("Background");
	mainSpriteRender_ = CreateRenderer("LoadingSprites");
	mainSpriteRender_->CreateAnimation("Start", "LoadingSprites", 0, 24, false, 0.1f);
	mainSpriteRender_->ChangeAnimation("Start");
	mainSpriteRender_->SetCameraEffectOff();
	backRender_->SetCameraEffectOff();
}

void LoadingImage::UpdateBefore()
{

}

void LoadingImage::Update()
{
	// 로딩 애니메이션 마지막프레임이라면 씬 자동전환
	if (24 == mainSpriteRender_->GetCurAnimationFrame())
	{
		Off();
		// GameEngineLevelManager::GetInst().ChangeLevel("PlayLevel", true);
	}
}

void LoadingImage::UpdateAfter()
{
}


void LoadingImage::Render()
{
	if (true == IsOn())
	{
		backRender_->Render();
		mainSpriteRender_->AnimationUpdate();
	}

}
