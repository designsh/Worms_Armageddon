#include "MenuSelectLevel.h"
#include "MenuSelBackDrop.h"
#include "MenuSelImage.h"
#include "MouseObject.h"
#include "WindController.h"
#include "BackgroundScatter.h"

#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include <GameEngineWindow.h>
#include <GameEngineImage.h>

MenuSelectLevel::MenuSelectLevel() // default constructer 디폴트 생성자
{

}

MenuSelectLevel::~MenuSelectLevel() // default destructer 디폴트 소멸자
{

}

MenuSelectLevel::MenuSelectLevel(MenuSelectLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void MenuSelectLevel::Loading()
{
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}

	CreateActor<MenuSelBackDrop>();
	CreateActor<MenuSelImage>();
	CreateActor<MouseObject>();

	WindController* windController_ = CreateActor<WindController>();
	windController_->SetWind(WindDir::TORIGHT, 400.f);
	for (int i = 0; i < 39; i++)
	{
		BackgroundScatter* newScatter = CreateActor<BackgroundScatter>();
		newScatter->SetParent(windController_);
	}
}

void MenuSelectLevel::LevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel", true);
	}
}

