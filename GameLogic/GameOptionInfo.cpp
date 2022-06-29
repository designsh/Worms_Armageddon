#include "GameOptionInfo.h"

//========================= Game Option ===========================//

// ���� �����ϴ� ������ �÷��̾� ��
// �ӽ� : �׽�Ʈ ���Ǹ� ���� �ʱⰪ 6���� ���� ���� 0���� ���濹��
int GameOptionInfo::CurWormCnt = 0;
//int GameOptionInfo::CurWormCnt = 6;

// ���� �����ϴ� ������ �÷��̾�� ���
std::vector<std::string> GameOptionInfo::CurPlayerName;

// ���� �����ϴ� ������ ��(�ʱⰪ ���� ����)
std::string GameOptionInfo::CurPlayMap = "MapTrain";

// ���� �����ϴ� ������ �浹��(�ʱⰪ ���� ����)
std::string GameOptionInfo::CurPlayColMap = "MapTrain_Ground";

// ���� �����ϴ� ���� ���� �ּ�/�ִ� ��ġ�����
std::unordered_map<std::string, float4> GameOptionInfo::MapMinMaxInfo = std::unordered_map<std::string, float4>();

//======================= Game Basic Option =======================//

// ��Ÿ��
// TernTime = ���Ѵ��̸� ����Ÿ������
float GameOptionInfo::TernTime = 45.f;

// ����Ÿ��
int GameOptionInfo::RoundTime = 15;

// �¸�����
int GameOptionInfo::WinSreuired = 2;

// Worm ��������
// WormSelect = 0 Off
// WormSelect = 1 On
// WormSelect = 2 Random
int GameOptionInfo::WormSelect = 0;

// Worm �⺻ü��
// WormEnergy = 50 ���Ѵ�(ü�¾���)
int GameOptionInfo::WormEnergy = 50;

// �ڷ���Ʈ On/Off
bool GameOptionInfo::Teleportin = false;

//======================= Game Basic Option =======================//


