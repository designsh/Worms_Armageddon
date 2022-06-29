#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class Petroleum : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;
	GameEngineRenderer* ChildSpriteRender_[3];

	GameEngineCollision* groundCollision_; // �ٴ�
	GameEngineCollision* BodyCollision_; // ����

	GameEngineFSM<Petroleum> state_;
	GameEngineFSM<Petroleum> PhysicalState_;
	std::string nextState_;

	float4 Dir_;
	float4 prevPos_;

	float degree_;
	//float deltaTime_;

	float WindAcc_;
	float WindSpeed_;
	float GravityAcc;
	float GravitySpeed;

	float deltaTime_;

	bool isLive_;

	bool Burn_;
	bool Isground_;
	bool CountSecond_[10]; // ������ �ʸ� ���� ���� �迭

	float Cur_LifeTime_;
	float Max_LifeTime_;

	// �������� ����, Ȥ�� ȭ���� �����ð� ����Ǿ��� ���
	// Phase_ ��ġ�� ���� �巳���� ���ϸ��̼�(������ ����)�� ����ǰ�,
	// ���� �̻��� �Ǹ� ����

public:
	Petroleum(); // default constructer ����Ʈ ������
	~Petroleum(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Petroleum(const Petroleum& _other) = delete; // default Copy constructer ����Ʈ ���������
	Petroleum(Petroleum&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Petroleum& operator=(const Petroleum& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Petroleum& operator=(const Petroleum&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

	void PetroleumDeath();


private:
	void initCollision();
	//void PetroleumUpdate(float deltaTime_);
	//void PetroleumMoveUpdate(float deltaTime_);
	//void PetroleumGroundUpdate(float deltaTime_);

	StateInfo AirStart(StateInfo _state);
	StateInfo AirUpdate(StateInfo _state);

	StateInfo GroundStart(StateInfo _state);
	StateInfo GroundUpdate(StateInfo _state);



	StateInfo LiquidPhase0Start(StateInfo _state);
	StateInfo LiquidPhase0Update(StateInfo _state);

	StateInfo LiquidPhase1Start(StateInfo _state);
	StateInfo LiquidPhase1Update(StateInfo _state);

	StateInfo LiquidPhase2Start(StateInfo _state);
	StateInfo LiquidPhase2Update(StateInfo _state);

	StateInfo LiquidPhase3Start(StateInfo _state);
	StateInfo LiquidPhase3Update(StateInfo _state);

	StateInfo Phase1Start(StateInfo _state);
	StateInfo Phase1Update(StateInfo _state);

	StateInfo Phase2Start(StateInfo _state);
	StateInfo Phase2Update(StateInfo _state);

	StateInfo Phase3Start(StateInfo _state);
	StateInfo Phase3Update(StateInfo _state);

	StateInfo Phase4Start(StateInfo _state);
	StateInfo Phase4Update(StateInfo _state);

	StateInfo Phase5Start(StateInfo _state);
	StateInfo Phase5Update(StateInfo _state);

	void CalFrameIndex();
	void WormCollision();
public:

	bool GetisLive()
	{
		return isLive_;
	}

	void SetDir(float4 _Dir)
	{
		Dir_ = _Dir;
	}

	void SetDir(float _Dirx , float _Diry)
	{
		Dir_.x = _Dirx;
		Dir_.y = _Diry;
		Dir_.z = 0.f;
	}

	void SetWindSpeed(float _WindSpeed)
	{
		WindAcc_ = _WindSpeed / 30.f;
	}
};

