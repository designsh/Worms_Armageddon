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

MenuSelectLevel::MenuSelectLevel() // default constructer ����Ʈ ������
{

}

MenuSelectLevel::~MenuSelectLevel() // default destructer ����Ʈ �Ҹ���
{

}

MenuSelectLevel::MenuSelectLevel(MenuSelectLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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

