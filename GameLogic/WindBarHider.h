#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class WindController;
class WindBarHider : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	WindController* parentController_;

public:
	WindBarHider(); // default constructer 디폴트 생성자
	~WindBarHider(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WindBarHider(const WindBarHider& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WindBarHider(WindBarHider&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WindBarHider& operator=(const WindBarHider& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WindBarHider& operator=(const WindBarHider&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자


public:
	void SetParentController(WindController* _parent)
	{
		parentController_ = _parent;
		return;
	}

	void WindBarUpdate();

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

