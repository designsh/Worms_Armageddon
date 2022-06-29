#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <GameEngineMath.h>
#include <GameEngineNameBase.h>
#include <GameEngineDebug.h>
// 사용자 정의 자료형
// 보통 상태(하나의 객체가 몇가지 상태를 가진다고 할때)를 
// 명시적으로 표현하고 싶을때 많이 사용합니다.
enum class RENDERPIVOT
{
	CENTER,
	BOT,
	LEFTTOP,
	MAX,
};

// 분류 : 랜더링
// 용도 : 그림을 그리는데 필요한 편의기능을 제공한다.
// 설명 : 액터가 관리하며 랜더링에 필요한 편의기능 제공
class GameEngineActor;
class GameEngineImage;
class GameEngineImageFile;
class GameEngineRenderer : public GameEngineNameBase
{
private:
	class FrameAnimation : public GameEngineNameBase
	{
		friend GameEngineRenderer;
	private:
		FrameAnimation();
		FrameAnimation(const FrameAnimation& obj);
		~FrameAnimation();

	private:
		int start_;
		int end_;
		int cur_;
		bool reverse_;
		std::vector<float> frameTime_;

		float curframeTime_;
		GameEngineRenderer* renderer_;
		GameEngineImageFile* image_;
		RENDERPIVOT pivot_;
		bool loop_;
		bool isend_;

		// 에니메이션 프레임 호출 함수 : 이현 // 복사되지 않음
		struct AnimationNotify
		{
			int             Frame_; //함수 호출 프레임
			std::function<void()>   FrameFunction_; //호출 함수
		};

		std::function<void()>   EndFunction_; //에니메이션 종료 함수
		std::list<AnimationNotify*>   FrameFunctionList_; //프레임 호출 함수 리스트
		//
	private:
		void Reset()
		{
			cur_ = start_;
			curframeTime_ = frameTime_[0];
			isend_ = false;
		}
		void Update();
		void UpdateReverseLoop();
	};

public:
	friend GameEngineActor;

private:	// member Var
	GameEngineActor* actor_;
	float4 imagePivot_;
	float4 pivotpos_;
	float4 rendersize_;
	float4 imagepos_;
	float4 imagesize_;
	GameEngineImageFile* image_;
	GameEngineImageFile* maskimage_;
	bool isCamEffect_;
	float rotate_;
	int alpha_;

private:
	void SetActor(GameEngineActor* _parent)
	{
		actor_ = _parent;
	}

public:
	GameEngineRenderer(); // default constructer 디폴트 생성자
	~GameEngineRenderer(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineRenderer(const GameEngineRenderer& _other);// = delete; // default Copy constructer 디폴트 복사생성자
	//GameEngineRenderer(GameEngineRenderer&& _other);// noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

//public:		//delete operator
	//GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	//GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	void SetCutIndex(size_t _Index, RENDERPIVOT _Pivot = RENDERPIVOT::LEFTTOP);
	void Render();

private:
	std::map<std::string, FrameAnimation*> allAnimation_;
	FrameAnimation* curani_;

private:
	FrameAnimation* FindAnimation(const std::string& _name);

public:
	void CreateAnimation(
		const std::string& _Name, // idle,
		const std::string& _ImageName, // ,
		int _Start,
		int _End,
		bool _Loop = true,
		float _FrameTime = 0.1f,
		RENDERPIVOT pivot_ = RENDERPIVOT::CENTER
	);

	bool IsCurAnimationName(const std::string& _Name);
	void ChangeAnimation(const std::string& _Name, bool _forceChange = false);
	void ChangeAnimation(const std::string& _Name, const std::string& _name, bool _forceChange = false);
	void SetChangeFrame(const std::string& _Name, int _index, float _Time);
	void AnimationUpdate();
	void AnimationUpdateReverseLoop();
	bool IsCurAnimationEnd();

	int GetCurAnimationFrame();
	std::string GetCurAnimationName();

public:
	void CurAnimationLoopEnd();
	void CurAnimationReset();

	public:
		void SetAlpha(const int _Value)
		{
			alpha_ = _Value;

			if (255 <= alpha_)
			{
				alpha_ = 255;
				return;
			}

			if (0 >= alpha_)
			{
				alpha_ = 0;
				return;
			}
		}

		void SetAddAlpha(const int _Value)
		{
			alpha_ += _Value;

			if (255 <= alpha_)
			{
				alpha_ = 255;
				return;
			}

			if (0 >= alpha_)
			{
				alpha_ = 0;
				return;
			}

		}

		void SetRotate(const float _Value)
		{
			rotate_ = _Value;
		}

		void SetAddRotate(const float _Value)
		{
			rotate_ += _Value;
		}

		void SetImagePivot(const float4& _Value)
		{
			imagePivot_ = _Value;
		}

		void SetPivotPos(const float4& _Value)
		{
			pivotpos_ = _Value;
		}

		void SetPivotMove(float4 _pos)
		{
			pivotpos_ += _pos;
		}

		void SetRenderSize(const float4& _Value)
		{
			rendersize_ = _Value;
		}
		void SetImagePos(const float4& _Value)
		{
			imagepos_ = _Value;
		}
		void SetImageSize(const float4& _Value)
		{
			imagesize_ = _Value;
		}

		void SetCameraEffectOn()
		{
			isCamEffect_ = true;
		}

		void SetCameraEffectOff()
		{
			isCamEffect_ = false;
		}

		void SetImage(const std::string& _Name);
		void SetImageNoSize(const std::string& _name);

		void SetMaskImage(const std::string& _Name);

		void SetImage(GameEngineImageFile* _image)
		{
			image_ = _image;
		}

		GameEngineImageFile* GetImage() {
			return image_;
		}

		float4 GetImageSize()
		{
			return imagesize_;
		}



		void SetAnimationCurrentFrame(const std::string& _Name, const int index) // 에니메이션 cur_ 변경하는 함수 
		{
			FindAnimation(_Name)->cur_ = index;
		}

		void SetAnimationCurrentFrame(const int index) // 에니메이션 cur_ 변경하는 함수 
		{
			curani_->cur_ = index;
		}

		// 에니메이션 프레임 호출함수 : 이현
		template <typename T>
		void SetAnimationEndFunction(const std::string& Name, T* pObj,
			void (T::* pFunc)())
		{
			FrameAnimation* fInfo = FindAnimation(Name);

			if (nullptr == fInfo)
			{
				GameEngineDebug::MsgBoxError("에니메이션이 존재하지 않아 호출 함수가 지정되지 못했습니다.");
				return;
			}

			fInfo->EndFunction_ = std::bind(pFunc, pObj);
		}

		template <typename T>
		void SetAnimationFrameFunction(const std::string& Name, int Frame,
			T* pObj, void (T::* pFunc)())
		{
			FrameAnimation* fInfo = FindAnimation(Name);

			if (nullptr == fInfo)
			{
				GameEngineDebug::MsgBoxError("에니메이션이 존재하지 않아 호출 함수가 지정되지 못했습니다.");
				return;
			}

			if (fInfo->end_ < Frame)
			{
				GameEngineDebug::MsgBoxError("에니메이션 함수의 호출 시점이 에니메이션의 프레임보다 큽니다.");
				return;
			}
			FrameAnimation::AnimationNotify* fNotify = new FrameAnimation::AnimationNotify;

			fNotify->Frame_ = Frame;
			fNotify->FrameFunction_ = std::bind(pFunc, pObj);

			fInfo->FrameFunctionList_.push_back(fNotify);
		}
		//


};

