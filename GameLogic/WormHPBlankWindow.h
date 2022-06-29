#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class UIController;
class Worm;
class WormHPBlankWindow : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	Worm* parent_;
	bool isWormLinked_;

public:
	WormHPBlankWindow(); // default constructer ����Ʈ ������
	~WormHPBlankWindow(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WormHPBlankWindow(const WormHPBlankWindow& _other) = delete; // default Copy constructer ����Ʈ ���������
	WormHPBlankWindow(WormHPBlankWindow&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WormHPBlankWindow& operator=(const WormHPBlankWindow& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WormHPBlankWindow& operator=(const WormHPBlankWindow&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

