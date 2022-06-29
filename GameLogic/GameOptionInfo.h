#pragma once
#include <string>
#include <unordered_map>
#include <GameEngineMath.h>

// 설명 : 로비화면에서 설정하는 모든 게임옵션을 관리하며, 전역으로 해당 값들을 사용할 수 있다.
//        단, 로비레벨에서 조작하는 것 외에 임의의 조작을 하지않는다.
class GameOptionInfo
{
public: // 게임 옵션
	// 현재 생성하는 게임의 플레이어 수
	static int CurWormCnt;

	// 현재 생성하는 게임의 플레이어목록
	static std::vector<std::string> CurPlayerName;

	// 현재 생성하는 게임의 맵
	static std::string CurPlayMap;

	// 현재 생성하는 게임의 충돌맵
	static std::string CurPlayColMap;

	// 현재 생성하는 맵의 Min/Max Value
	static std::unordered_map<std::string, float4> MapMinMaxInfo;

public: // 게임기본옵션
	static float TernTime;
	static int RoundTime;
	static int WinSreuired;
	static int WormSelect;
	static int WormEnergy;
	static bool Teleportin;

public: // 게임상세옵션


public: // 무기옵션


};

