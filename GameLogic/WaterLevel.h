#pragma once
#include <GameEngineActor.h>
	// �з� : 
	// �뵵 : 
	// ���� : 
class WaterLevel : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;

private:
	bool roundtimechk_; // �κ�ȭ���� ����Ÿ��üũ Flag
	float waterincreasetime_;
	float waterincreaserange_;

public:
	WaterLevel(); // default constructer ����Ʈ ������
	~WaterLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WaterLevel(const WaterLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	WaterLevel(WaterLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WaterLevel& operator=(const WaterLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WaterLevel& operator=(const WaterLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	std::list<GameEngineActor*> Waterlist;

public:
	void WaterLevelUp(float deltaTime); // ���� ���
	void WaterLevelDown(float deltaTime); // ���� �ϰ�

public:
	void TernChangeWaterLevelUp();
	void SetWaterIncreaseRange(float _Range = 800.f);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	const float GetWaterLevel()
	{
		return pos_.y;
	}

	void SetwaterLevel(float _waterLevel)
	{
		pos_.y = _waterLevel;
	}
};