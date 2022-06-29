#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class UIController;
class Worm;
class BottomNameTag : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	
private:
	Worm* parentWorm_;
	UIController* parentUI_;

public:
	BottomNameTag(); // default constructer ����Ʈ ������
	~BottomNameTag(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	BottomNameTag(const BottomNameTag& _other) = delete; // default Copy constructer ����Ʈ ���������
	BottomNameTag(BottomNameTag&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	BottomNameTag& operator=(const BottomNameTag& _other) = delete; // default Copy operator ����Ʈ ���� ������
	BottomNameTag& operator=(const BottomNameTag&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void NameInit(int _wormNumber);
	void StartPosInit(int _wormNumber);
};

