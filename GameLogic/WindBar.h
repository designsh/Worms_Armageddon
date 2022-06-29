#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 

class WindController;
class WindBar : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	WindController* parentController_;

private:
	float originalSizeX_;

public:
	WindBar(); // default constructer 디폴트 생성자
	~WindBar(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WindBar(const WindBar& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WindBar(WindBar&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WindBar& operator=(const WindBar& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WindBar& operator=(const WindBar&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SetParentController(WindController* _parent)
	{
		parentController_ = _parent;
		return;
	}

	void WindBarUpdate();

public:	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

};

