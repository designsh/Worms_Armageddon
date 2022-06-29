#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class Worm;
class UIController;
class BottomFlag : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;

private:
	Worm* parentWorm_;
	UIController* parentUI_;

public:
	BottomFlag(); // default constructer ����Ʈ ������
	~BottomFlag(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	BottomFlag(const BottomFlag& _other) = delete; // default Copy constructer ����Ʈ ���������
	BottomFlag(BottomFlag&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	BottomFlag& operator=(const BottomFlag& _other) = delete; // default Copy operator ����Ʈ ���� ������
	BottomFlag& operator=(const BottomFlag&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void NationInit(int _wormNumber);
	void StartPosInit(int _wormNumber);
};

