#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class WindController;
class WindBarHider : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	WindController* parentController_;

public:
	WindBarHider(); // default constructer ����Ʈ ������
	~WindBarHider(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WindBarHider(const WindBarHider& _other) = delete; // default Copy constructer ����Ʈ ���������
	WindBarHider(WindBarHider&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WindBarHider& operator=(const WindBarHider& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WindBarHider& operator=(const WindBarHider&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����


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

