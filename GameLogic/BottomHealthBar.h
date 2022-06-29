#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class Worm;
class UIController;
class BottomHealthBar : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;

private:
	Worm* parentWorm_;
	UIController* parentUI_;

public:
	BottomHealthBar(); // default constructer ����Ʈ ������
	~BottomHealthBar(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	BottomHealthBar(const BottomHealthBar& _other) = delete; // default Copy constructer ����Ʈ ���������
	BottomHealthBar(BottomHealthBar&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	BottomHealthBar& operator=(const BottomHealthBar& _other) = delete; // default Copy operator ����Ʈ ���� ������
	BottomHealthBar& operator=(const BottomHealthBar&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void RenderColorInit(int _wormNumber);
	void StartPosInit(int _wormNumber);
	void DamageInit(int _damage);
};

