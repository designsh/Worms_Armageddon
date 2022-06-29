#pragma once
#include "WindController.h"
#include <GameEngineMath.h>
// 분류 : 
// 용도 : 
// 설명 : 

class BackgroundScatter : public WindController
{

private:	// member Var
	GameEngineRenderer* mainRender_;

private:
	WindController* parent_;
	float4 spawnPos_;
	GameEngineMath::Random randomGenerator_;

public:
	void SetFallSpeed(float _fallSpeedFrom, float _fallSpeedTo)
	{
		fallSpeed_ = randomGenerator_.RandomFloat(_fallSpeedFrom, _fallSpeedTo);
	}

public:
	BackgroundScatter(); // default constructer 디폴트 생성자
	~BackgroundScatter(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	BackgroundScatter(const BackgroundScatter& _other) = delete; // default Copy constructer 디폴트 복사생성자
	BackgroundScatter(BackgroundScatter&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	BackgroundScatter& operator=(const BackgroundScatter& _other) = delete; // default Copy operator 디폴트 대입 연산자
	BackgroundScatter& operator=(const BackgroundScatter&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자


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

