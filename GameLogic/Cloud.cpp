#include "Cloud.h"
#include "WindController.h"
#include <GameEngineTime.h>
#include <GameEngineRenderer.h>	
#include <GameEngineMath.h>


Cloud::Cloud() // default constructer 디폴트 생성자
	: mainRender_(nullptr), spawnPos_({ randomGenerator_.RandomFloat(0.0f, 3000.0f), -300.0f }), cloudSpeed_(0.0f)
{

	SetRenderOrder((int)RenderOrder::BackGround1);
	SetPos({ randomGenerator_.RandomFloat(0.0f, 3000.0f), -300.0f });

}

Cloud::~Cloud() // default destructer 디폴트 소멸자
{

}

Cloud::Cloud(Cloud&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr), spawnPos_({ randomGenerator_.RandomFloat(0.0f, 3000.0f), -300.0f }), cloudSpeed_(0.0f)
{

}



void Cloud::Start()
{
	int diceRoll = randomGenerator_.RandomInt(0,2);

	switch (diceRoll)
	{
	case 0:
		mainRender_ = CreateRenderer("cloudl");
		mainRender_->CreateAnimation("cloudl", "cloudl", 0, 19, true, 0.033f);
		mainRender_->ChangeAnimation("cloudl");
		cloudSpeed_ = 25.0f;
		break;
	case 1:
		mainRender_ = CreateRenderer("cloudm");
		mainRender_->CreateAnimation("cloudm", "cloudm", 0, 19, true, 0.033f);
		mainRender_->ChangeAnimation("cloudm");
		cloudSpeed_ = 100.0f;
		break;
	case 2:
		mainRender_ = CreateRenderer("clouds");
		mainRender_->CreateAnimation("clouds", "clouds", 0, 19, true, 0.033f);
		mainRender_->ChangeAnimation("clouds");
		cloudSpeed_ = 150.0f;
		break;

	default:
		break;
	}
	spawnPos_.x = randomGenerator_.RandomFloat(0.0f, 3000.0f);
}

void Cloud::UpdateBefore()
{
}

void Cloud::Update()
{
	SetMove({(parent_->windSpeed_ + cloudSpeed_)* GameEngineTime::GetInst().GetDeltaTime(),0.0f});
}

void Cloud::UpdateAfter()
{
	if (this->GetPos().x < -1260.0f || this->GetPos().x > 3940.0f)
	{
		switch (parent_->windDir_)
		{
		case WindDir::TOLEFT:
			SetPos({ 3940.0f , -300.0f}); // 위치리셋
			break;
		case WindDir::TORIGHT:
			SetPos({ -1260.0f ,-300.0f }); // 위치리셋
			break;
		case WindDir::NONE:
			break;
		default:
			break;
		}


	}
}

void Cloud::Render()
{
	mainRender_->AnimationUpdate();
}