#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineWindow.h>
#include <GameEngineDebugExtension.h>
#include <GameEngineTime.h>

#include "LoadingImage.h"
#include "BackGroundGradation.h"
#include "MouseObject.h"
#include "MapTrain.h"
#include "PlayLevel.h"
#include "Worm.h"
#include "GameController.h"
#include "Bazooka.h"
#include "Uzi.h"
#include "UziBullet.h"

#include "BottomHealthBar.h"
#include "BottomNameTag.h"
#include "BottomFlag.h"
#include "WindBarBlank.h"
#include "WindBar.h"
#include "WindBarHider.h"

#include "WaterWave.h"
#include "UnderWater.h"

#include "EffectActor.h"
#include "ExplosionSize.h"
#include "Effectkamismk.h"

#include "DrumActor.h"
#include "Grave.h"

#include "BackgroundScatter.h"
#include "PetroleumManager.h"
#include "Midground.h"
#include "WindController.h"
#include "FadeObject.h"
#include "Cloud.h"

#include "GameOptionInfo.h"


FadeObject* PlayLevel::fadeObject_ = nullptr;

PlayLevel::PlayLevel() // default constructer 디폴트 생성자
	: Train_(nullptr),
	Bazooka_(nullptr),
	loadingImage_(nullptr),
	isDebugOn_(true),
	randomGenerator_(),
	isWormLanded_(false),// default constructer 디폴트 생성자
	fadeInterTime_(0.0f),
	isFadeIn_(false),
	Controller_(nullptr),
	MouseObject_(nullptr)
{

}

PlayLevel::~PlayLevel() // default destructer 디폴트 소멸자
{

}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자	
	: Train_(nullptr),
	Bazooka_(nullptr),
	loadingImage_(nullptr),
	isDebugOn_(true),
	randomGenerator_(),
	isWormLanded_(false),
	fadeInterTime_(0.0f),
	isFadeIn_(false),
	Controller_(nullptr),
	MouseObject_(nullptr)
{

}

void PlayLevel::Loading()
{
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}
	
	fadeObject_ = CreateActor<FadeObject>();
	loadingImage_ = CreateActor<LoadingImage>();

	CreateActor<BackGroundGradation>();
	Train_ = CreateActor<MapTrain>();
	Train_->UpdateBefore();

	//{
	//	windController_ = CreateActor<WindController>();
	//}



	//for (int i = 0; i < 50; i++)
	//{
	//	Cloud* newCloud = CreateActor<Cloud>();
	//	newCloud->SetParent(windController_);
	//}

	// 뒷배경 생성
	CreateActor<Midground>();
	wormLoading();
	KeySetting();
}

