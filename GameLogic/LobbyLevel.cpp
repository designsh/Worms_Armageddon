#include "LobbyLevel.h"
#include "LobbyImage.h"
#include "LobbySelectMapImage.h"
#include "LobbyScatter.h"
#include "LobbyHost.h"
#include "ChattingInput.h"
#include "ChattingHistory.h"
#include "LobbyStartButton.h"
#include "LobbyExitButton.h"
#include "MouseObject.h"

// ������ ����
#include "LobbyCreateTeam.h"

// ���ӿɼǰ���
// ���ӿɼ�
#include "GameOptionInfo.h"

// �⺻
#include "LobbyTernTimeSet.h"
#include "LobbyRoundTimeSet.h"
#include "LobbyWinsreQuiredSet.h"
#include "LobbyWormSelectSet.h"
#include "LobbyWormEnergySet.h"
#include "LobbyTeleportinSet.h"

// ��
#include "GameOptionSet.h"

// ����
#include "WeaponOptionSet.h"

#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include <GameEngineWindow.h>
#include <GameEngineImage.h>

LobbyLevel::LobbyLevel() // default constructer ����Ʈ ������
{

}

LobbyLevel::~LobbyLevel() // default destructer ����Ʈ �Ҹ���
{
}

LobbyLevel::LobbyLevel(LobbyLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}


void LobbyLevel::Loading()
{
	// ����ȭ�� ��� �� �ʼ��� �̹���
	Loading_SJH();

	// ����ȭ�� �ε��� ���õ� �÷��̾��̸� ��� Ŭ����
	GameOptionInfo::CurPlayerName.clear();
}

void LobbyLevel::LevelUpdate()
{

}

void LobbyLevel::Loading_SJH()
{
	// �ε��ÿ� �ε��� ��� �̹��������� �̸��� üũ�Ͽ� MapSel* ���ν����ϴ� �̹��������̸� ��� ã�Ƽ�
	// LobbySelectMapImage ���Ϳ� �Ѱ��ش�.
	std::vector<std::string> ImageNameList = GameEngineImage::GetInst().FindAllSpecKeyImage("LobbyMap_");
	int CurMapIndex = 0;
	for (size_t i = 0; i < ImageNameList.size(); ++i)
	{
		// ù ���� LobbyMap_MapTrain �̹Ƿ� �ش� �ε����� ã�´�.
		if (ImageNameList[i] == "LobbyMap_MapTrain")
		{
			CurMapIndex = static_cast<int>(i);
			break;
		}
	}

	// �κ� ���콺 ���ʹ�ưŬ�� Ű ����
	// �⺻�ɼǸ޴��� �浹�� : �����ɼ����� �̵�
	// �غ���� �̹����� �浹�� : �غ�Ϸ�/�̿Ϸ� ����
	// �÷��̾�ø�ϰ� �浹�� : �÷��̾� ���ÿϷ�
	// ä���Է¹ڽ��� �浹�� : ä���Է¹ڽ� Ȱ��ȭ
	if (false == GameEngineInput::GetInst().IsKey("LobbyLevel_MouseLButton"))
	{
		GameEngineInput::GetInst().CreateKey("LobbyLevel_MouseLButton", VK_LBUTTON);
	}

	// �κ� ���콺 �����ʹ�ưŬ�� Ű ����
	// �ʼ��� �̹����� �浹�� : ������ ����
	// �ɼǸ޴��� �浹�� : �����ɼ����� �̵�
	if (false == GameEngineInput::GetInst().IsKey("LobbyLevel_MouseRButton"))
	{
		GameEngineInput::GetInst().CreateKey("LobbyLevel_MouseRButton", VK_RBUTTON);
	}

	float4 HalfResoultion = GameEngineWindow::GetInst().GetSize().halffloat4();

	// ���� ���
	CreateActor<LobbyImage>();

	// ���ǿ�����Ʈ(�ٶ�����)
	for (int i = 0; i < 39; i++)
	{
		LobbyScatter* newScatter = CreateActor<LobbyScatter>();
	}

	// �ʼ����̹���
	LobbySelectMapImage* SelectMapImage = CreateActor<LobbySelectMapImage>();
	SelectMapImage->SetPos({ HalfResoultion.x + 100.f, 20.f });
	SelectMapImage->CreateSelMapImageNameList(ImageNameList);
	SelectMapImage->SetCurMapIndex(CurMapIndex);

	// ä�ñ��
	CreateActor<ChattingHistory>(); // ä���̷�
	CreateActor<ChattingInput>(); // ä�� �Է�

	// �ɼǼ���(���ӿɼ�, ����ɼ�)
	CreateActor<GameOptionSet>();
	CreateActor<WeaponOptionSet>();

	// ���ӽ��� �� ���� ��ư
	CreateActor<LobbyStartButton>();
	CreateActor<LobbyExitButton>();

	// ȣ��Ʈ
	CreateActor<LobbyHost>();

	// �⺻���ӿɼ�
	CreateActor<LobbyTernTimeSet>();
	CreateActor<LobbyRoundTimeSet>();
	CreateActor<LobbyWinsreQuiredSet>();
	CreateActor<LobbyWormSelectSet>();
	CreateActor<LobbyWormEnergySet>();
	CreateActor<LobbyTeleportinSet>();

	// �� ����
	CreateActor<LobbyCreateTeam>();

	// ���콺
	CreateActor<MouseObject>();
}
