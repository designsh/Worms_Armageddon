#pragma once
#include <GameEngineActor.h>
#include <GameEngineSoundPlayer.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class MenuSelImage : public GameEngineActor
{
private:
	bool menusel_;
	float alpha_;
	unsigned char castalpha_;

private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollider_;
	GameEngineCollision* curcollider_;

private:
	GameEngineRenderer* faderenderer_;
	GameEngineSoundPlayer colmousesound_;

public:
	MenuSelImage(); // default constructer ����Ʈ ������
	~MenuSelImage(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MenuSelImage(const MenuSelImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	MenuSelImage(MenuSelImage&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MenuSelImage& operator=(const MenuSelImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MenuSelImage& operator=(const MenuSelImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void ChangeLevel();
};

