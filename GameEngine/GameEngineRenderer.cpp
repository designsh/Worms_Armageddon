#include "GameEngineRenderer.h"
#include <GameEngineDebug.h>
#include <GameEngineTime.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"
#include "GameEngineActor.h"

GameEngineRenderer::FrameAnimation::FrameAnimation()
	: start_(-1),
	end_(-1),
	cur_(-1),
	curframeTime_(0.0f),
	renderer_(nullptr),
	pivot_(RENDERPIVOT::BOT),
	loop_(nullptr),
	image_(nullptr),
	isend_(false),
	reverse_(false)
{

}

GameEngineRenderer::FrameAnimation::FrameAnimation(const FrameAnimation& obj)
	: start_(-1),
	end_(-1),
	cur_(-1),
	curframeTime_(0.0f),
	renderer_(nullptr),
	pivot_(RENDERPIVOT::BOT),
	loop_(nullptr),
	image_(nullptr),
	isend_(false),
	reverse_(false)
{
	//*this = obj;

	//frameTime_.resize((int)(obj.frameTime_.size()));

	//std::copy(obj.frameTime_.begin(), obj.frameTime_.end(), frameTime_.begin());
}

GameEngineRenderer::FrameAnimation::~FrameAnimation()
{
	auto iterfirst = FrameFunctionList_.begin();
	auto iterEnd = FrameFunctionList_.end();
	for (; iterfirst != iterEnd; ++iterfirst)
	{
		delete *iterfirst;
	}
}

void GameEngineRenderer::FrameAnimation::Update()
{
	isend_ = false;
	curframeTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.0f >= curframeTime_)
	{
		++cur_;
		auto iter1 = FrameFunctionList_.begin();
		auto iter2 = FrameFunctionList_.end();
		for (; iter1 != iter2; ++iter1)
		{
			if ((*iter1)->Frame_ == cur_)
			{
				(*iter1)->FrameFunction_();
			}
		}

		if (end_ < cur_)
		{
			if (nullptr != EndFunction_)
			{
				EndFunction_();
			}

			isend_ = true;

			if (true == loop_)
			{
				cur_ = start_;
			}
			else
			{
				--cur_;
			}
		}
		curframeTime_ = frameTime_[cur_ - start_];
	}

	renderer_->SetCutIndex(cur_, pivot_);
	renderer_->Render();
}

void GameEngineRenderer::FrameAnimation::UpdateReverseLoop()
{
	curframeTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.0f >= curframeTime_)
	{
		if (cur_ == 0)
		{
			reverse_ = false;
		}

		if (false == reverse_)
		{
			++cur_;
		}
		else
		{
			--cur_;
		}

		if (false == FrameFunctionList_.empty())
		{
			auto iter1 = FrameFunctionList_.begin();
			auto iter2 = FrameFunctionList_.end();
			for (; iter1 != iter2; ++iter1)
			{
				if ((*iter1)->Frame_ == cur_)
				{
					(*iter1)->FrameFunction_();
				}
			}
		}

		if (end_ == cur_)
		{
			if (nullptr != EndFunction_)
			{
				EndFunction_(); 
			}

			reverse_ = true;
		}
		curframeTime_ = frameTime_[cur_ - start_];
	}

	renderer_->SetCutIndex(cur_, pivot_);
	renderer_->Render();
}

// Static Var
// Static Func

// constructer destructer
GameEngineRenderer::GameEngineRenderer()
	: imagePivot_(float4::ZERO),
	pivotpos_(float4::ZERO),
	rendersize_(float4::ZERO),
	imagepos_(float4::ZERO),
	imagesize_(float4::ZERO),
	isCamEffect_(true),
	rotate_(0.0f),
	alpha_(255),
	curani_(0),
	actor_(nullptr),
	image_(nullptr),
	maskimage_(nullptr)

{
}

GameEngineRenderer::~GameEngineRenderer()
{
	std::map<std::string, FrameAnimation*>::iterator AniStart = allAnimation_.begin();
	std::map<std::string, FrameAnimation*>::iterator AniEnd = allAnimation_.end();

	for (; AniStart != AniEnd; ++AniStart)
	{
		if (nullptr == AniStart->second)
		{
			continue;
		}

		delete AniStart->second;
		AniStart->second = nullptr;
	}

	allAnimation_.clear();
}

