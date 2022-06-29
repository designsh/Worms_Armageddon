#include "GameEngineDebug.h"
#include <assert.h>
#include <crtdbg.h>
#include <Windows.h>

// Static Var
// Static Func
// constructer destructer
GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug()
{
}

GameEngineDebug::GameEngineDebug(GameEngineDebug&& _other) noexcept
{
}

void GameEngineDebug::LeakCheckOn() 
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

//member Func
void GameEngineDebug::MsgBoxError(const char* _Ptr) 
{
	MessageBoxA(nullptr, _Ptr, "Error", MB_OK);
	assert(false);
}

void GameEngineDebug::AssertFalse()
{
	assert(false);
}

void GameEngineDebug::OutPutDebugString(const std::string _Text) 
{
	OutputDebugStringA(_Text.c_str());
}