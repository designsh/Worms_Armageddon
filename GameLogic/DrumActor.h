#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class DrumActor : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;
	GameEngineCollision* BodyCollision_; // 몸통
	GameEngineCollision* groundCollision_; // 바닥

	const float PetroleumSpeed;

	float Phase_; // 드럼통이 가열된 정도, Max = 3.f
	float deltaTime_;
	float WindSpeed_;
	float degree_;
	GameEngineMath::Random random_;

	// 직접적인 직격, 혹은 화염에 일정시간 노출되었을 경우
	// Phase_ 수치에 따라서 드럼통의 에니메이션(가열된 정도)이 변경되고,
	// 일정 이상이 되면 폭발

public:
	DrumActor(); // default constructer 디폴트 생성자
	~DrumActor(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	DrumActor(const DrumActor& _other) = delete; // default Copy constructer 디폴트 복사생성자
	DrumActor(DrumActor&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	DrumActor& operator=(const DrumActor& _other) = delete; // default Copy operator 디폴트 대입 연산자
	DrumActor& operator=(const DrumActor&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	void initCollision();

public:
	void DrumExplode();
};

