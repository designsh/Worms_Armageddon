#include "GameEngineImage.h"
#include "GameEngineImageFile.h"
#include <GameEngineDebug.h>
#include "GameEngineWindow.h"

// Static Var
// Static Func
GameEngineImage* GameEngineImage::Inst = new GameEngineImage();

// constructer destructer
GameEngineImage::GameEngineImage()
{
}

GameEngineImage::~GameEngineImage()
{
	std::map<std::string, GameEngineImageFile*>::iterator StartIter = globalManagedimages_.begin();
	std::map<std::string, GameEngineImageFile*>::iterator EndIter = globalManagedimages_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}
	globalManagedimages_.clear();

	if (nullptr != backBufferImage_)
	{
		delete backBufferImage_;
		backBufferImage_ = nullptr;
	}

	if (nullptr != windowimage_)
	{
		delete windowimage_;
		windowimage_ = nullptr;
	}
}

GameEngineImage::GameEngineImage(GameEngineImage&& _other) noexcept
{
}

void GameEngineImage::DoubleBuffering()
{
	windowimage_->BitCopy(backBufferImage_, float4::ZERO, GameEngineWindow::GetInst().GetSize());
}

void GameEngineImage::ClearBackBuffer()
{
	backBufferImage_->ClearImage();
}

GameEngineImageFile* GameEngineImage::GetBackBufferImage()
{
	return backBufferImage_;
}

void GameEngineImage::InitializeWindowImage(HDC _windowbackgroundDc)
{
	if (nullptr == _windowbackgroundDc)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	backBufferImage_ = new GameEngineImageFile();
	backBufferImage_->Create(_windowbackgroundDc, GameEngineWindow::GetInst().GetSize());

	windowimage_ = new GameEngineImageFile();
	windowimage_->Create(_windowbackgroundDc);
}

//member Func

GameEngineImageFile* GameEngineImage::FindGameImage(std::string _name)
{
	std::map<std::string, GameEngineImageFile*>::iterator FindIter 
		= globalManagedimages_.find(_name);

	if (FindIter == globalManagedimages_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

std::vector<std::string> GameEngineImage::FindAllSpecKeyImage(const std::string& _SpecKey)
{
	std::vector<std::string> Res;

	std::string SpecString = _SpecKey;

	std::map<std::string, GameEngineImageFile*>::iterator StartIter = globalManagedimages_.begin();
	std::map<std::string, GameEngineImageFile*>::iterator EndIter = globalManagedimages_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		size_t Find = 0;
		if ((Find = (*StartIter).first.find(_SpecKey)) != std::string::npos)
		{
			// 특정문자열을 포함한 키가 존재한다면
			std::string KeyName;
			KeyName = (*StartIter).first;
			Res.push_back(KeyName);
		}
	}

	return Res;
}

GameEngineImageFile* GameEngineImage::LoadGameImage(std::string _name, std::string _path)
{
	if (nullptr != FindGameImage(_name))
	{
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	GameEngineImageFile* NewImage = new GameEngineImageFile();
	if (false == NewImage->Load(_path))
	{
		delete NewImage;
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	globalManagedimages_.insert(std::map<std::string, GameEngineImageFile*>::value_type(_name, NewImage));
	return NewImage;
}