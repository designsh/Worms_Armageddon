#include "WaterLevel.h"
#include "WaterWave.h"
#include "UnderWater.h"
#include "GameOptionInfo.h"

#include <GameEngineTime.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>

#define MOVE_SPEED 800.f

WaterLevel::WaterLevel() // default constructer ����Ʈ ������
	:mainSpriteRender_(nullptr),
	roundtimechk_(false),
	waterincreasetime_(0.f),
	waterincreaserange_(800.f)
{
}

WaterLevel::~WaterLevel() // default destructer ����Ʈ �Ҹ���
{

}

WaterLevel::WaterLevel(WaterLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	:mainSpriteRender_(nullptr),
	roundtimechk_(_other.roundtimechk_),
	waterincreasetime_(_other.waterincreasetime_),
	waterincreaserange_(_other.waterincreaserange_)
{
}

void WaterLevel::WaterLevelUp(float deltaTime)
{
	auto iterfirst = Waterlist.begin();
	auto iterEnd = Waterlist.end();

	for (; iterfirst != iterEnd; iterfirst++)
	{
		(*iterfirst)->SetMove(float4::UP * waterincreaserange_ * deltaTime);
	}
	pos_.y -= (waterincreaserange_ * deltaTime);
}

void WaterLevel::WaterLevelDown(float deltaTime)
{
	auto iterfirst = Waterlist.begin();
	auto iterEnd = Waterlist.end();

	for (; iterfirst != iterEnd; iterfirst++)
	{
		(*iterfirst)->SetMove(float4::DOWN * waterincreaserange_ * deltaTime);
	}
	pos_.y += (waterincreaserange_ * deltaTime);
}

void WaterLevel::TernChangeWaterLevelUp()
{
	if (true == roundtimechk_)
	{
		float deltaTime = GameEngineTime::GetInst().GetDeltaTime();

		auto iterfirst = Waterlist.begin();
		auto iterEnd = Waterlist.end();
		for (; iterfirst != iterEnd; iterfirst++)
		{
			(*iterfirst)->SetMove(float4::UP * waterincreaserange_ * deltaTime);
		}
		pos_.y -= (waterincreaserange_ * deltaTime);
	}
}

void WaterLevel::SetWaterIncreaseRange(float _Range)
{
	// ������ ��¼ӵ� ����
	waterincreaserange_ = _Range;
}

void WaterLevel::Start()
{
}

void WaterLevel::UpdateBefore()
{
	// �κ�ȭ���� ����Ÿ���� üũ
	if (false == roundtimechk_)
	{
		// ������ �ð��� �ʰ��ϸ� ������ �ڵ���� On
		waterincreasetime_ += GameEngineTime::GetInst().GetDeltaTime();
		float RoundTime = GameOptionInfo::RoundTime * 60.f; // ����Ÿ���� ������ �����ǹǷ� �ʷ� ��ȯ
		if (waterincreasetime_ >= RoundTime)
		{
			roundtimechk_ = true;
			waterincreasetime_ = 0.f;
		}
	}
}

void WaterLevel::Update()
{
	float deltaTime = GameEngineTime::GetInst().GetDeltaTime();

	// �׽�Ʈ �ڵ�
	{
		//if (true == GameEngineInput::GetInst().IsPress("TestWaterLevelUp"))
		//{
		//	WaterLevelUp(deltaTime);
		//}
		//if (true == GameEngineInput::GetInst().IsPress("TestWaterLevelDown"))
		//{
		//	WaterLevelDown(deltaTime);
		//}
	}
}

void WaterLevel::UpdateAfter()
{
}


void WaterLevel::Render()
{
	//mainSpriteRender_->Render();
}

