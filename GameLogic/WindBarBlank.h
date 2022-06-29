#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class WindBarBlank : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;

public:
	WindBarBlank(); // default constructer ����Ʈ ������
	~WindBarBlank(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WindBarBlank(const WindBarBlank& _other) = delete; // default Copy constructer ����Ʈ ���������
	WindBarBlank(WindBarBlank&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WindBarBlank& operator=(const WindBarBlank& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WindBarBlank& operator=(const WindBarBlank&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

