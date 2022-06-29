#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// 
// ���� : 
class UIController; 
class Worm;
class WormName : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	Worm* parent_;
	bool isWormLinked_;

public:
	WormName(); // default constructer ����Ʈ ������
	~WormName(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WormName(const WormName& _other) = delete; // default Copy constructer ����Ʈ ���������
	WormName(WormName&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WormName& operator=(const WormName& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WormName& operator=(const WormName&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void NameInit(int _wormNumber);
	void StartPosInit(int _wormNumber);
	void SetParentWorm(Worm* _worm)
	{
		parent_ = _worm;
		isWormLinked_ = true;
	}

};