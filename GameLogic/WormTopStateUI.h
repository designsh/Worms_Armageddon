#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class Worm;
class UIController;
class TopHPText;
class GameEngineRenderer;
class WormTopStateUI : public GameEngineActor
{
private:	// member Var
	Worm* ParentWorm_;
	UIController* ParentUI_;

private:
	bool WormLinked_;
	int WormIndex_;
	int PlayerColorIndex_;

private:
	float Deltatime_;

private:
	GameEngineRenderer* NameRenderer_;
	GameEngineRenderer* ArrowRenderer_;
	GameEngineRenderer* HPBoxRenderer_;

private:
	TopHPText* HPText_;
	bool isHPTextNeedChange_;

	void UpdateTextAnimation();

public:
	WormTopStateUI(); // default constructer ����Ʈ ������
	~WormTopStateUI(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WormTopStateUI(const WormTopStateUI& _other) = delete; // default Copy constructer ����Ʈ ���������
	WormTopStateUI(WormTopStateUI&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WormTopStateUI& operator=(const WormTopStateUI& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WormTopStateUI& operator=(const WormTopStateUI&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	Worm* GetParentWorm() const;
	int GetWormIndex() const;
	int GetPlayerColorIndex() const;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void SetParentWorm(Worm* _Parent);
	void SetParentUIController(UIController* _ParentUI);

public:
	void GameStartInit(int _WormIndex);

public:
	void SettingRenderer();
	void SetPlayerName();
	void SetPlayerArrow();
	void SetHPBox();
	void CreateHPText();

public:
	void SettingRendererPos();
	void SetPlayerNamePos();

public:
	TopHPText* GetHPText()
	{
		return HPText_;
	}

	void SetTextChangeRequest()
	{
		isHPTextNeedChange_ = true;
	}

public:
	void CurWormHPTextDeath();
};

