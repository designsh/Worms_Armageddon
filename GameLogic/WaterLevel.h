#pragma once
#include <GameEngineActor.h>
	// 분류 : 
	// 용도 : 
	// 설명 : 
class WaterLevel : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;

private:
	bool roundtimechk_; // 로비화면의 라운드타임체크 Flag
	float waterincreasetime_;
	float waterincreaserange_;

public:
	WaterLevel(); // default constructer 디폴트 생성자
	~WaterLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WaterLevel(const WaterLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WaterLevel(WaterLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WaterLevel& operator=(const WaterLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WaterLevel& operator=(const WaterLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	std::list<GameEngineActor*> Waterlist;

public:
	void WaterLevelUp(float deltaTime); // 수면 상승
	void WaterLevelDown(float deltaTime); // 수면 하강

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