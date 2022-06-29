#include "AppFunc.h"
#include <GameEngineLevelManager.h>
#include <GameEngineTime.h>
#include <GameEngineImage.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineSoundManager.h>
#include <GameEngineDirectroy.h>
#include <GameEngineFile.h>
#include <GameEngineImageFile.h>
#include <GameEngineDebugExtension.h>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <filesystem>

#include <GameOptionInfo.h>


namespace fs = std::filesystem;

void AppResourcesInit()
{
	// 맵 최소, 최대값 초기화
	{
		GameOptionInfo::MapMinMaxInfo.insert(std::pair<std::string, float4>("MapTrain", { 800.f, 3300.f }));
		GameOptionInfo::MapMinMaxInfo.insert(std::pair<std::string, float4>("MapBooks", { 200.f, 3640.f }));
		GameOptionInfo::MapMinMaxInfo.insert(std::pair<std::string, float4>("MapCars", { 200.f, 3640.f }));
		GameOptionInfo::MapMinMaxInfo.insert(std::pair<std::string, float4>("MapCity", { 400.f, 3440.f }));

	}

	// 이미지 로드
	{
		GameEngineDirectroy Dir = GameEngineDirectroy();
		Dir.MoveParent("Worms_Armageddon");

		if (false == Dir.MoveChild("\\Resources\\Image\\"))
		{
			GameEngineDebug::AssertFalse();
			return;
		}

		// 절대 경로
		GameEngineImage::GetInst().LoadGameImage("LobbyImage", Dir.PathToPlusFileName("LobbyImage.bmp"));

		// 맵 종류
		// 그라데이션
		GameEngineImage::GetInst().LoadGameImage("Gradient", Dir.PathToPlusFileName("gradient.bmp"));

		// 맵
		GameEngineImage::GetInst().LoadGameImage("MapTrain", Dir.PathToPlusFileName("MapTrain.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapBooks", Dir.PathToPlusFileName("MapBooks.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapCars", Dir.PathToPlusFileName("MapCars.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapCity", Dir.PathToPlusFileName("MapCity.bmp"));

		// 충돌맵
		GameEngineImage::GetInst().LoadGameImage("MapTrain_Ground", Dir.PathToPlusFileName("MapTrain_Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapBooks_Ground", Dir.PathToPlusFileName("MapBooks_Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapCars_Ground", Dir.PathToPlusFileName("MapCars_Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapCity_Ground", Dir.PathToPlusFileName("MapCity_Ground.bmp"));

		GameEngineImage::GetInst().LoadGameImage("Ground", Dir.PathToPlusFileName("Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom", Dir.PathToPlusFileName("Boom.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom_4", Dir.PathToPlusFileName("Boom_4.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom_6", Dir.PathToPlusFileName("Boom_6.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom_13", Dir.PathToPlusFileName("Boom_13.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom_25", Dir.PathToPlusFileName("Boom_25.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom_50", Dir.PathToPlusFileName("Boom_50.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom_75", Dir.PathToPlusFileName("Boom_75.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom_100", Dir.PathToPlusFileName("Boom_100.bmp"));
		GameEngineImage::GetInst().LoadGameImage("BoomEdge", Dir.PathToPlusFileName("BoomEdge.bmp"));
		GameEngineImage::GetInst().LoadGameImage("BoomEdge_100", Dir.PathToPlusFileName("BoomEdge_100.bmp"));
		GameEngineImage::GetInst().LoadGameImage("BoomEdge_75", Dir.PathToPlusFileName("BoomEdge_75.bmp"));
		GameEngineImage::GetInst().LoadGameImage("BoomEdge_50", Dir.PathToPlusFileName("BoomEdge_50.bmp"));
		GameEngineImage::GetInst().LoadGameImage("BoomEdge_25", Dir.PathToPlusFileName("BoomEdge_25.bmp"));
		GameEngineImage::GetInst().LoadGameImage("BoomEdge_13", Dir.PathToPlusFileName("BoomEdge_13.bmp"));
		GameEngineImage::GetInst().LoadGameImage("BoomEdge_6", Dir.PathToPlusFileName("BoomEdge_6.bmp"));
		GameEngineImage::GetInst().LoadGameImage("BoomEdge_4", Dir.PathToPlusFileName("BoomEdge_4.bmp"));

		GameEngineImage::GetInst().LoadGameImage("Bazooka", Dir.PathToPlusFileName("Bazooka.bmp")); // 테스트용 이미지
		GameEngineImageFile* loadingImage = GameEngineImage::GetInst().LoadGameImage("missile", Dir.PathToPlusFileName("missile.bmp"));
		loadingImage->Cut({ 60,60 });

		loadingImage = GameEngineImage::GetInst().LoadGameImage("blob", Dir.PathToPlusFileName("blob.bmp"));
		loadingImage->Cut({ 64.f,64.f });


		float4 cutSize = float4(60.f, 60.f);
		RS::LoadImageFromFileAndCut(Dir.PathToPlusFileName("hmissil1.bmp"), cutSize);
		RS::LoadImageFromFileAndCut(Dir.PathToPlusFileName("hmissil2.bmp"), cutSize);
		RS::LoadImageFromFileAndCut(Dir.PathToPlusFileName("markerr.bmp"), cutSize);

		if (false == Dir.MoveChild("\\Weapons\\"))
		{
			GameEngineDebug::AssertFalse();
			return;
		}

		GameEngineImage::GetInst().LoadGameImage("Grds0", Dir.PathToPlusFileName("grds0.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds1", Dir.PathToPlusFileName("grds1.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds2", Dir.PathToPlusFileName("grds2.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds3", Dir.PathToPlusFileName("grds3.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds4", Dir.PathToPlusFileName("grds4.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds5", Dir.PathToPlusFileName("grds5.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds6", Dir.PathToPlusFileName("grds6.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds7", Dir.PathToPlusFileName("grds7.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds8", Dir.PathToPlusFileName("grds8.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl0", Dir.PathToPlusFileName("grdl0.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl1", Dir.PathToPlusFileName("grdl1.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl2", Dir.PathToPlusFileName("grdl2.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl3", Dir.PathToPlusFileName("grdl3.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl4", Dir.PathToPlusFileName("grdl4.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl5", Dir.PathToPlusFileName("grdl5.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl6", Dir.PathToPlusFileName("grdl6.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl7", Dir.PathToPlusFileName("grdl7.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl8", Dir.PathToPlusFileName("grdl8.bmp"));

		GameEngineImage::GetInst().LoadGameImage("Grds0b", Dir.PathToPlusFileName("grds0b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds1b", Dir.PathToPlusFileName("grds1b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds2b", Dir.PathToPlusFileName("grds2b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds3b", Dir.PathToPlusFileName("grds3b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds4b", Dir.PathToPlusFileName("grds4b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds5b", Dir.PathToPlusFileName("grds5b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds6b", Dir.PathToPlusFileName("grds6b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds7b", Dir.PathToPlusFileName("grds7b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grds8b", Dir.PathToPlusFileName("grds8b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl0b", Dir.PathToPlusFileName("grdl0b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl1b", Dir.PathToPlusFileName("grdl1b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl2b", Dir.PathToPlusFileName("grdl2b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl3b", Dir.PathToPlusFileName("grdl3b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl4b", Dir.PathToPlusFileName("grdl4b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl5b", Dir.PathToPlusFileName("grdl5b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl6b", Dir.PathToPlusFileName("grdl6b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl7b", Dir.PathToPlusFileName("grdl7b.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Grdl8b", Dir.PathToPlusFileName("grdl8b.bmp"));

		GameEngineImage::GetInst().LoadGameImage("airjetbLeft", Dir.PathToPlusFileName("airjetbLeft.bmp"));
		GameEngineImage::GetInst().LoadGameImage("airjetbRight", Dir.PathToPlusFileName("airjetbRight.bmp"));

		RS::LoadImageFromFileAndCut(Dir.PathToPlusFileName("airmisl.bmp"), cutSize);

		TitleLevelInit();
		MenuSelectInit();
		ResourceInitPJW();
		CharactorImageInit();
		WeaponImageInit();
		UIImageInit();
		MapWaterImageInit();
		GimmickObjectImageInit();
		EffectImageInit();
		LobbyImageInit();
		EndingImageInit();
	}

	// 사운드 로드
	{
		SoundLoad();
		//GameEngineDirectroy Dir = GameEngineDirectroy();
		//Dir.MoveParent("API38");
		//
		//if (false == Dir.MoveChild("\\Resources\\Sound\\"))
		//{
		//	GameEngineDebug::AssertFalse();
		//	return;
		//}
		//
		//GameEngineSound::GetInst().LoadSound("test.mp3", Dir.PathToPlusFileName("test.mp3"));

	}
}

void AppRelease()
{
	GameEngineDebugExtension::Release();
	GameEngineLevelManager::Destroy();


	GameEngineImage::Destroy();
	GameEngineSoundManager::Destroy();
	GameEngineInput::Destroy();
	GameEngineWindow::Destroy();
	GameEngineTime::Destroy();
}


void ResourceInitPJW()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms_Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}
	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().LoadGameImage("LoadingSprites", Dir.PathToPlusFileName("LoadingSprites.bmp"));
	loadingImage->Cut({ 160,160 });
	GameEngineImage::GetInst().LoadGameImage("Midground", Dir.PathToPlusFileName("Midground.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Background", Dir.PathToPlusFileName("backGround.bmp"));

	if (false == Dir.MoveChild("\\Misc\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImageFile* cloudL = GameEngineImage::GetInst().LoadGameImage("cloudl", Dir.PathToPlusFileName("cloudl.bmp"));
	cloudL->Cut({ 160,160 });
	GameEngineImageFile* cloudM = GameEngineImage::GetInst().LoadGameImage("cloudm", Dir.PathToPlusFileName("cloudm.bmp"));
	cloudM->Cut({ 128,128 });
	GameEngineImageFile* cloudS = GameEngineImage::GetInst().LoadGameImage("clouds", Dir.PathToPlusFileName("clouds.bmp"));
	cloudS->Cut({ 60,60 });

	GameEngineImage::GetInst().LoadGameImage("ScatterStar", Dir.PathToPlusFileName("ScatterStar.bmp"));
	GameEngineImage::GetInst().LoadGameImage("ScatterStar1", Dir.PathToPlusFileName("ScatterStar1.bmp"));
	GameEngineImage::GetInst().LoadGameImage("ScatterStar2", Dir.PathToPlusFileName("ScatterStar2.bmp"));

	GameEngineImage::GetInst().LoadGameImage("ScatterSnow", Dir.PathToPlusFileName("ScatterSnow.bmp"));
	GameEngineImage::GetInst().LoadGameImage("windGauge", Dir.PathToPlusFileName("windGauge.bmp"));
	GameEngineImage::GetInst().LoadGameImage("windBarHider", Dir.PathToPlusFileName("windBarHider.bmp"));
	GameEngineImageFile* windBarSprites = GameEngineImage::GetInst().LoadGameImage("windBar", Dir.PathToPlusFileName("windBar.bmp"));
	windBarSprites->Cut({ 87,13 });
	GameEngineImageFile* leafSprites = GameEngineImage::GetInst().LoadGameImage("ScatterLeaf", Dir.PathToPlusFileName("ScatterLeaf.bmp"));
	leafSprites->Cut({ 32,32 });

	if (false == Dir.MoveChild("\\Player_arrow\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}
	GameEngineImageFile* arrowdnb = GameEngineImage::GetInst().LoadGameImage("arrowdnb", Dir.PathToPlusFileName("arrowdnb.bmp"));
	arrowdnb->Cut({ 60,60 });
	GameEngineImageFile* arrowdnc = GameEngineImage::GetInst().LoadGameImage("arrowdnc", Dir.PathToPlusFileName("arrowdnc.bmp"));
	arrowdnc->Cut({ 60,60 });
	GameEngineImageFile* arrowdng = GameEngineImage::GetInst().LoadGameImage("arrowdng", Dir.PathToPlusFileName("arrowdng.bmp"));
	arrowdng->Cut({ 60,60 });
	GameEngineImageFile* arrowdnp = GameEngineImage::GetInst().LoadGameImage("arrowdnp", Dir.PathToPlusFileName("arrowdnp.bmp"));
	arrowdnp->Cut({ 60,60 });
	GameEngineImageFile* arrowdnr = GameEngineImage::GetInst().LoadGameImage("arrowdnr", Dir.PathToPlusFileName("arrowdnr.bmp"));
	arrowdnr->Cut({ 60,60 });
	GameEngineImageFile* arrowdny = GameEngineImage::GetInst().LoadGameImage("arrowdny", Dir.PathToPlusFileName("arrowdny.bmp"));
	arrowdny->Cut({ 60,60 });

	Dir.MoveParent("Image");

	if (false == Dir.MoveChild("\\UI\\HPbar\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}
	//GameEngineImage::GetInst().LoadGameImage("HPbar", Dir.PathToPlusFileName("HPbar.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomNameTag", Dir.PathToPlusFileName("BottomNameTag.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomNameTag2", Dir.PathToPlusFileName("BottomNameTag2.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomNameTag3", Dir.PathToPlusFileName("BottomNameTag3.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomNameTag4", Dir.PathToPlusFileName("BottomNameTag4.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomNameTag5", Dir.PathToPlusFileName("BottomNameTag5.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomNameTag6", Dir.PathToPlusFileName("BottomNameTag6.bmp"));

	GameEngineImage::GetInst().LoadGameImage("BottomFlagRUS", Dir.PathToPlusFileName("BottomFlagRUS.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomFlagKOR", Dir.PathToPlusFileName("BottomFlagKOR.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomFlagUSA", Dir.PathToPlusFileName("BottomFlagUSA.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomFlagJPN", Dir.PathToPlusFileName("BottomFlagJPN.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomFlagGER", Dir.PathToPlusFileName("BottomFlagGER.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomFlagBRA", Dir.PathToPlusFileName("BottomFlagBRA.bmp"));
	
	GameEngineImage::GetInst().LoadGameImage("BottomHPbarR", Dir.PathToPlusFileName("BottomHPbarR.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomHPbarG", Dir.PathToPlusFileName("BottomHPbarG.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomHPbarB", Dir.PathToPlusFileName("BottomHPbarB.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomHPbarY", Dir.PathToPlusFileName("BottomHPbarY.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomHPbarP", Dir.PathToPlusFileName("BottomHPbarP.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomHPbarS", Dir.PathToPlusFileName("BottomHPbarS.bmp"));

	GameEngineImage::GetInst().LoadGameImage("WormName1", Dir.PathToPlusFileName("WormName1.bmp"));
	GameEngineImage::GetInst().LoadGameImage("WormName2", Dir.PathToPlusFileName("WormName2.bmp"));
	GameEngineImage::GetInst().LoadGameImage("WormName3", Dir.PathToPlusFileName("WormName3.bmp"));
	GameEngineImage::GetInst().LoadGameImage("WormName4", Dir.PathToPlusFileName("WormName4.bmp"));
	GameEngineImage::GetInst().LoadGameImage("WormName5", Dir.PathToPlusFileName("WormName5.bmp"));
	GameEngineImage::GetInst().LoadGameImage("WormName6", Dir.PathToPlusFileName("WormName6.bmp"));

	GameEngineImage::GetInst().LoadGameImage("WormHP", Dir.PathToPlusFileName("WormHP.bmp"));
	GameEngineImageFile* HPNumberSprite = GameEngineImage::GetInst().LoadGameImage("HPnumber", Dir.PathToPlusFileName("HPnumber.bmp"));
	HPNumberSprite->Cut({ 12,12 });

	Dir.MoveParent("UI");

	if (false == Dir.MoveChild("\\Timer\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}
	GameEngineImage::GetInst().LoadGameImage("TimerWindowR", Dir.PathToPlusFileName("TimerWindowR.bmp"));
	GameEngineImage::GetInst().LoadGameImage("TimerWindowB", Dir.PathToPlusFileName("TimerWindowB.bmp"));
	GameEngineImage::GetInst().LoadGameImage("TimerWindowG", Dir.PathToPlusFileName("TimerWindowG.bmp"));
	GameEngineImage::GetInst().LoadGameImage("TimerWindowY", Dir.PathToPlusFileName("TimerWindowY.bmp"));
	GameEngineImage::GetInst().LoadGameImage("TimerWindowP", Dir.PathToPlusFileName("TimerWindowP.bmp"));
	GameEngineImage::GetInst().LoadGameImage("TimerWindowC", Dir.PathToPlusFileName("TimerWindowC.bmp"));
	GameEngineImageFile* digitSprite = GameEngineImage::GetInst().LoadGameImage("TimerNum", Dir.PathToPlusFileName("TimerNum.bmp"));
	digitSprite->Cut({ 34,34 });

}

void UIImageInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();

	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("WeaponSheet", Dir.PathToPlusFileName("WeaponSheet_Temp.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Cursor", Dir.PathToPlusFileName("Cursor.bmp"));

	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\Weapon Icons"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	// 무기선택박스
	GameEngineImage::GetInst().LoadGameImage("WeaponSelector", Dir.PathToPlusFileName("WeaponSelector.bmp"));

	// 무기창의 무기목록
	// Weapon Sheet Utile Line
	GameEngineImage::GetInst().LoadGameImage("jetpack", Dir.PathToPlusFileName("jetpack.bmp"));
	GameEngineImage::GetInst().LoadGameImage("gravity", Dir.PathToPlusFileName("gravity.bmp"));
	GameEngineImage::GetInst().LoadGameImage("speed", Dir.PathToPlusFileName("speed.bmp"));
	GameEngineImage::GetInst().LoadGameImage("laser", Dir.PathToPlusFileName("laser.bmp"));
	GameEngineImage::GetInst().LoadGameImage("invisibl", Dir.PathToPlusFileName("invisibl.bmp"));

	// Weapon Sheet F1 Line
	GameEngineImage::GetInst().LoadGameImage("bazooka", Dir.PathToPlusFileName("bazooka.bmp"));
	GameEngineImage::GetInst().LoadGameImage("hmissile", Dir.PathToPlusFileName("hmissile.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mortar", Dir.PathToPlusFileName("mortar.bmp"));
	GameEngineImage::GetInst().LoadGameImage("pigeon", Dir.PathToPlusFileName("pigeon.bmp"));
	GameEngineImage::GetInst().LoadGameImage("launch", Dir.PathToPlusFileName("launch.bmp"));

	// Weapon Sheet F2 Line
	GameEngineImage::GetInst().LoadGameImage("grenade", Dir.PathToPlusFileName("grenade.bmp"));
	GameEngineImage::GetInst().LoadGameImage("cluster", Dir.PathToPlusFileName("cluster.bmp"));
	GameEngineImage::GetInst().LoadGameImage("banana", Dir.PathToPlusFileName("banana.bmp"));
	GameEngineImage::GetInst().LoadGameImage("axe", Dir.PathToPlusFileName("axe.bmp"));
	GameEngineImage::GetInst().LoadGameImage("quake", Dir.PathToPlusFileName("quake.bmp"));

	// Weapon Sheet F3 Line
	GameEngineImage::GetInst().LoadGameImage("shotgun", Dir.PathToPlusFileName("shotgun.bmp"));
	GameEngineImage::GetInst().LoadGameImage("handgun", Dir.PathToPlusFileName("handgun.bmp"));
	GameEngineImage::GetInst().LoadGameImage("uzi", Dir.PathToPlusFileName("uzi.bmp"));
	GameEngineImage::GetInst().LoadGameImage("minigun", Dir.PathToPlusFileName("minigun.bmp"));
	GameEngineImage::GetInst().LoadGameImage("longbow", Dir.PathToPlusFileName("longbow.bmp"));

	// Weapon Sheet F4 Line
	GameEngineImage::GetInst().LoadGameImage("firepnch", Dir.PathToPlusFileName("firepnch.bmp"));
	GameEngineImage::GetInst().LoadGameImage("dragball", Dir.PathToPlusFileName("dragball.bmp"));
	GameEngineImage::GetInst().LoadGameImage("kamikaze", Dir.PathToPlusFileName("kamikaze.bmp"));
	GameEngineImage::GetInst().LoadGameImage("suicide", Dir.PathToPlusFileName("suicide.bmp"));
	GameEngineImage::GetInst().LoadGameImage("prod", Dir.PathToPlusFileName("prod.bmp"));

	// Weapon Sheet F5 Line
	GameEngineImage::GetInst().LoadGameImage("dynamite", Dir.PathToPlusFileName("dynamite.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mine", Dir.PathToPlusFileName("mine.bmp"));
	GameEngineImage::GetInst().LoadGameImage("sheep", Dir.PathToPlusFileName("sheep.bmp"));
	GameEngineImage::GetInst().LoadGameImage("aqua", Dir.PathToPlusFileName("aqua.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mole", Dir.PathToPlusFileName("mole.bmp"));

	// Weapon Sheet F6 Line
	GameEngineImage::GetInst().LoadGameImage("airstrke", Dir.PathToPlusFileName("airstrke.bmp"));
	GameEngineImage::GetInst().LoadGameImage("firestrk", Dir.PathToPlusFileName("firestrk.bmp"));
	GameEngineImage::GetInst().LoadGameImage("postal", Dir.PathToPlusFileName("postal.bmp"));
	GameEngineImage::GetInst().LoadGameImage("minestrk", Dir.PathToPlusFileName("minestrk.bmp"));
	GameEngineImage::GetInst().LoadGameImage("molestrk", Dir.PathToPlusFileName("molestrk.bmp"));

	// Weapon Sheet F7 Line
	GameEngineImage::GetInst().LoadGameImage("blwtorch", Dir.PathToPlusFileName("blwtorch.bmp"));
	GameEngineImage::GetInst().LoadGameImage("drill", Dir.PathToPlusFileName("drill.bmp"));
	GameEngineImage::GetInst().LoadGameImage("girder", Dir.PathToPlusFileName("girder.bmp"));
	GameEngineImage::GetInst().LoadGameImage("baseball", Dir.PathToPlusFileName("baseball.bmp"));
	GameEngineImage::GetInst().LoadGameImage("girders", Dir.PathToPlusFileName("girders.bmp"));

	// Weapon Sheet F8 Line
	GameEngineImage::GetInst().LoadGameImage("rope", Dir.PathToPlusFileName("rope.bmp"));
	GameEngineImage::GetInst().LoadGameImage("bungee", Dir.PathToPlusFileName("bungee.bmp"));
	GameEngineImage::GetInst().LoadGameImage("parachut", Dir.PathToPlusFileName("parachut.bmp"));
	GameEngineImage::GetInst().LoadGameImage("teleport", Dir.PathToPlusFileName("teleport.bmp"));
	GameEngineImage::GetInst().LoadGameImage("scales", Dir.PathToPlusFileName("scales.bmp"));

	// Weapon Sheet F9 Line
	GameEngineImage::GetInst().LoadGameImage("sbanana", Dir.PathToPlusFileName("sbanana.bmp"));
	GameEngineImage::GetInst().LoadGameImage("hgrenade", Dir.PathToPlusFileName("hgrenade.bmp"));
	GameEngineImage::GetInst().LoadGameImage("thrower", Dir.PathToPlusFileName("thrower.bmp"));
	GameEngineImage::GetInst().LoadGameImage("tamborin", Dir.PathToPlusFileName("tamborin.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mbbomb", Dir.PathToPlusFileName("mbbomb.bmp"));

	// Weapon Sheet F10 Line
	GameEngineImage::GetInst().LoadGameImage("petrolbm", Dir.PathToPlusFileName("petrolbm.bmp"));
	GameEngineImage::GetInst().LoadGameImage("skunk", Dir.PathToPlusFileName("skunk.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mingvase", Dir.PathToPlusFileName("mingvase.bmp"));
	GameEngineImage::GetInst().LoadGameImage("shpstrke", Dir.PathToPlusFileName("shpstrke.bmp"));
	GameEngineImage::GetInst().LoadGameImage("carpet", Dir.PathToPlusFileName("carpet.bmp"));

	// Weapon Sheet F11 Line
	GameEngineImage::GetInst().LoadGameImage("cow", Dir.PathToPlusFileName("cow.bmp"));
	GameEngineImage::GetInst().LoadGameImage("oldwoman", Dir.PathToPlusFileName("oldwoman.bmp"));
	GameEngineImage::GetInst().LoadGameImage("donkey", Dir.PathToPlusFileName("donkey.bmp"));
	GameEngineImage::GetInst().LoadGameImage("nuke", Dir.PathToPlusFileName("nuke.bmp"));
	GameEngineImage::GetInst().LoadGameImage("armagedn", Dir.PathToPlusFileName("armagedn.bmp"));

	// Weapon Sheet F12 Line
	GameEngineImage::GetInst().LoadGameImage("skipgo", Dir.PathToPlusFileName("skipgo.bmp"));
	GameEngineImage::GetInst().LoadGameImage("surender", Dir.PathToPlusFileName("surender.bmp"));
	GameEngineImage::GetInst().LoadGameImage("select", Dir.PathToPlusFileName("select.bmp"));
	GameEngineImage::GetInst().LoadGameImage("freeze", Dir.PathToPlusFileName("freeze.bmp"));
	GameEngineImage::GetInst().LoadGameImage("bullet", Dir.PathToPlusFileName("bullet.bmp"));
}

void LobbyImageInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_Backdrop", Dir.PathToPlusFileName("Lobby_Backdrop.bmp"));

	// 로비 버튼관련
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\ButtonBorders"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_ButtonNormal", Dir.PathToPlusFileName("Normal_Btn.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_ButtonMouseOn", Dir.PathToPlusFileName("MouseOver_Btn.bmp"));

	// 로비 화면 관련 Display Box
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\ButtonBorders"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_HostBox", Dir.PathToPlusFileName("4459.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_PlayerBox", Dir.PathToPlusFileName("6868.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_SelPlayerInput", Dir.PathToPlusFileName("5619.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_SelPlayerBox", Dir.PathToPlusFileName("6836.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_ChattingHis", Dir.PathToPlusFileName("13268.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_ChattingInput", Dir.PathToPlusFileName("24428.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_ChattingInputOK", Dir.PathToPlusFileName("24428_2.bmp"));

	// 로비화면 호스트 레디 이미지
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\Multiplay\\HostJoinScreen\\BigReadyBulb.seq"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_HostReadyOff", Dir.PathToPlusFileName("OFF_btn.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_HostReadyOn", Dir.PathToPlusFileName("ON_btn.bmp"));

	GameEngineImage::GetInst().LoadGameImage("Lobby_HostReadyOff_MouseOver", Dir.PathToPlusFileName("OFF_btn_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_HostReadyOn_MouseOver", Dir.PathToPlusFileName("ON_btn_MouseOver.bmp"));

	// 로비화면 호스트 생성 리소스
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\Multiplay\\HostJoinScreen\\ReadyYN.seq"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_HostCurReadyOn", Dir.PathToPlusFileName("ON.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_HostCurReadyOff", Dir.PathToPlusFileName("OFF.bmp"));

	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\Multiplay\\HostJoinScreen\\Nation"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("LobbyNation_Kor", Dir.PathToPlusFileName("Nation_Kor.bmp"));

	// 선택가능 맵 이미지 로딩
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\SelectMap"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("LobbyMap_MapTrain", Dir.PathToPlusFileName("LobbyMap_MapTrain.bmp"));
	GameEngineImage::GetInst().LoadGameImage("LobbyMap_MapCars", Dir.PathToPlusFileName("LobbyMap_MapCars.bmp"));
	GameEngineImage::GetInst().LoadGameImage("LobbyMap_MapCity", Dir.PathToPlusFileName("LobbyMap_MapCity.bmp"));
	GameEngineImage::GetInst().LoadGameImage("LobbyMap_MapBooks", Dir.PathToPlusFileName("LobbyMap_MapBooks.bmp"));

	// 로비 게임옵션 및 무기옵션 설정화면 진입 이미지
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\Menu\\optionsmenu"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_SetGameOption", Dir.PathToPlusFileName("gameoptions.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_SetWeaponOption", Dir.PathToPlusFileName("weaponoptions.bmp"));

	// 로비 게임 기본옵션 설정

	// 턴타임
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\gameoptions\\TurnTime"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime0", Dir.PathToPlusFileName("000000.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime1", Dir.PathToPlusFileName("000001.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime2", Dir.PathToPlusFileName("000002.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime3", Dir.PathToPlusFileName("000003.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime4", Dir.PathToPlusFileName("000004.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime5", Dir.PathToPlusFileName("000005.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime6", Dir.PathToPlusFileName("000006.bmp"));

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime0_MouseOver", Dir.PathToPlusFileName("000000_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime1_MouseOver", Dir.PathToPlusFileName("000001_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime2_MouseOver", Dir.PathToPlusFileName("000002_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime3_MouseOver", Dir.PathToPlusFileName("000003_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime4_MouseOver", Dir.PathToPlusFileName("000004_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime5_MouseOver", Dir.PathToPlusFileName("000005_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_TernTime6_MouseOver", Dir.PathToPlusFileName("000006_MouseOver.bmp"));

	// 라운드타임
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\gameoptions\\RoundTime"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime0", Dir.PathToPlusFileName("000001.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime1", Dir.PathToPlusFileName("000002.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime2", Dir.PathToPlusFileName("000003.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime3", Dir.PathToPlusFileName("000004.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime4", Dir.PathToPlusFileName("000005.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime5", Dir.PathToPlusFileName("000006.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime6", Dir.PathToPlusFileName("000007.bmp"));

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime0_MouseOver", Dir.PathToPlusFileName("000001_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime1_MouseOver", Dir.PathToPlusFileName("000002_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime2_MouseOver", Dir.PathToPlusFileName("000003_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime3_MouseOver", Dir.PathToPlusFileName("000004_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime4_MouseOver", Dir.PathToPlusFileName("000005_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime5_MouseOver", Dir.PathToPlusFileName("000006_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_RoundTime6_MouseOver", Dir.PathToPlusFileName("000007_MouseOver.bmp"));

	// 승리 조건
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\gameoptions\\winsrequired"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired0", Dir.PathToPlusFileName("000000.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired1", Dir.PathToPlusFileName("000001.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired2", Dir.PathToPlusFileName("000002.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired3", Dir.PathToPlusFileName("000003.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired4", Dir.PathToPlusFileName("000004.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired5", Dir.PathToPlusFileName("000005.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired6", Dir.PathToPlusFileName("000006.bmp"));

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired0_MouseOver", Dir.PathToPlusFileName("000000_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired1_MouseOver", Dir.PathToPlusFileName("000001_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired2_MouseOver", Dir.PathToPlusFileName("000002_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired3_MouseOver", Dir.PathToPlusFileName("000003_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired4_MouseOver", Dir.PathToPlusFileName("000004_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired5_MouseOver", Dir.PathToPlusFileName("000005_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WinSrequired6_MouseOver", Dir.PathToPlusFileName("000006_MouseOver.bmp"));

	// Worm 체력
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\gameoptions\\WormEnergy"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormEnergy0", Dir.PathToPlusFileName("000000.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormEnergy1", Dir.PathToPlusFileName("000001.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormEnergy2", Dir.PathToPlusFileName("000002.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormEnergy3", Dir.PathToPlusFileName("000003.bmp"));

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormEnergy0_MouseOver", Dir.PathToPlusFileName("000000_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormEnergy1_MouseOver", Dir.PathToPlusFileName("000001_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormEnergy2_MouseOver", Dir.PathToPlusFileName("000002_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormEnergy3_MouseOver", Dir.PathToPlusFileName("000003_MouseOver.bmp"));

	// 턴교체 On/Off
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\gameoptions"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormSelect0", Dir.PathToPlusFileName("WormSelectOFF.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormSelect1", Dir.PathToPlusFileName("WormSelectON.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormSelect2", Dir.PathToPlusFileName("WormSelectRANDOM.bmp"));

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormSelect0_MouseOver", Dir.PathToPlusFileName("WormSelectOFF_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormSelect1_MouseOver", Dir.PathToPlusFileName("WormSelectON_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_WormSelect2_MouseOver", Dir.PathToPlusFileName("WormSelectRANDOM_MouseOver.bmp"));

	// 텔레포트 On/Off
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_Teleportin0", Dir.PathToPlusFileName("TeleportinOFF.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_Teleportin1", Dir.PathToPlusFileName("TeleportinON.bmp"));

	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_Teleportin0_MouseOver", Dir.PathToPlusFileName("TeleportinOFF_MouseOver.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_BasicOption_Teleportin1_MouseOver", Dir.PathToPlusFileName("TeleportinON_MouseOver.bmp"));

	// 선택가능한 플레이어 & 선택한 플레이어관련
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\CreateTeam"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_Player", Dir.PathToPlusFileName("000000.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_CPU1", Dir.PathToPlusFileName("000001.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_CPU2", Dir.PathToPlusFileName("000002.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_CPU3", Dir.PathToPlusFileName("000003.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_CPU4", Dir.PathToPlusFileName("000004.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Lobby_CPU5", Dir.PathToPlusFileName("000005.bmp"));
}

void EndingImageInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Ending_BackDrop", Dir.PathToPlusFileName("Worms_EndingBackDrop.bmp"));

	Dir.MoveParent("Worms_Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\Font"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	// 알파벳
	GameEngineImageFile* digitSprite = GameEngineImage::GetInst().LoadGameImage("Ending_Alphabet", Dir.PathToPlusFileName("AlphabetUpper_Font.bmp"));
	digitSprite->Cut({ 50,52 });

}

void LoadSoundFromFileLoop(const std::string& _path, bool _loop)
{
	size_t fileNameStartIndex = _path.rfind("\\") + 1;
	std::string fileName = _path.substr(fileNameStartIndex, _path.size() - fileNameStartIndex);

	GameEngineSoundManager::GetInstance().CreateSound(fileName, _path, _loop);
}

void CharactorImageInit()
{
	GameEngineDirectroy dir = GameEngineDirectroy();
	dir.MoveParent("Worms_Armageddon");
	dir.MoveChild("\\Resources\\Image\\Worms");

	float4 cutSize = float4(60.f, 60.f);

	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("backflp.bmp"), cutSize);

	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("wdieLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("wdieRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR_.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR_u.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR_d.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR1_.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR1_u.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR1_d.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR2_.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR2_u.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideR2_d.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL_.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL_u.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL_d.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL1_.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL1_u.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL1_d.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL2_.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL2_u.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("SlideL2_d.bmp"), cutSize);

	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("wfly1_R.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("wfly2_R.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("wfly3_R.bmp"), cutSize);

	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("wfly1_L.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("wfly2_L.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("wfly3_L.bmp"), cutSize);

	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("walkLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("walkRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("jumpReadyLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("jumpReadyRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyUpLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyUpRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyDownLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyDownRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyLinkLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyLinkRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("idleLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("idleRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazAimLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazAimRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazOffRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazOnRight.bmp", cutSize);
	// throwStart : 투척물 던진 후 "그 각도에 맞는 스프라이트로" 잠시 고정되는 애니메이션입니다.
	// throwOff : 투척물 던진 후, throwStart 가 끝나면 다시 손을 넣는 애니메이션입니다.
	RS::LoadImageFromFileAndCut(dir / "throwStartLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "throwStartRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "throwOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "throwOffRight.bmp", cutSize);
	// 수류탄 애니메이션
	RS::LoadImageFromFileAndCut(dir / "grnAimLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "grnAimRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "grnOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "grnOnRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "grnOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "grnOffRight.bmp", cutSize);
	// 승룡권 애니메이션
	RS::LoadImageFromFileAndCut(dir / "firePunchOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchOffRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchEndLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchEndRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchFlyLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchFlyRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchLandLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchLandRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchReadyLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchReadyRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchStartLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "firePunchStartRight.bmp", cutSize);
	// 우지 애니메이션
	RS::LoadImageFromFileAndCut(dir / "uziOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "uziOffRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "uziOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "uziOnRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "uziAimLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "uziAimRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "uziFireLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "uziFireRight.bmp", cutSize);
	// 양 애니메이션
	RS::LoadImageFromFileAndCut(dir / "sheepOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "sheepOnRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "sheepOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "sheepOffRight.bmp", cutSize);
	// 도끼 애니메이션
	RS::LoadImageFromFileAndCut(dir / "axeOnLeft.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeOnRight.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeFire1Left.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeFire1Right.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeFire2Left.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeFire2Right.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeFire3Left.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeFire3Right.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeOffLeft.bmp", { 104,104 });
	RS::LoadImageFromFileAndCut(dir / "axeOffRight.bmp", { 104,104 });
	// 호밍미사일 애니메이션
	RS::LoadImageFromFileAndCut(dir / "homingAimLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "homingAimRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "homingOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "homingOffRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "homingOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "homingOnRight.bmp", cutSize);
	// Girder 애니메이션
	RS::LoadImageFromFileAndCut(dir / "girderOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "girderOffRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "girderOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "girderOnRight.bmp", cutSize);
	// 토치 애니메이션
	RS::LoadImageFromFileAndCut(dir / "blowtorchOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "blowtorchOnRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "blowtorchOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "blowtorchOffRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "blowtorchFireLeft.bmp", float4(60.f, 80.f));
	RS::LoadImageFromFileAndCut(dir / "blowtorchFireRight.bmp", float4(60.f, 80.f));
	// 드릴 애니메이션
	RS::LoadImageFromFileAndCut(dir / "drillLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "drillRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "drillOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "drillOnRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "drillOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "drillOffRight.bmp", cutSize);
	// 에어 스트라이크 애니메이션
	RS::LoadImageFromFileAndCut(dir / "AirStrikeOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "AirStrikeOnRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "AirStrikeOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "AirStrikeOffRight.bmp", cutSize);

	// 승리 애니메이션
	RS::LoadImageFromFileAndCut(dir / "winLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "winRight.bmp", cutSize);

	{
		GameEngineDirectroy dir = GameEngineDirectroy();
		dir.MoveParent("Worms_Armageddon");
		dir.MoveChild("\\Resources\\Image\\Misc\\Aim_Taget");
		RS::LoadImageFromFileAndCut(dir / "crshairr.bmp", cutSize);
	}
}

void WeaponImageInit()
{
	GameEngineDirectroy dir = GameEngineDirectroy();
	dir.MoveParent("Worms_Armageddon");
	dir.MoveChild("\\Resources\\Image");

	float4 cutSize = float4(60.f, 60.f);

	// 양, 슈퍼양
	RS::LoadImageFromFileAndCut(dir / "superSheep.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "sheepWalkLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "sheepWalkRight.bmp", cutSize);
}

void SoundLoad()
{
	// 2022-02-03 조규현 : Effects 폴더의 모든 파일을 로드합니다.
	{
		fs::path path(fs::current_path());
		if (path.filename().string() != "Worms_Armageddon")
		{
			path = path.parent_path();
		}

		if (path.filename().string() != "Worms_Armageddon")
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 경로 \"Worms_Armageddon\"");
		}


		path = path / "Resources" / "Sound" / "Effects";

		for (const fs::path& p : fs::directory_iterator(path))
		{
			RS::LoadSoundFromFile(p.string());
		}
	}

	{
		fs::path path(fs::current_path());
		if (path.filename().string() != "Worms_Armageddon")
		{
			path = path.parent_path();
		}

		if (path.filename().string() != "Worms_Armageddon")
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 경로 \"Worms_Armageddon\"");
		}


		path = path / "Resources" / "Sound" / "English";

		for (const fs::path& p : fs::directory_iterator(path))
		{
			RS::LoadSoundFromFile(p.string());
		}
	}

	GameEngineDirectroy dir = GameEngineDirectroy();
	dir.MoveParent("Worms_Armageddon");
	dir.MoveChild("\\Resources\\Sound\\Effects");

	//RS::LoadSoundFromFile(dir / "SHEEPBAA.WAV");
	//RS::LoadSoundFromFile(dir / "SUPERSHEEPRELEASE.WAV");
	//RS::LoadSoundFromFile(dir / "SUPERSHEEPWHOOSH.WAV");
	//RS::LoadSoundFromFile(dir / "BlowTorch.WAV");
	//RS::LoadSoundFromFile(dir / "GIRDERIMPACT.WAV");
	//RS::LoadSoundFromFile(dir / "DRILL.WAV");
	//RS::LoadImageFromFile(dir / "FirePunchImpact.WAV");

	//// Title Screen Sound
	//RS::LoadSoundFromFile(dir / "Worms_TitleScreen.mp3");
	//RS::LoadSoundFromFile(dir / "WormLanding.wav");
	LoadSoundFromFileLoop(dir / "Worms_TitleScreen_Heartbeat.wav");

	// MenuSelect Screen Sound
	//RS::LoadSoundFromFile(dir / "CursorSelect.wav");

	// Lobby Screen Sound

}

GameEngineImageFile* RS::LoadImageFromFile(const std::string& _path)
{
	size_t fileNameStartIndex = _path.rfind("\\") + 1;
	std::string fileName = _path.substr(fileNameStartIndex, _path.size() - fileNameStartIndex);

	return GameEngineImage::GetInst().LoadGameImage(fileName, _path);
}

void RS::LoadImageFromFileAndCut(const std::string& _path, const float4& _cutSize)
{
	size_t fileNameStartIndex = _path.rfind("\\") + 1;
	std::string fileName = _path.substr(fileNameStartIndex, _path.size() - fileNameStartIndex);

	GameEngineImageFile* image = GameEngineImage::GetInst().LoadGameImage(fileName, _path);
	image->Cut(_cutSize);
}

void RS::LoadSoundFromFile(const std::string& _path)
{
	size_t fileNameStartIndex = _path.rfind("\\") + 1;
	std::string fileName = _path.substr(fileNameStartIndex, _path.size() - fileNameStartIndex);

	GameEngineSoundManager::GetInstance().CreateSound(fileName, _path);
}

void MapWaterImageInit() // 바닥 수면 이미지 로드에 사용
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms_Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\Map\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().
		LoadGameImage("Water_sprite", Dir.PathToPlusFileName("Water_sprite.bmp"));
	loadingImage->Cut({ 2560,100 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("Water_sprite_surfice", Dir.PathToPlusFileName("Water_sprite_surfice.bmp"));
	loadingImage->Cut({ 2560,100 });

	GameEngineImage::GetInst().
		LoadGameImage("Under_Water", Dir.PathToPlusFileName("Under_Water.bmp"));
}

void GimmickObjectImageInit() // 기믹 오브젝트 로드에 사용
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms_Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\Misc\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	//oildrum
	{
		GameEngineImageFile* loadingImage = GameEngineImage::GetInst().
			LoadGameImage("oildrum1", Dir.PathToPlusFileName("oildrum1.bmp"));
		loadingImage->Cut({ 90,90 });

		loadingImage = GameEngineImage::GetInst().
			LoadGameImage("oildrum2", Dir.PathToPlusFileName("oildrum2.bmp"));
		loadingImage->Cut({ 90,90 });

		loadingImage = GameEngineImage::GetInst().
			LoadGameImage("oildrum3", Dir.PathToPlusFileName("oildrum3.bmp"));
		loadingImage->Cut({ 90,90 });

		loadingImage = GameEngineImage::GetInst().
			LoadGameImage("oildrum4", Dir.PathToPlusFileName("oildrum4.bmp"));
		loadingImage->Cut({ 90,90 });
	}

	Dir.MoveParent("Worms_Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\Misc\\Grave\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	{
		GameEngineImageFile* loadingImage = GameEngineImage::GetInst().
			LoadGameImage("grave1", Dir.PathToPlusFileName("grave1.bmp"));
		loadingImage->Cut({ 60,60 });

		loadingImage = GameEngineImage::GetInst().
			LoadGameImage("grave2", Dir.PathToPlusFileName("grave2.bmp"));
		loadingImage->Cut({ 60,60 });

		loadingImage = GameEngineImage::GetInst().
			LoadGameImage("grave3", Dir.PathToPlusFileName("grave3.bmp"));
		loadingImage->Cut({ 60,60 });

		loadingImage = GameEngineImage::GetInst().
			LoadGameImage("grave4", Dir.PathToPlusFileName("grave4.bmp"));
		loadingImage->Cut({ 60,60 });

		loadingImage = GameEngineImage::GetInst().
			LoadGameImage("grave5", Dir.PathToPlusFileName("grave5.bmp"));
		loadingImage->Cut({ 60,60 });

		loadingImage = GameEngineImage::GetInst().
			LoadGameImage("grave6", Dir.PathToPlusFileName("grave6.bmp"));
		loadingImage->Cut({ 60,60 });
	}

}

void EffectImageInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms_Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\Effects\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().
		LoadGameImage("circle25", Dir.PathToPlusFileName("circle25.bmp"));
	loadingImage->Cut({ 50,50 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("circle50", Dir.PathToPlusFileName("circle50.bmp"));
	loadingImage->Cut({ 100,100 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("circle75", Dir.PathToPlusFileName("circle75.bmp"));
	loadingImage->Cut({ 150,150 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("circle100", Dir.PathToPlusFileName("circle100.bmp"));
	loadingImage->Cut({ 200,200 });


	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("elipse100", Dir.PathToPlusFileName("elipse100.bmp"));
	loadingImage->Cut({ 300,300 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("elipse75", Dir.PathToPlusFileName("elipse75.bmp"));
	loadingImage->Cut({ 224,224 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("elipse50", Dir.PathToPlusFileName("elipse50.bmp"));
	loadingImage->Cut({ 150,150 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("elipse25", Dir.PathToPlusFileName("elipse25.bmp"));
	loadingImage->Cut({ 74,74 });

	//말풍선 효과음, 아직 사용 안됨

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("exbiff", Dir.PathToPlusFileName("exbiff.bmp"));
	loadingImage->Cut({ 60,60 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("exfoom", Dir.PathToPlusFileName("exfoom.bmp"));
	loadingImage->Cut({ 100,100 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("expoot", Dir.PathToPlusFileName("expoot.bmp"));
	loadingImage->Cut({ 70,70 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("expow", Dir.PathToPlusFileName("expow.bmp"));
	loadingImage->Cut({ 60,60 });

	//


	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("flame1", Dir.PathToPlusFileName("flame1.bmp"));
	loadingImage->Cut({ 60,60 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("flame2", Dir.PathToPlusFileName("flame2.bmp"));
	loadingImage->Cut({ 60,60 });


	// 아직 사용 안됨(클레스 없음)
	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("skdsmoke", Dir.PathToPlusFileName("skdsmoke.bmp"));
	loadingImage->Cut({ 20,20 });
	//

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smkdrk20", Dir.PathToPlusFileName("smkdrk20.bmp"));
	loadingImage->Cut({ 20,20 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smkdrk30", Dir.PathToPlusFileName("smkdrk30.bmp"));
	loadingImage->Cut({ 30,30 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smkdrk40", Dir.PathToPlusFileName("smkdrk40.bmp"));
	loadingImage->Cut({ 40,40 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smklt25", Dir.PathToPlusFileName("smklt25.bmp"));
	loadingImage->Cut({ 44,44 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smklt50", Dir.PathToPlusFileName("smklt50.bmp"));
	loadingImage->Cut({ 60,60 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smklt75", Dir.PathToPlusFileName("smklt75.bmp"));
	loadingImage->Cut({ 90,90 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smklt100", Dir.PathToPlusFileName("smklt100.bmp"));
	loadingImage->Cut({ 134,134 });



	//petrol

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol60", Dir.PathToPlusFileName("petrol60.bmp"));
	loadingImage->Cut({ 60,60 }); //20

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol50", Dir.PathToPlusFileName("petrol50.bmp"));
	loadingImage->Cut({ 50,50 }); //20

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol40", Dir.PathToPlusFileName("petrol40.bmp"));
	loadingImage->Cut({ 40,40 }); //20

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol30", Dir.PathToPlusFileName("petrol30.bmp"));
	loadingImage->Cut({ 30,30 }); //20

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol20", Dir.PathToPlusFileName("petrol20.bmp"));
	loadingImage->Cut({ 20,20 }); //20

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol10", Dir.PathToPlusFileName("petrol10.bmp"));
	loadingImage->Cut({ 10,10 }); //10


	//petrol-

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol-1", Dir.PathToPlusFileName("petrol-1.bmp"));
	loadingImage->Cut({ 60,60 }); //64

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol-2", Dir.PathToPlusFileName("petrol-2.bmp"));
	loadingImage->Cut({ 60,60 }); //64

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol-3", Dir.PathToPlusFileName("petrol-3.bmp"));
	loadingImage->Cut({ 60,60 }); //64

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("petrol-4", Dir.PathToPlusFileName("petrol-4.bmp"));
	loadingImage->Cut({ 60,60 }); //64


	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("kamismk", Dir.PathToPlusFileName("kamismk.bmp"));
	loadingImage->Cut({ 60,60 }); //64
}

void LoadSoundInit()
{
	// 사운드 로드
	{
		GameEngineDirectroy Dir = GameEngineDirectroy();
		Dir.MoveParent("Worms_Armageddon");

		if (false == Dir.MoveChild("\\Resources\\Sound\\BGM"))
		{
			GameEngineDebug::AssertFalse();
			return;
		}

		//GameEngineSound::GetInst().LoadSound("01_generic", Dir.PathToPlusFileName("ingame_01_generic.wav"));
		//GameEngineSound::GetInst().LoadSound("02_cavern", Dir.PathToPlusFileName("ingame_02_cavern.wav"));
		//GameEngineSound::GetInst().LoadSound("03_jungle", Dir.PathToPlusFileName("ingame_03_jungle.wav"));
		//GameEngineSound::GetInst().LoadSound("04_battlezone", Dir.PathToPlusFileName("ingame_04_battlezone.wav"));
		//GameEngineSound::GetInst().LoadSound("05_forest", Dir.PathToPlusFileName("ingame_05_forest.wav"));
		//GameEngineSound::GetInst().LoadSound("06_weird_alien_plan", Dir.PathToPlusFileName("ingame_06_weird_alien_plan.wav"));
		//GameEngineSound::GetInst().LoadSound("07_outerspace", Dir.PathToPlusFileName("ingame_07_outerspace.wav"));
		//GameEngineSound::GetInst().LoadSound("08_desert", Dir.PathToPlusFileName("ingame_08_desert.wav"));
		//GameEngineSound::GetInst().LoadSound("09_hellest", Dir.PathToPlusFileName("ingame_09_hellest.wav"));
		//GameEngineSound::GetInst().LoadSound("10_mech_workshop", Dir.PathToPlusFileName("ingame_10_mech_workshop.wav"));
		//GameEngineSound::GetInst().LoadSound("11_rain_surf", Dir.PathToPlusFileName("ingame_11_rain_surf.wav"));
		//GameEngineSound::GetInst().LoadSound("lose", Dir.PathToPlusFileName("new_lose.wav"));
		//GameEngineSound::GetInst().LoadSound("win_bronze", Dir.PathToPlusFileName("new_win_bronze.wav"));
		//GameEngineSound::GetInst().LoadSound("win_gold", Dir.PathToPlusFileName("new_win_gold.wav"));
		//GameEngineSound::GetInst().LoadSound("win_gold_special", Dir.PathToPlusFileName("new_win_gold_special.wav"));
		//GameEngineSound::GetInst().LoadSound("win_silver", Dir.PathToPlusFileName("new_win_silver.wav"));
		//GameEngineSound::GetInst().LoadSound("Stats", Dir.PathToPlusFileName("Stats.wav"));
		//GameEngineSound::GetInst().LoadSound("suddendeath1_loop", Dir.PathToPlusFileName("suddendeath1_loop.wav"));
		//GameEngineSound::GetInst().LoadSound("suddendeath2_loop", Dir.PathToPlusFileName("suddendeath2_loop.wav"));
		//GameEngineSound::GetInst().LoadSound("title", Dir.PathToPlusFileName("title.wav"));

		//if (false == Dir.MoveChild("\\Resources\\Sound\\Effects\\"))
		//{
		//	GameEngineDebug::AssertFalse();
		//	return;
		//}

		//if (false == Dir.MoveChild("\\Resources\\Sound\\BGM\\"))
		//{
		//	GameEngineDebug::AssertFalse();
		//	return;
		//}

		//if (false == Dir.MoveChild("\\Resources\\Sound\\English\\"))
		//{
		//	GameEngineDebug::AssertFalse();
		//	return;
		//}
	}
}

void TitleLevelInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms_Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	// Fade In/Out Image Load
	GameEngineImage::GetInst().LoadGameImage("Fade_Black", Dir.PathToPlusFileName("Fade_Black.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Fade_White", Dir.PathToPlusFileName("Fade_White.bmp"));

	// Intro Logo1
	GameEngineImage::GetInst().LoadGameImage("Intro_Logo1", Dir.PathToPlusFileName("Intro_Logo1.bmp"));

	// Intro Logo2
	GameEngineImage::GetInst().LoadGameImage("Intro_Logo2", Dir.PathToPlusFileName("Intro_Logo2.bmp"));

	// Title Logo
	GameEngineImage::GetInst().LoadGameImage("Title_Logo", Dir.PathToPlusFileName("Title_Logo.bmp"));

	// Title Logo Animation
	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().LoadGameImage("TitleLogo_Actor", Dir.PathToPlusFileName("TitleLogo_Actor.bmp"));
	loadingImage->Cut({ 140, 140 });

	// Title Logo Armageddon Text
	GameEngineImage::GetInst().LoadGameImage("Armageddon_1", Dir.PathToPlusFileName("Armageddon_1.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_2", Dir.PathToPlusFileName("Armageddon_2.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_3", Dir.PathToPlusFileName("Armageddon_3.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_4", Dir.PathToPlusFileName("Armageddon_4.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_5", Dir.PathToPlusFileName("Armageddon_5.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_6", Dir.PathToPlusFileName("Armageddon_6.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_7", Dir.PathToPlusFileName("Armageddon_7.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_8", Dir.PathToPlusFileName("Armageddon_8.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_9", Dir.PathToPlusFileName("Armageddon_9.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Armageddon_10", Dir.PathToPlusFileName("Armageddon_10.bmp"));

	// Title BackDrop
	GameEngineImage::GetInst().LoadGameImage("Title_Backdrop", Dir.PathToPlusFileName("Title_Backdrop.bmp"));
}

void MenuSelectInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms_Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	// MenuSelect Level Backdrop
	GameEngineImage::GetInst().LoadGameImage("MenuSel_BackDrop", Dir.PathToPlusFileName("Lobby_Backdrop.bmp"));

	// MenuSelect Level Title
	GameEngineImage::GetInst().LoadGameImage("MenuSel_Title", Dir.PathToPlusFileName("MenuSel_Title.bmp"));

	// MenuSelect Image(Lobby 진입 메뉴)
	GameEngineImage::GetInst().LoadGameImage("MenuSelect_Image", Dir.PathToPlusFileName("MenuSelect_Image.bmp"));
	GameEngineImage::GetInst().LoadGameImage("MenuSelect_Image_col", Dir.PathToPlusFileName("MenuSelect_Image_col.bmp"));

}