void PlayLevel::LevelUpdate()
{
	PJWLevelUpdate();

	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{

		//GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}

	{
		// 디버깅 출력 내용입니다.
		GameEngineDebugExtension::PrintDebugWindowText("Resolution : ", GameEngineWindow::GetInst().GetSize().x, " X ", GameEngineWindow::GetInst().GetSize().y);
		GameEngineDebugExtension::PrintDebugWindowText("FPS : ", GameEngineTime::GetInst().GetFPS());
		GameEngineDebugExtension::PrintDebugWindowText("CamPos X : ", GetCamPos().ix(), ", CamPos Y : ", GetCamPos().iy());
		GameEngineDebugExtension::PrintDebugWindowText("Mouse X : ", GameEngineWindow::GetInst().GetMousePos().x, ", Mouse Y : ", GameEngineWindow::GetInst().GetMousePos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Mouse+CamPos X : ", GameEngineWindow::GetInst().GetMousePos().x + GetCamPos().ix(), ", Mouse+CamPos Y : ", GameEngineWindow::GetInst().GetMousePos().y+ GetCamPos().iy());

		for (int i = 0; i < GameOptionInfo::CurWormCnt; ++i)
		{
			//std::string WormName = "Worm ";
			//WormName += std::to_string(i + 1);

			//GameEngineDebugExtension::PrintDebugWindowText(WormName + "Pos X : ", Controller_->GetWormList()[i]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[i]->GetPos().y);
		}


		//GameEngineDebugExtension::PrintDebugWindowText("Worm 1 Pos X : ", Controller_->GetWormList()[0]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[0]->GetPos().y);
		//GameEngineDebugExtension::PrintDebugWindowText("Worm 2 Pos X : ", Controller_->GetWormList()[1]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[1]->GetPos().y);
		//GameEngineDebugExtension::PrintDebugWindowText("Worm 3 Pos X : ", Controller_->GetWormList()[2]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[2]->GetPos().y);
		//GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", Controller_->GetWormList()[3]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[3]->GetPos().y);
		//GameEngineDebugExtension::PrintDebugWindowText("Worm 5 Pos X : ", Controller_->GetWormList()[4]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[4]->GetPos().y);
		//GameEngineDebugExtension::PrintDebugWindowText("Worm 6 Pos X : ", Controller_->GetWormList()[5]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[5]->GetPos().y);
//		GameEngineDebugExtension::PrintDebugWindowText("Worm 7 Pos X : ", Controller_->GetWormList()[6]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[6]->GetPos().y);
//		GameEngineDebugExtension::PrintDebugWindowText("Worm 8 Pos X : ", Controller_->GetWormList()[7]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[7]->GetPos().y);


		GameEngineDebugExtension::PrintDebugWindowText("Wind Direction : ", Controller_->GetWindController()->GetCurrentWindDir(), ", Wind Speed : ", Controller_->GetWindController()->GetCurrentWindSpeed());
		GameEngineDebugExtension::PrintDebugWindowText("Water Level : ", Controller_->GetWaterLevel());
	}
}

const float PlayLevel::GetWaterLevel()
{
	return Controller_->GetWaterLevel();
}

void PlayLevel::wormLoading()
{
	Controller_ = CreateActor<GameController>("GameController");


	float4 minMaxInfo = GameOptionInfo::MapMinMaxInfo[GameOptionInfo::CurPlayMap];

	for (size_t i = 0; i < GameOptionInfo::CurWormCnt; i++)
	{
		Controller_->CreateWorm(minMaxInfo.x, minMaxInfo.y);
		Controller_->CreateDrum(minMaxInfo.x, minMaxInfo.y);
	}

	MouseObject_ = CreateActor<MouseObject>("PlayLevelMouse");
	MouseObject_->SetGameController(Controller_);

	// 플레이어별 UIController 생성
	Controller_->CreateWormUI();
	GameEngineTime::GetInst().TimeCheck();
}

void PlayLevel::CreateExplosion100(float4 Pos, int _Damage, bool _DamageToDist)
{
	ExplosionSize100* actor = CreateActor<ExplosionSize100>
		(Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
	actor->SetDamage(_Damage, _DamageToDist);

	GroundUpdate100(Pos);
}

void PlayLevel::CreateExplosion75(float4 Pos, int _Damage, bool _DamageToDist)
{
	ExplosionSize75* actor = CreateActor<ExplosionSize75>
		(Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
	actor->SetDamage(_Damage, _DamageToDist);

	GroundUpdate75(Pos);
}

void PlayLevel::CreateExplosion50(float4 Pos, int _Damage, bool _DamageToDist)
{
	ExplosionSize50* actor = CreateActor<ExplosionSize50>
		(Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
	actor->SetDamage(_Damage, _DamageToDist);

	GroundUpdate50(Pos);
}

void PlayLevel::CreateExplosion25(float4 Pos, int _Damage, bool _DamageToDist)
{
	ExplosionSize25* actor = CreateActor<ExplosionSize25>
		(Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
	actor->SetDamage(_Damage, _DamageToDist);

	GroundUpdate25(Pos);
}

void PlayLevel::CreateGrave(float4 Pos)
{
	CreateActor<Grave>(Pos);
}

void PlayLevel::CreatePurpleStarEffect(float4 Pos)
{
	CreateActor<Effect::kamismk>(Pos);
}

void PlayLevel::GroundUpdate100(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 56.f, _pos.y - 56.f);
	Train_->GroundUpdate100(_Pos);
}

void PlayLevel::GroundUpdate75(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 43.5f, _pos.y - 43.5f);

	Train_->GroundUpdate75(_Pos);
}

void PlayLevel::GroundUpdate50(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 31.f, _pos.y -31.f);
	Train_->GroundUpdate50(_Pos);
}

void PlayLevel::GroundUpdate25(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 18.5f, _pos.y - 18.5f);
	Train_->GroundUpdate25(_Pos);
}

void PlayLevel::GroundUpdate13(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 12.5f, _pos.y- 12.5f);
	Train_->GroundUpdate13(_Pos);
}

void PlayLevel::GroundUpdate6(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 9.f, _pos.y - 9.f);
	Train_->GroundUpdate6(_Pos);
}

void PlayLevel::GroundUpdate4(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 8.f, _pos.y - 8.f);
	Train_->GroundUpdate4(_Pos);
}

void PlayLevel::KeySetting()
{
	if (false == GameEngineInput::GetInst().IsKey("TestWaterLevelUp"))
	{
		GameEngineInput::GetInst().CreateKey("TestWaterLevelUp", 'Q');
	}

	if (false == GameEngineInput::GetInst().IsKey("TestWaterLevelDown"))
	{
		GameEngineInput::GetInst().CreateKey("TestWaterLevelDown", 'E');
	}
}

void PlayLevel::CreateGimmickObject()
{
	DrumActor* DrumActor1 = CreateActor<DrumActor>(MouseObject_->GetPos()+ GetCamPos());
}

void PlayLevel::PJWLevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Toggle"))
	{
		if (true == isDebugOn_)
		{
			GameEngineDebugExtension::DebugWindowClose();

			isDebugOn_ = false;
			return;
		}
		GameEngineDebugExtension::DebugWindowOpen({ 500, 500 }, { 0, 0 });
		isDebugOn_ = true;
		return;
	}

	if (false == loadingImage_->IsOn() && false == isFadeIn_)
	{
		fadeObject_->SetFadeOutSpeed(200.0f);
		fadeObject_->FadeOut();
		isFadeIn_ = true;
	}
}