GameEngineRenderer::GameEngineRenderer(const GameEngineRenderer& _other)
	: imagePivot_(float4::ZERO),
	pivotpos_(float4::ZERO),
	rendersize_(float4::ZERO),
	imagepos_(float4::ZERO),
	imagesize_(float4::ZERO),
	isCamEffect_(true),
	rotate_(0.0f),
	alpha_(255),
	curani_(0),
	actor_(nullptr),
	image_(nullptr),
	maskimage_(nullptr)
{
	//*this = _other;

	//allAnimation_.clear();
	//std::copy(_other.allAnimation_.begin(), _other.allAnimation_.end(), allAnimation_.begin());

	//actor_ = nullptr;
	//SetParent(nullptr);
}

//GameEngineRenderer::GameEngineRenderer(GameEngineRenderer&& _other) noexcept
//{
//
//}

//member Func

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	image_ = GameEngineImage::GetInst().FindGameImage(_Name);

	if (nullptr == image_)
	{
		GameEngineDebug::AssertFalse();
	}

	imagepos_ = float4::ZERO;
	imagesize_ = image_->GetSize();
	rendersize_ = image_->GetSize();
	imagePivot_ = rendersize_.halffloat4();
}

void GameEngineRenderer::SetImageNoSize(const std::string& _name)
{
	image_ = GameEngineImage::GetInst().FindGameImage(_name);

	if (nullptr == image_)
	{
		GameEngineDebug::AssertFalse();
	}
}

void GameEngineRenderer::SetMaskImage(const std::string& _Name) 
{
	maskimage_ = GameEngineImage::GetInst().FindGameImage(_Name);

	if (nullptr == maskimage_)
	{
		GameEngineDebug::AssertFalse();
	}
}


void GameEngineRenderer::Render()
{
	GameEngineImageFile* WindowImage = GameEngineImage::GetInst().GetBackBufferImage();

	float4 ActorPos = actor_->GetCamEffectPos();

	if (false == isCamEffect_)
	{
		ActorPos = actor_->GetPos();
	}

	float4 RenderPos = ActorPos + pivotpos_ - imagePivot_;

	if (0.0f == rotate_)
	{

		if (alpha_ == 255)
		{
			WindowImage->TransCopy(image_,
				RenderPos,
				rendersize_,
				imagepos_,
				imagesize_,
				RGB(255, 0, 255));
		}
		else 
		{
			WindowImage->AlphaCopy(image_, 
				alpha_,
				RenderPos,
				rendersize_,
				imagepos_,
				imagesize_);
		}

	}
	else 
	{
		WindowImage->PlgCopy(image_,
			maskimage_,
			rotate_,
			RenderPos,
			rendersize_,
			imagepos_,
			imagesize_);
	}
}


void GameEngineRenderer::SetCutIndex(size_t _Index, RENDERPIVOT _Pivot)
{
#ifdef _DEBUG	
	if (false == image_->IsCut())
	{
		GameEngineDebug::AssertFalse();
		return;
	}
#endif // DEBUG

	imagepos_ = image_->GetCutPos(_Index);
	imagesize_ = image_->GetCutSize(_Index);
	rendersize_ = imagesize_;

	// w
	imagePivot_ = rendersize_.halffloat4();

	switch (_Pivot)
	{
	case RENDERPIVOT::LEFTTOP:
		imagePivot_ = float4::ZERO;
		break;
	case RENDERPIVOT::CENTER:
		imagePivot_ = rendersize_.halffloat4();
		break;
	case RENDERPIVOT::BOT:
		imagePivot_ = rendersize_.halffloat4();
		imagePivot_.y += rendersize_.halffloat4().y;
		break;
	default:
		GameEngineDebug::AssertFalse();
		break;
	}

}

GameEngineRenderer::FrameAnimation* GameEngineRenderer::FindAnimation(const std::string& _name)
{
	std::map<std::string, FrameAnimation*>::iterator FindAniIter = allAnimation_.find(_name);

	if (FindAniIter == allAnimation_.end())
	{
		return nullptr;
	}

	return FindAniIter->second;
}

