#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class Midground : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;

public:
	Midground(); // default constructer ����Ʈ ������
	~Midground(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Midground(const Midground& _other) = delete; // default Copy constructer ����Ʈ ���������
	Midground(Midground&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Midground& operator=(const Midground& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Midground& operator=(const Midground&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

