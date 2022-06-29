#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>

// �з� :
// �뵵 :
// ���� :
class FadeObject : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	float Alpha_;
	GameEngineFSM<FadeObject> FadeState;

public:
	// �ܺο��� ����Ҷ� ���Լ��� �������� ���̴�.
	void FadeIn();
	void FadeOut();

public:		
	FadeObject(); // default constructer ����Ʈ ������
	~FadeObject(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	FadeObject(const FadeObject& _other) = delete; // default Copy constructer ����Ʈ ���������
	FadeObject(FadeObject&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	FadeObject& operator=(const FadeObject& _other) = delete; // default Copy operator ����Ʈ ���� ������
	FadeObject& operator=(const FadeObject&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Start();
	void Update();
	void Render();

private:		//member Func
	StateInfo FadeInStart(StateInfo _Info);
	StateInfo FadeOutStart(StateInfo _Info);

	StateInfo FadeInUpdate(StateInfo _Info);
	StateInfo FadeOutUpdate(StateInfo _Info);

	StateInfo DefaultStart(StateInfo _Info);
	StateInfo DefaultUpdate(StateInfo _Info);


	// GameEngineActor��(��) ���� ��ӵ�
	virtual void UpdateBefore() override;

	virtual void UpdateAfter() override;

private:
	float fadeInSpeed_;
	float fadeOutSpeed_;

public:
	void SetFadeInSpeed(float _fadeSpeed);
	void SetFadeOutSpeed(float _fadeSpeed);
};

