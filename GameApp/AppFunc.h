#pragma once
#include <string>
#include <GameEngineImageFile.h>

void AppRelease();
void AppResourcesInit();


// 로딩 이미지 커밋 충돌 방지용 함수 묶음 - 박종원 
void ResourceInitPJW();

// UI 이미지 커밋 충돌 방지용 함수 묶음 - 신종하
void UIImageInit();

// 대기실씬 이미지 로딩 - 신종하
void LobbyImageInit();

// 엔딩씬 이미지 로딩 - 신종하 
void EndingImageInit();

// 사운드 생성시 루프가능 사운드 기능 추가 - 신종하
void LoadSoundFromFileLoop(const std::string& _path, bool _Loop = true);

// 2022-01-12 조규현 : 
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