#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class BackGroundGradation : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;

public:
	BackGroundGradation(); // default constructer ����Ʈ ������
	~BackGroundGradation(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	BackGroundGradation(const BackGroundGradation& _other) = delete; // default Copy constructer ����Ʈ ���������
	BackGroundGradation(BackGroundGradation&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	BackGroundGradation& operator=(const BackGroundGradation& _other) = delete; // default Copy operator ����Ʈ ���� ������
	BackGroundGradation& operator=(const BackGroundGradation&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

