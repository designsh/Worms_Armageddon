#include "WindController.h"
#include <GameEngineInput.h>
WindController::WindController() // default constructer 디폴트 생성자
	: windSpeed_(0.0f), fallSpeed_(0.0f), isDebugOn_(false), windDir_(WindDir::NONE)
{

}

WindController::~WindController() // default destructer 디폴트 소멸자
{

}

WindController::WindController(WindController&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: windSpeed_(0.0f), fallSpeed_(0.0f), isDebugOn_(false), windDir_(WindDir::NONE)
{

}

void WindController::SetWind(WindDir _windDir,float _windSpeed)
{
	windSpeed_ = randomGenerator_.RandomFloat(_windSpeed - 200.0f, _windSpeed + 200.0f);
	windDir_ = _windDir;
	
	switch (windDir_)
	{
	case WindDir::TOLEFT:
		windSpeed_ *= -1.0f;
		break;
	case WindDir::TORIGHT:
		break;
	case WindDir::NONE:
		break;
	default:
		break;
	}
	return;
}

void WindController::Start()
{
	if (false == GameEngineInput::GetInst().IsKey("WindToggle"))
	{
		GameEngineInput::GetInst().CreateKey("WindToggle", 'o');
	}
}
void WindController::UpdateBefore()
{

}
void WindController::Update() 
{
	if (true == GameEngineInput::GetInst().IsDown("WindToggle"))
	{
		if (true == isDebugOn_)
		{
			SetWind(WindDir::TOLEFT, 300.0f);
			isDebugOn_ = false;
			return;
		}
		isDebugOn_ = true;
		SetWind(WindDir::TORIGHT, 300.0f);
	}



}
void WindController::UpdateAfter()
{

}
void WindController::Render()
{

}