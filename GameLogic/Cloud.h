#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class WindController;
class Cloud : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	WindController* parent_;
	float4 spawnPos_;
	GameEngineMath::Random randomGenerator_;
	float cloudSpeed_;

public:
	Cloud(); // default constructer ����Ʈ ������
	~Cloud(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Cloud(const Cloud& _other) = delete; // default Copy constructer ����Ʈ ���������
	Cloud(Cloud&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Cloud& operator=(const Cloud& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Cloud& operator=(const Cloud&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SetParent(WindController* _parent)
	{
		parent_ = _parent;
	}

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

