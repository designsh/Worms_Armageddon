#include "TitleLevel.h"
#include "TitleImage.h"
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
TitleLevel::TitleLevel() // default constructer 디폴트 생성자
{

}

TitleLevel::~TitleLevel() // default destructer 디폴트 소멸자
{

}

TitleLevel::TitleLevel(TitleLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void TitleLevel::Loading()
{
	// 타이틀씬 액터 생성
	CreateActor<TitleImage>();

	if (false == GameEngineInput::GetInst().IsKey("Debug_Toggle"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Toggle", VK_TAB);
	}
}

void TitleLevel::LevelUpdate()
{
}