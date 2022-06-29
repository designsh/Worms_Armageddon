#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
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
	WormTopStateUI(); // default constructer 디폴트 생성자
	~WormTopStateUI(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WormTopStateUI(const WormTopStateUI& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WormTopStateUI(WormTopStateUI&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WormTopStateUI& operator=(const WormTopStateUI& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WormTopStateUI& operator=(const WormTopStateUI&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

