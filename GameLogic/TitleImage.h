#pragma once
#include <GameEngineActor.h>
#include <GameEngineTimeEventer.h>
#include <GameEngineSoundPlayer.h>
// �з� : 
// �뵵 : 
// ���� : 
class TitleImage : public GameEngineActor
{
private:
	float alpha_;
	unsigned char castalpha_;
	bool fadestop_;
	bool introstop_;
	bool titlepenetration_;
	bool armageddonEnd_;
	bool fadewhilteEnd_;
	bool nextlevel_;
	bool levelChangeStart_;

private:
	int textonIndex_;
	float textontime_;

private:
	GameEngineSoundPlayer mainsound_;
	GameEngineSoundPlayer effectsound1_;
	GameEngineSoundPlayer effectsound2_;

private:	// member Var
	GameEngineRenderer* fadeBlackSpriteRender_;
	GameEngineRenderer* fadeWhiteSpriteRender_;
	GameEngineRenderer* intrologo1SpriteRender_;
	GameEngineRenderer* intrologo2SpriteRender_;
	GameEngineRenderer* titlelogoSpriteRender_;
	GameEngineRenderer* titlelogoActorRender_;
	GameEngineRenderer* mainSpriteRender_;

private: // �Ƹ��ٵ� �̹��� ����Ʈ
	std::vector<GameEngineRenderer*> armageddonlist_;

private: // TimeEventer 
	GameEngineTimeEventer<TitleImage> introTimer_;

public:
	TitleImage();
	~TitleImage();

protected:		// delete constructer
	TitleImage(const TitleImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleImage(TitleImage&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TitleImage& operator=(const TitleImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleImage& operator=(const TitleImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void IntroLogo1Start();
	void IntroLogo1Stay();
	bool IntroLogo1End();

public:
	void IntroLogo2Start();
	void IntroLogo2Stay();
	bool IntroLogo2End();

public:
	void TitleStart();
	void TitleStay();
	bool TitleEnd();

public:
	bool WhiteFadeStart();

public:
	void LevelChange();
};

