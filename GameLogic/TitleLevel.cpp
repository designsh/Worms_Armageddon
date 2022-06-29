#include "TitleLevel.h"
#include "TitleImage.h"
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
TitleLevel::TitleLevel() // default constructer ����Ʈ ������
{

}

TitleLevel::~TitleLevel() // default destructer ����Ʈ �Ҹ���
{

}

TitleLevel::TitleLevel(TitleLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void TitleLevel::Loading()
{
	// Ÿ��Ʋ�� ���� ����
	CreateActor<TitleImage>();

	if (false == GameEngineInput::GetInst().IsKey("Debug_Toggle"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Toggle", VK_TAB);
	}
}

void TitleLevel::LevelUpdate()
{
}