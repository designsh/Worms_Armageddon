#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class Worm;
class TimerBlankWindow : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	Worm* parent_;
	bool isWormLinked_;

public:
	TimerBlankWindow(); // default constructer ����Ʈ ������
	~TimerBlankWindow(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	TimerBlankWindow(const TimerBlankWindow& _other) = delete; // default Copy constructer ����Ʈ ���������
	TimerBlankWindow(TimerBlankWindow&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TimerBlankWindow& operator=(const TimerBlankWindow& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TimerBlankWindow& operator=(const TimerBlankWindow&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void RenderColorInit(int _wormNumber);
	void SetParentWorm(Worm* _worm)
	{
		parent_ = _worm;
		isWormLinked_ = true;
	}
};