void GameEngineRenderer::ChangeAnimation(const std::string& _Name, bool _forceChange /*= false*/)
{
	// 기존 애니메이션도 진행하고 있고
	if (nullptr != curani_ &&
		// 강제바꾸기가 아니고
		false == _forceChange &&
		// 애니메이션 이름이 같으면
		curani_->GetName() == _Name)
	{
		return;
	}

	curani_ = FindAnimation(_Name);
	curani_->Reset();

#ifdef _DEBUG	
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}
#endif // DEBUG
}

void GameEngineRenderer::ChangeAnimation(const std::string& _Name, const std::string& _name, bool _forceChange)
{
	// 기존 애니메이션도 진행하고 있고
	if (nullptr != curani_ &&
		// 강제바꾸기가 아니고
		false == _forceChange &&
		// 애니메이션 이름이 같으면
		curani_->GetName() == _Name)
	{
		return;
	}

	SetImageNoSize(_name);
	curani_ = FindAnimation(_Name);
	curani_->Reset();

#ifdef _DEBUG	
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}
#endif // DEBUG
}

void GameEngineRenderer::CreateAnimation(
	const std::string& _Name, // idle,
	const std::string& _ImageName, // ,
	int _Start,
	int _End,
	bool _Loop /*= true*/,
	float _FrameTime /*= 0.1f*/,
	RENDERPIVOT pivot_ /*= RENDERPIVOT::CENTER*/
)
{
	GameEngineImageFile* ImagePtr = GameEngineImage::GetInst().FindGameImage(_ImageName);

#ifdef _DEBUG	
	if (nullptr != FindAnimation(_Name))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	if (nullptr == ImagePtr)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	if (false == ImagePtr->IsCut())
	{
		GameEngineDebug::AssertFalse();
		return;
	}
#endif // DEBUG

	FrameAnimation* NewAnimation = new FrameAnimation();

	NewAnimation->SetName(_Name);
	NewAnimation->start_ = _Start;
	NewAnimation->end_ = _End;

	NewAnimation->frameTime_.reserve(NewAnimation->end_ - NewAnimation->start_);
	for (size_t i = 0; i < (NewAnimation->end_ - NewAnimation->start_) + 1; i++)
	{
		NewAnimation->frameTime_.push_back(_FrameTime);
	}
	NewAnimation->image_ = ImagePtr;
	NewAnimation->cur_ = _Start;
	NewAnimation->curframeTime_ = _FrameTime;
	NewAnimation->pivot_ = pivot_;
	NewAnimation->renderer_ = this;
	NewAnimation->loop_ = _Loop;

	allAnimation_.insert(std::map<std::string, FrameAnimation*>::value_type(_Name, NewAnimation));

}

void GameEngineRenderer::AnimationUpdate()
{
#ifdef _DEBUG	
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}
#endif // DEBUG

	curani_->Update();
}

void GameEngineRenderer::AnimationUpdateReverseLoop()
{
#ifdef _DEBUG	
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}
#endif // DEBUG

	curani_->UpdateReverseLoop();
}

bool GameEngineRenderer::IsCurAnimationName(const std::string& _Name)
{
#ifdef _DEBUG	
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}
#endif // DEBUG

	if (curani_->GetName() == _Name)
	{
		return true;
	}

	return false;
}

bool GameEngineRenderer::IsCurAnimationEnd()
{
#ifdef _DEBUG	
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}
#endif // DEBUG

	return curani_->end_ == curani_->cur_;
}

void GameEngineRenderer::SetChangeFrame(const std::string& _Name, int _index, float _Time)
{
	FrameAnimation* FindAni = FindAnimation(_Name);

#ifdef _DEBUG	
	if (nullptr == FindAni)
	{
		GameEngineDebug::AssertFalse();
		return;
	}
#endif // DEBUG

	FindAni->frameTime_[static_cast<size_t>(_index - FindAni->start_)] = _Time;

}

int GameEngineRenderer::GetCurAnimationFrame()
{
#ifdef _DEBUG	
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}
#endif // DEBUG

	return curani_->cur_;
}

std::string GameEngineRenderer::GetCurAnimationName()
{
	return curani_->GetName();
}

void GameEngineRenderer::CurAnimationLoopEnd()
{
	curani_->loop_ = false;
}

void GameEngineRenderer::CurAnimationReset()
{
	curani_->cur_ = 0;
	if (true == curani_->loop_)
	{
		CurAnimationLoopEnd();
	}
}
