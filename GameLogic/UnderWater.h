#pragma once
#include <GameEngineActor.h>
	// �з� : 
	// �뵵 : 
	// ���� : 
class UnderWater : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;
public:
	UnderWater(); // default constructer ����Ʈ ������
	~UnderWater(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	UnderWater(const UnderWater& _other) = delete; // default Copy constructer ����Ʈ ���������
	UnderWater(UnderWater&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	UnderWater& operator=(const UnderWater& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UnderWater& operator=(const UnderWater&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};


