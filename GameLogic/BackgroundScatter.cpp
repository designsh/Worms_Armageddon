#include "BackgroundScatter.h"
#include "WindController.h"
#include <GameEngineTime.h>
#include <GameEngineRenderer.h>	
#include <GameEngineMath.h>

BackgroundScatter::BackgroundScatter() // default constructer 디폴트 생성자
: mainRender_(nullptr), spawnPos_({ randomGenerator_.RandomFloat(0.0f, 3000.0f), -300.0f })
{
	SetRenderOrder((int)RenderOrder::BackGround1);
	SetPos({ randomGenerator_.RandomFloat(-1280.0f, 1280.0f), randomGenerator_.RandomFloat(-720.0f, 720.0f) });
}

BackgroundScatter::~BackgroundScatter() // default destructer 디폴트 소멸자
{

}

BackgroundScatter::BackgroundScatter(BackgroundScatter&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr), spawnPos_({ randomGenerator_.RandomFloat(0.0f, 3000.0f), -300.0f })
{

}


void BackgroundScatter::Start()
{
	mainRender_ = CreateRenderer("ScatterLeaf");
	mainRender_->CreateAnimation("Type0", "ScatterLeaf",0,12,true,0.204f);
	mainRender_->ChangeAnimation("Type0");
	fallSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
	spawnPos_.x = randomGenerator_.RandomFloat(0.0f, 3000.0f);
}

void BackgroundScatter::UpdateBefore()
{
}

void BackgroundScatter::Update()
{
		SetMove({ parent_->windSpeed_ * GameEngineTime::GetInst().GetDeltaTime(), fallSpeed_ * GameEngineTime::GetInst().GetDeltaTime() });
}

void BackgroundScatter::UpdateAfter()
{
	if (this->GetPos().y > 1000.0f || this->GetPos().x < -1260.0f || this->GetPos().x > 3940.0f) // 수면보다 pos 가 낮아질 경우
	{
		switch (parent_->windDir_)
		{
		case WindDir::TOLEFT:
			SetPos({ randomGenerator_.RandomFloat(700.0f, 3000.0f) , spawnPos_.y }); // 위치리셋
			fallSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
			break;
		case WindDir::TORIGHT:
			SetPos({ randomGenerator_.RandomFloat(-800.0f, 1500.0f) , spawnPos_.y }); // 위치리셋
			fallSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
			break;
		case WindDir::NONE:
			SetPos({ randomGenerator_.RandomFloat(600.0f, 3000.0f) , spawnPos_.y }); // 위치리셋
			fallSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
			break;
		default:
			break;
		}


	}
}

void BackgroundScatter::Render()
{
	mainRender_->AnimationUpdate();
}