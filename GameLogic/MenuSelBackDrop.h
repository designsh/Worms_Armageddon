#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class MenuSelBackDrop : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineRenderer* titlerenderer_;

public:
	MenuSelBackDrop(); // default constructer ����Ʈ ������
	~MenuSelBackDrop(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MenuSelBackDrop(const MenuSelBackDrop& _other) = delete; // default Copy constructer ����Ʈ ���������
	MenuSelBackDrop(MenuSelBackDrop&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MenuSelBackDrop& operator=(const MenuSelBackDrop& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MenuSelBackDrop& operator=(const MenuSelBackDrop&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

