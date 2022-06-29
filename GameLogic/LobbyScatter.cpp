#include "LobbyScatter.h"
#include <GameEngineTime.h>
#include <GameEngineRenderer.h>	
#include <GameEngineMath.h>

LobbyScatter::LobbyScatter() // default constructer ����Ʈ ������
	: mainRender_(nullptr), spawnPos_({ randomGenerator_.RandomFloat(-700.0f, 700.0f), -100.0f })
{
	SetRenderOrder((int)RenderOrder::BackGround);
	SetPos({ randomGenerator_.RandomFloat(0.0f, 1280.0f), randomGenerator_.RandomFloat(0.0f, 720.0f) });
}

LobbyScatter::~LobbyScatter() // default destructer ����Ʈ �Ҹ���
{

}

LobbyScatter::LobbyScatter(LobbyScatter&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr), spawnPos_({ randomGenerator_.RandomFloat(0.0f, 3000.0f), -300.0f })
{

}


void LobbyScatter::Start()
{
	int diceRoll = randomGenerator_.RandomInt(0, 2);

	switch (diceRoll)
	{
	case 0:
		mainRender_ = CreateRenderer("ScatterStar");
		break;
	case 1:
		mainRender_ = CreateRenderer("ScatterStar1");
		break;
	case 2:
		mainRender_ = CreateRenderer("ScatterStar2");
		break;
	default:
		break;
	}
	
	windSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
	fallSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
	spawnPos_.x = randomGenerator_.RandomFloat(0.0f, 300.0f);
}

void LobbyScatter::UpdateBefore()
{
}

void LobbyScatter::Update()
{
	SetMove({ 200.0f * GameEngineTime::GetInst().GetDeltaTime(), fallSpeed_ * GameEngineTime::GetInst().GetDeltaTime() });
}

void LobbyScatter::UpdateAfter()
{
	if (this->GetPos().y > 800.0f || this->GetPos().x > 1300.0f) // Y�������� 800 �̳� X�������� 1300 �̻� ��� ���...
	{
			SetPos({ randomGenerator_.RandomFloat(-700.0f, 700.0f) , spawnPos_.y }); // ��ġ����
			fallSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
	}
}

void LobbyScatter::Render()
{
	mainRender_->Render();
}