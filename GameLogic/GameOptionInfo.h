#pragma once
#include <string>
#include <unordered_map>
#include <GameEngineMath.h>

// ���� : �κ�ȭ�鿡�� �����ϴ� ��� ���ӿɼ��� �����ϸ�, �������� �ش� ������ ����� �� �ִ�.
//        ��, �κ񷹺����� �����ϴ� �� �ܿ� ������ ������ �����ʴ´�.
class GameOptionInfo
{
public: // ���� �ɼ�
	// ���� �����ϴ� ������ �÷��̾� ��
	static int CurWormCnt;

	// ���� �����ϴ� ������ �÷��̾���
	static std::vector<std::string> CurPlayerName;

	// ���� �����ϴ� ������ ��
	static std::string CurPlayMap;

	// ���� �����ϴ� ������ �浹��
	static std::string CurPlayColMap;

	// ���� �����ϴ� ���� Min/Max Value
	static std::unordered_map<std::string, float4> MapMinMaxInfo;

public: // ���ӱ⺻�ɼ�
	static float TernTime;
	static int RoundTime;
	static int WinSreuired;
	static int WormSelect;
	static int WormEnergy;
	static bool Teleportin;

public: // ���ӻ󼼿ɼ�


public: // ����ɼ�


};

