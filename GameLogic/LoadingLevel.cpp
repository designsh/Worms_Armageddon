#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include "LoadingLevel.h"
#include "LoadingImage.h"
LoadingLevel::LoadingLevel() // default constructer ����Ʈ ������
{

}

LoadingLevel::~LoadingLevel() // default destructer ����Ʈ �Ҹ���
{

}

LoadingLevel::LoadingLevel(LoadingLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void LoadingLevel::Loading()
{
	CreateActor<LoadingImage>();

}

void LoadingLevel::LevelUpdate()
{
}