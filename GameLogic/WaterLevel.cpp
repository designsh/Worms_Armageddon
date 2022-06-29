#include "WaterLevel.h"
#include "WaterWave.h"
#include "UnderWater.h"
#include "GameOptionInfo.h"

#include <GameEngineTime.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>

#define MOVE_SPEED 800.f

WaterLevel::WaterLevel() // default constructer 디폴트 생성자
	:mainSpriteRender_(nullptr),
	roundtimechk_(false),
	waterincreasetime_(0.f),
	waterincreaserange_(800.f)
{
}

WaterLevel::~WaterLevel() // default destructer 디폴트 소멸자
{

}

WaterLevel::WaterLevel(WaterLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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
	// 물높이 상승속도 세팅
	waterincreaserange_ = _Range;
}

void WaterLevel::Start()
{
}

void WaterLevel::UpdateBefore()
{
	// 로비화면의 라운드타임을 체크
	if (false == roundtimechk_)
	{
		// 설정한 시간이 초과하면 물높이 자동상승 On
		waterincreasetime_ += GameEngineTime::GetInst().GetDeltaTime();
		float RoundTime = GameOptionInfo::RoundTime * 60.f; // 라운드타임은 분으로 설정되므로 초로 변환
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

	// 테스트 코드
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

