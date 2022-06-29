#pragma once
#include <GameEngineActor.h>
#include <GameEngineMath.h>
// 분류 : 
// 용도 : 
// 설명 : 

enum class WindDir
{
	TOLEFT,
	TORIGHT,
	NONE
};

class WindController : public GameEngineActor
{
public:	// member Var
	float windSpeed_;
	float fallSpeed_;
	WindDir windDir_;
	
private:
	GameEngineMath::Random randomGenerator_;
	
	bool isDebugOn_;

public:
	WindController(); // default constructer 디폴트 생성자
	~WindController(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WindController(const WindController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WindController(WindController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WindController& operator=(const WindController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WindController& operator=(const WindController&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SetWind(WindDir _windDir,float _windSpeed); // 바람의 방향과 속도를 일괄적으로 변경하는 함수(주의 : 양수만 넣을 것)
	// 음수를 넣으면 우에서 좌로, 양수를 넣으면 좌에서 우로 바람의 방향이 정해집니다.
	// 인자의 오차범위 +- 200.0f 의 랜덤 풍속이 더해집니다.

public:
	std::string GetCurrentWindDir()
	{
		switch (windDir_)
		{
		case WindDir::TOLEFT:
			return "To Left ";
			break;
		case WindDir::TORIGHT:
			return "To Right ";
			break;
		case WindDir::NONE:
			return "WindLess ";
			break;
		default:
			break;
		}
		return "";
	}

	float GetCurrentWindSpeed()
	{
		return windSpeed_;
	}

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

