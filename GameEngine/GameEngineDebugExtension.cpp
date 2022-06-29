#include "GameEngineDebugExtension.h"
#include "GameEngineWindow.h"
#include "GameEngineImageFile.h"


// Static Var
// Static Func
GameEngineWindow* GameEngineDebugExtension::debugWindow_ = nullptr;
std::stringstream GameEngineDebugExtension::Str;
std::vector<std::string> GameEngineDebugExtension::debugList_;

// constructer destructer
GameEngineDebugExtension::GameEngineDebugExtension()
{
}

GameEngineDebugExtension::~GameEngineDebugExtension()
{
}

GameEngineDebugExtension::GameEngineDebugExtension(GameEngineDebugExtension&& _other) noexcept
{
}

//member Func

void GameEngineDebugExtension::DebugWindowOpen(float4 _Size, float4 _Scale)
{
	if (nullptr == debugWindow_)
	{
		debugWindow_ = GameEngineWindow::CreateSubWindow("DebugWindow", _Size, _Scale);
		return;
	}
	else if(nullptr != debugWindow_)
	{
		ShowWindow(debugWindow_->windowhandle_, SW_SHOW);
	}
}

void GameEngineDebugExtension::DebugWindowClose()
{
	if (nullptr != debugWindow_)
	{
		ShowWindow(debugWindow_->windowhandle_, SW_HIDE);
	}
}



void GameEngineDebugExtension::Release() 
{
	if (nullptr != debugWindow_)
	{
		delete debugWindow_;
		debugWindow_ = nullptr;
	}
}

//void GameEngineDebugExtension::PrintDebugWindowText(const std::string& _Text) 
//{
//	if (nullptr == debugWindow_)
//	{
//		AssertFalse();
//	}
//
//
//	debugList_.push_back(_Text);
//}

void GameEngineDebugExtension::Update() 
{
	float4 StartPos = float4::ZERO;
	
	for (size_t i = 0; i < debugList_.size(); i++)
	{
		TextOutA(debugWindow_->GetBackBuffer()->GetDC()
			, StartPos.ix()
			, StartPos.iy()
			, debugList_[i].c_str()
			, static_cast<int>(debugList_[i].size())
		);
	
		StartPos.y += 20.0f;
	}
	
	debugList_.clear();
	
	debugWindow_->GetWindowImage()->BitCopy(debugWindow_->GetBackBuffer(), float4::ZERO, GameEngineWindow::GetInst().GetSize());
	
	Rectangle(debugWindow_->GetBackBuffer()->GetDC(),
		0,
		0,
		debugWindow_->GetSize().ix(),
		debugWindow_->GetSize().iy()
	);

}