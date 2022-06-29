#include "GameOptionInfo.h"

//========================= Game Option ===========================//

// 현재 생성하는 게임의 플레이어 수
// 임시 : 테스트 편의를 위해 초기값 6으로 세팅 추후 0으로 변경예정
int GameOptionInfo::CurWormCnt = 0;
//int GameOptionInfo::CurWormCnt = 6;

// 현재 생성하는 게임의 플레이어명 목록
std::vector<std::string> GameOptionInfo::CurPlayerName;

// 현재 생성하는 게임의 맵(초기값 강제 지정)
std::string GameOptionInfo::CurPlayMap = "MapTrain";

// 현재 생성하는 게임의 충돌맵(초기값 강제 지정)
std::string GameOptionInfo::CurPlayColMap = "MapTrain_Ground";

// 현재 생성하는 게임 맵의 최소/최대 위치값목록
std::unordered_map<std::string, float4> GameOptionInfo::MapMinMaxInfo = std::unordered_map<std::string, float4>();

//======================= Game Basic Option =======================//

// 턴타임
// TernTime = 무한대이면 랜덤타임적용
float GameOptionInfo::TernTime = 45.f;

// 라운드타임
int GameOptionInfo::RoundTime = 15;

// 승리조건
int GameOptionInfo::WinSreuired = 2;

// Worm 선택조건
// WormSelect = 0 Off
// WormSelect = 1 On
// WormSelect = 2 Random
int GameOptionInfo::WormSelect = 0;

// Worm 기본체력
// WormEnergy = 50 무한대(체력없음)
int GameOptionInfo::WormEnergy = 50;

// 텔레포트 On/Off
bool GameOptionInfo::Teleportin = false;

//======================= Game Basic Option =======================//


