#pragma once
#include <string>
#include <GameEngineImageFile.h>

void AppRelease();
void AppResourcesInit();


// �ε� �̹��� Ŀ�� �浹 ������ �Լ� ���� - ������ 
void ResourceInitPJW();

// UI �̹��� Ŀ�� �浹 ������ �Լ� ���� - ������
void UIImageInit();

// ���Ǿ� �̹��� �ε� - ������
void LobbyImageInit();

// ������ �̹��� �ε� - ������ 
void EndingImageInit();

// ���� ������ �������� ���� ��� �߰� - ������
void LoadSoundFromFileLoop(const std::string& _path, bool _Loop = true);

// 2022-01-12 ������ : 
namespace RS
{
	GameEngineImageFile* LoadImageFromFile(const std::string& _path);
	void LoadImageFromFileAndCut(const std::string& _path, const float4& _cutSize);
	void LoadSoundFromFile(const std::string& _path);
}
void CharactorImageInit();
void WeaponImageInit();

void MapWaterImageInit();
void GimmickObjectImageInit();
void EffectImageInit();

void LoadSoundInit();
void TitleLevelInit();
void MenuSelectInit();

void SoundLoad();