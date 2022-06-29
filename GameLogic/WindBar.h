#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 

class WindController;
class WindBar : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	WindController* parentController_;

private:
	float originalSizeX_;

public:
	WindBar(); // default constructer ����Ʈ ������
	~WindBar(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WindBar(const WindBar& _other) = delete; // default Copy constructer ����Ʈ ���������
	WindBar(WindBar&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WindBar& operator=(const WindBar& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WindBar& operator=(const WindBar&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

