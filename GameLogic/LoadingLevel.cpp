#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include "LoadingLevel.h"
#include "LoadingImage.h"
LoadingLevel::LoadingLevel() // default constructer 디폴트 생성자
{

}

LoadingLevel::~LoadingLevel() // default destructer 디폴트 소멸자
{

}

LoadingLevel::LoadingLevel(LoadingLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void LoadingLevel::Loading()
{
	CreateActor<LoadingImage>();

}

void LoadingLevel::LevelUpdate()
{
}