#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <GameEngineMath.h>
#include <GameEngineNameBase.h>
#include <GameEngineDebug.h>
// ����� ���� �ڷ���
// ���� ����(�ϳ��� ��ü�� ��� ���¸� �����ٰ� �Ҷ�)�� 
// ��������� ǥ���ϰ� ������ ���� ����մϴ�.
enum class RENDERPIVOT
{
	CENTER,
	BOT,
	LEFTTOP,
	MAX,
};

// �з� : ������
// �뵵 : �׸��� �׸��µ� �ʿ��� ���Ǳ���� �����Ѵ�.
// ���� : ���Ͱ� �����ϸ� �������� �ʿ��� ���Ǳ�� ����
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

		// ���ϸ��̼� ������ ȣ�� �Լ� : ���� // ������� ����
		struct AnimationNotify
		{
			int             Frame_; //�Լ� ȣ�� ������
			std::function<void()>   FrameFunction_; //ȣ�� �Լ�
		};

		std::function<void()>   EndFunction_; //���ϸ��̼� ���� �Լ�
		std::list<AnimationNotify*>   FrameFunctionList_; //������ ȣ�� �Լ� ����Ʈ
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
	GameEngineRenderer(); // default constructer ����Ʈ ������
	~GameEngineRenderer(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineRenderer(const GameEngineRenderer& _other);// = delete; // default Copy constructer ����Ʈ ���������
	//GameEngineRenderer(GameEngineRenderer&& _other);// noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

//public:		//delete operator
	//GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	//GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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



		void SetAnimationCurrentFrame(const std::string& _Name, const int index) // ���ϸ��̼� cur_ �����ϴ� �Լ� 
		{
			FindAnimation(_Name)->cur_ = index;
		}

		void SetAnimationCurrentFrame(const int index) // ���ϸ��̼� cur_ �����ϴ� �Լ� 
		{
			curani_->cur_ = index;
		}

		// ���ϸ��̼� ������ ȣ���Լ� : ����
		template <typename T>
		void SetAnimationEndFunction(const std::string& Name, T* pObj,
			void (T::* pFunc)())
		{
			FrameAnimation* fInfo = FindAnimation(Name);

			if (nullptr == fInfo)
			{
				GameEngineDebug::MsgBoxError("���ϸ��̼��� �������� �ʾ� ȣ�� �Լ��� �������� ���߽��ϴ�.");
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
				GameEngineDebug::MsgBoxError("���ϸ��̼��� �������� �ʾ� ȣ�� �Լ��� �������� ���߽��ϴ�.");
				return;
			}

			if (fInfo->end_ < Frame)
			{
				GameEngineDebug::MsgBoxError("���ϸ��̼� �Լ��� ȣ�� ������ ���ϸ��̼��� �����Ӻ��� Ů�ϴ�.");
				return;
			}
			FrameAnimation::AnimationNotify* fNotify = new FrameAnimation::AnimationNotify;

			fNotify->Frame_ = Frame;
			fNotify->FrameFunction_ = std::bind(pFunc, pObj);

			fInfo->FrameFunctionList_.push_back(fNotify);
		}
		//


};

