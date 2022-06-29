#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class WaterWave : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;
public:
	WaterWave(); // default constructer ����Ʈ ������
	~WaterWave(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WaterWave(const WaterWave& _other) = delete; // default Copy constructer ����Ʈ ���������
	WaterWave(WaterWave&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WaterWave& operator=(const WaterWave& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WaterWave& operator=(const WaterWave&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void SetAnimationCurrentFrame(const int _index);

};

