#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
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
	Cloud(); // default constructer 디폴트 생성자
	~Cloud(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Cloud(const Cloud& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Cloud(Cloud&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Cloud& operator=(const Cloud& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Cloud& operator=(const Cloud&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

