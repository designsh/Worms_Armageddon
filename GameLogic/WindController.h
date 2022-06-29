#pragma once
#include <GameEngineActor.h>
#include <GameEngineMath.h>
// �з� : 
// �뵵 : 
// ���� : 

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
	WindController(); // default constructer ����Ʈ ������
	~WindController(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WindController(const WindController& _other) = delete; // default Copy constructer ����Ʈ ���������
	WindController(WindController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WindController& operator=(const WindController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WindController& operator=(const WindController&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SetWind(WindDir _windDir,float _windSpeed); // �ٶ��� ����� �ӵ��� �ϰ������� �����ϴ� �Լ�(���� : ����� ���� ��)
	// ������ ������ �쿡�� �·�, ����� ������ �¿��� ��� �ٶ��� ������ �������ϴ�.
	// ������ �������� +- 200.0f �� ���� ǳ���� �������ϴ�.

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

