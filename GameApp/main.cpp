// 00AR38Start.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <GameEngineWindow.h>
#include <Windows.h>
#include <GameEngineDebugExtension.h>
#include <GameEngineLevelManager.h>
#include <GameEngineActor.h>

#include <TitleLevel.h>
#include <MenuSelectLevel.h>
#include <LobbyLevel.h>
#include <LoadingLevel.h>
#include <PlayLevel.h>
#include <EndingLevel.h>


#include <GameEngineMath.h>
#include <GameEngineInput.h>
#include <GameEngineSoundManager.h>
#include <GameEngineMath.h>
#include "AppFunc.h"

void UpdateFunc() 
{
	//GameEngineDebugExtension::Update();
	GameEngineLevelManager::GetInst().Update();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 디버깅 기본 기능 실행
	GameEngineDebugExtension::LeakCheckOn();

	GameEngineSoundManager::GetInstance().Initialize();
	// 윈도우 생성 및 기본 윈도우 창에서 게임을 돌릴 준비를 한다.
	GameEngineWindow::GetInst().CreateMainWindowClass(hInstance, "GameWindow");
	GameEngineWindow::GetInst().CreateMainWindow("MyWindow", { 1280, 720 }, {0, 0});
	//GameEngineDebugExtension::DebugWindowOpen({ 500, 500 }, { 0, 0 });
	
	AppResourcesInit();

	// 각 씬을 생성하고 로딩을 완료한후
	// 최초 만들어질 씬을 지정한다.
	GameEngineLevelManager::GetInst().CreateLevel<TitleLevel>("TitleLevel");
	GameEngineLevelManager::GetInst().CreateLevel<MenuSelectLevel>("MenuSelectLevel");
	GameEngineLevelManager::GetInst().CreateLevel<LobbyLevel>("LobbyLevel");
	GameEngineLevelManager::GetInst().CreateLevel<PlayLevel>("PlayLevel");
	GameEngineLevelManager::GetInst().CreateLevel<EndingLevel>("EndingLevel");


	// 최초 씬 지정.
	GameEngineLevelManager::GetInst().ChangeLevel("TitleLevel");

	GameEngineWindow::GetInst().Loop(UpdateFunc);

	AppRelease();
}
