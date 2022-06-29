#include "TitleImage.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include <GameEngineTime.h>

TitleImage::TitleImage() :
	alpha_(0.0f),
	castalpha_(0),
	fadestop_(false),
	introstop_(false),
	titlepenetration_(false),
	armageddonEnd_(false),
	fadewhilteEnd_(false),
	nextlevel_(false),
	levelChangeStart_(false),
	textonIndex_(-1),
	textontime_(0.5f),
	mainsound_("Worms_TitleScreen.mp3"),
	effectsound1_("WormLanding.wav"),
	effectsound2_("Worms_TitleScreen_Heartbeat.wav"),
	fadeBlackSpriteRender_(nullptr),
	fadeWhiteSpriteRender_(nullptr),
	intrologo1SpriteRender_(nullptr),
	intrologo2SpriteRender_(nullptr),
	titlelogoSpriteRender_(nullptr),
	titlelogoActorRender_(nullptr),
	mainSpriteRender_(nullptr),
	introTimer_{}
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround));
}

TitleImage::~TitleImage() // default destructer ����Ʈ �Ҹ���
{

}

TitleImage::TitleImage(TitleImage&& _other) noexcept :
	alpha_(_other.alpha_),
	castalpha_(_other.castalpha_),
	fadestop_(_other.fadestop_),
	introstop_(_other.introstop_),
	titlepenetration_(_other.titlepenetration_),
	fadewhilteEnd_(_other.fadewhilteEnd_),
	nextlevel_(_other.nextlevel_),
	levelChangeStart_(_other.levelChangeStart_),
	armageddonEnd_(_other.armageddonEnd_),
	textonIndex_(_other.textonIndex_),
	textontime_(_other.textontime_),
	mainsound_("Worms_TitleScreen.mp3"),
	effectsound1_("WormLanding.wav"),
	effectsound2_("Worms_TitleScreen_Heartbeat.wav"),
	fadeBlackSpriteRender_(_other.fadeBlackSpriteRender_),
	fadeWhiteSpriteRender_(_other.fadeWhiteSpriteRender_),
	intrologo1SpriteRender_(_other.intrologo1SpriteRender_),
	intrologo2SpriteRender_(_other.intrologo2SpriteRender_),
	titlelogoSpriteRender_(_other.titlelogoSpriteRender_),
	titlelogoActorRender_(_other.titlelogoActorRender_),
	mainSpriteRender_(_other.mainSpriteRender_),
	introTimer_{}
{
}

void TitleImage::UpdateBefore()
{

}

void TitleImage::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 ImageHarf = float4::ZERO;

	// Fade In/Out ������ ����
	fadeBlackSpriteRender_ = CreateRenderer("Fade_Black");
	ImageHarf = fadeBlackSpriteRender_->GetImageSize().halffloat4();
	fadeBlackSpriteRender_->SetPivotPos(ImageHarf);
	fadeBlackSpriteRender_->Off();

	fadeWhiteSpriteRender_ = CreateRenderer("Fade_White");
	ImageHarf = fadeWhiteSpriteRender_->GetImageSize().halffloat4();
	fadeWhiteSpriteRender_->SetPivotPos(ImageHarf);
	fadeWhiteSpriteRender_->Off();

	// ��Ʈ�� �ΰ�1
	intrologo1SpriteRender_ = CreateRenderer("Intro_Logo1");
	ImageHarf = intrologo1SpriteRender_->GetImageSize().halffloat4();
	intrologo1SpriteRender_->SetPivotPos(float4(ImageHarf.x, ImageHarf.y + 100.f));
	intrologo1SpriteRender_->SetRenderSize(float4(1280.f, 512.f));
	intrologo1SpriteRender_->SetCameraEffectOff();
	intrologo1SpriteRender_->Off();

	// ��Ʈ�� �ΰ�2
	intrologo2SpriteRender_ = CreateRenderer("Intro_Logo2");
	ImageHarf = intrologo2SpriteRender_->GetImageSize().halffloat4();
	intrologo2SpriteRender_->SetPivotPos(float4(ImageHarf.x, ImageHarf.y + 100.f));
	intrologo2SpriteRender_->SetRenderSize(float4(1280.f, 512.f));
	intrologo2SpriteRender_->SetCameraEffectOff();
	intrologo2SpriteRender_->Off();

	// Ÿ���̺��� ���(��Ʈ�� �ΰ� Fade In/Out �뵵 ���)
	introTimer_.CreateTimeEvent(3.0f, this, nullptr, &TitleImage::IntroLogo1Start, &TitleImage::IntroLogo1Stay, &TitleImage::IntroLogo1End);
	introTimer_.CreateTimeEvent(3.0f, this, nullptr, &TitleImage::IntroLogo2Start, &TitleImage::IntroLogo2Stay, &TitleImage::IntroLogo2End);
	introTimer_.CreateTimeEvent(3.0f, this, nullptr, &TitleImage::TitleStart, &TitleImage::TitleStay, &TitleImage::TitleEnd);

	// Ÿ��Ʋ �ΰ�
	titlelogoSpriteRender_ = CreateRenderer("Title_Logo");
	ImageHarf = titlelogoSpriteRender_->GetImageSize().halffloat4();
	titlelogoSpriteRender_->SetPivotPos(float4(ImageHarf.x + 360.f, ImageHarf.y + 20.f));
	titlelogoSpriteRender_->SetRenderSize(float4(640.f, 200.f));
	titlelogoSpriteRender_->SetCameraEffectOff();
	titlelogoSpriteRender_->Off();

	// Ÿ��Ʋ�ΰ��� ���;ִϸ��̼�
	titlelogoActorRender_ = CreateRenderer("TitleLogo_Actor");
	ImageHarf = titlelogoActorRender_->GetImageSize().halffloat4();
	titlelogoActorRender_->SetPivotPos(float4(ImageHarf.x + 230.f, ImageHarf.y + 50.f));
	titlelogoActorRender_->CreateAnimation("TitleLogo_Actor", "TitleLogo_Actor", 0, 4, true, 0.18f);
	titlelogoActorRender_->ChangeAnimation("TitleLogo_Actor");
	titlelogoActorRender_->Off();

	// Ÿ��Ʋ�ΰ� �Ƹ��ٵ� �ؽ�Ʈ
	armageddonlist_.clear();
	for (size_t i = 0; i < 10; ++i)
	{
		std::string Name = "Armageddon_";
		Name += std::to_string(i + 1);
		GameEngineRenderer* NewRender = CreateRenderer(Name);

		// ��ġ ���
		ImageHarf = titlelogoSpriteRender_->GetImageSize().halffloat4();
		NewRender->SetPivotPos(float4(ImageHarf.x + 220.f + (i * 60.f), ImageHarf.y + 153.f));
		NewRender->SetRenderSize(float4(60.f, 64.f));

		NewRender->SetCameraEffectOff();
		NewRender->Off();

		armageddonlist_.push_back(NewRender);
	}

	// ��׶���
	mainSpriteRender_ = CreateRenderer("Title_Backdrop");
	ImageHarf = mainSpriteRender_->GetImageSize().halffloat4();
	mainSpriteRender_->SetPivotPos(ImageHarf);
	mainSpriteRender_->SetRenderSize(WindowSize);
	mainSpriteRender_->SetCameraEffectOff();
	mainSpriteRender_->Off();

	// Ű����
	if (false == GameEngineInput::GetInst().IsKey("Title_Skip"))
	{
		GameEngineInput::GetInst().CreateKey("Title_Skip", VK_SPACE);
	}

	if (false == GameEngineInput::GetInst().IsKey("All_Skip"))
	{
		GameEngineInput::GetInst().CreateKey("All_Skip", 'a');
	}

	if (false == GameEngineInput::GetInst().IsKey("Lobby_Skip"))
	{
		GameEngineInput::GetInst().CreateKey("Lobby_Skip", 's');
	}

	ShowCursor(true);
}

void TitleImage::Update()
{
	// �ý�ŵ �� �÷��̾����� �ٷ��̵�
	if (true == GameEngineInput::GetInst().IsDown("All_Skip"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("PlayLevel", true);
	}

	// Ÿ��Ʋ ������ �κ�ȭ������ �ٷ��̵�
	if (true == GameEngineInput::GetInst().IsDown("Lobby_Skip"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel", true);
	}

	// Ÿ���̺��� ������Ʈ ȣ��
	introTimer_.Update();

	// ��Ʈ�� ���� �� Ÿ��Ʋȭ�� ���Խ�
	if (true == introstop_)
	{
		titlelogoSpriteRender_->On();
		titlelogoActorRender_->On();

		introstop_ = false;
	}

	// Ÿ��Ʋ���� ��ŵ ���
	if (true == GameEngineInput::GetInst().IsDown("Title_Skip"))
	{
		// Ÿ��Ʋȭ�� ù���Կ��� -> Ÿ��Ʋ �Ϸ�
		if (true == titlelogoSpriteRender_->IsOn() && false == titlepenetration_ && false == armageddonEnd_)
		{
			// ��Ʈ�� ������ Ÿ��Ʋ �ΰ� �����̸�
			fadeWhiteSpriteRender_->On();

			alpha_ = 0.0f;
			castalpha_ = 0;
			fadeWhiteSpriteRender_->SetAlpha(castalpha_);

			titlepenetration_ = true;
		}

		// ���� ���� ����
		if (true == nextlevel_)
		{
			// Fade In/Out Alpha Reset
			fadeBlackSpriteRender_->On();

			alpha_ = 0.0f;
			castalpha_ = 0;
			fadeBlackSpriteRender_->SetAlpha(castalpha_);

			levelChangeStart_ = true;
			nextlevel_ = false;
		}
	}

	if (true == levelChangeStart_)
	{
		// Fade Black End �� ������ȯ
		LevelChange();
	}

	if (true == titlepenetration_ && true == fadeWhiteSpriteRender_->IsOn())
	{
		WhiteFadeStart();
	}

	if (true == fadewhilteEnd_)
	{
		// �Ƹ��ٵ� �ؽ�Ʈ ������ ����
		textontime_ -= GameEngineTime::GetInst().GetDeltaTime();
		if (0.0f >= textontime_)
		{
			++textonIndex_;
			armageddonlist_[textonIndex_]->On();

			textontime_ = 0.5f;

			// �Ƹ��ٵ� �ؽ�Ʈ ��� ���� ����
			effectsound1_.Play();
		}

		// �Ƹ��ٵ� �ؽ�Ʈ ��� ������ �Ϸ�
		size_t Index = armageddonlist_.size();
		if (nullptr != armageddonlist_[Index - 1])
		{
			if (true == armageddonlist_[Index - 1]->IsOn())
			{
				// Flag ó��
				armageddonEnd_ = true;
				fadewhilteEnd_ = false;
				nextlevel_ = true;

				// �Ƹ��ٵ� �ؽ�Ʈ ��� ����Ʈ ���� ����
				effectsound1_.Stop();
			}
		}
	}

	if (true == armageddonEnd_)
	{
		mainSpriteRender_->On();
		armageddonEnd_ = false;
	}
}

void TitleImage::UpdateAfter()
{
}

void TitleImage::Render()
{
	// ��Ʈ�ηΰ�1
	if (true == intrologo1SpriteRender_->IsOn())
	{
		intrologo1SpriteRender_->Render();
	}

	// ��Ʈ�ηΰ�2
	if (true == intrologo2SpriteRender_->IsOn())
	{
		intrologo2SpriteRender_->Render();
	}

	// ��׶���
	if (true == mainSpriteRender_->IsOn())
	{
		mainSpriteRender_->Render();
	}

	// Ÿ��Ʋ �ΰ� �Ƹ��Ե�
	size_t Size = armageddonlist_.size();
	for (size_t i = 0; i < Size; ++i)
	{
		if (true == armageddonlist_[i]->IsOn())
		{
			armageddonlist_[i]->Render();
		}
	}

	// Ÿ��Ʋ�ΰ�
	if (true == titlelogoSpriteRender_->IsOn())
	{
		titlelogoSpriteRender_->Render();
	}

	// Ÿ��Ʋ����
	if (true == titlelogoActorRender_->IsOn())
	{
		titlelogoActorRender_->AnimationUpdate();
	}

	// Fade In/Out
	if (true == fadeBlackSpriteRender_->IsOn())
	{
		fadeBlackSpriteRender_->Render();
	}

	if (true == fadeWhiteSpriteRender_->IsOn())
	{
		fadeWhiteSpriteRender_->Render();
	}
}

void TitleImage::IntroLogo1Start()
{
	intrologo1SpriteRender_->On();
	fadeBlackSpriteRender_->On();

	alpha_ = 2.55f;
	castalpha_ = 255;
	fadestop_ = false;

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

void TitleImage::IntroLogo1Stay()
{
	alpha_ -= GameEngineTime::GetInst().GetDeltaTime();

	if (0.0f >= alpha_)
	{
		alpha_ = 0.0f;
		castalpha_ = 0;
		fadestop_ = true;
		intrologo1SpriteRender_->Off();
		fadeBlackSpriteRender_->Off();
	}
	else
	{
		castalpha_ = static_cast<unsigned char>(alpha_ * 100.f);
	}

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

bool TitleImage::IntroLogo1End()
{
	return fadestop_;
}

void TitleImage::IntroLogo2Start()
{
	intrologo2SpriteRender_->On();
	fadeBlackSpriteRender_->On();

	alpha_ = 2.55f;
	castalpha_ = 255;
	fadestop_ = false;

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

void TitleImage::IntroLogo2Stay()
{
	alpha_ -= GameEngineTime::GetInst().GetDeltaTime();

	if (0.0f >= alpha_)
	{
		alpha_ = 0.0f;
		castalpha_ = 0;
		fadestop_ = true;
		fadeBlackSpriteRender_->Off();
	}
	else
	{
		castalpha_ = static_cast<unsigned char>(alpha_ * 100.f);
	}

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

bool TitleImage::IntroLogo2End()
{
	return fadestop_;
}

void TitleImage::TitleStart()
{
	fadeBlackSpriteRender_->On();

	alpha_ = 2.55f;
	castalpha_ = 255;
	fadestop_ = false;

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

void TitleImage::TitleStay()
{
	alpha_ -= GameEngineTime::GetInst().GetDeltaTime();

	if (0.f <= alpha_)
	{
		alpha_ = 0.0f;
		castalpha_ = 0;
		fadestop_ = true;
		introstop_ = true;
		intrologo2SpriteRender_->Off();
		fadeBlackSpriteRender_->Off();

		// ����ڵ� ���� ����
		effectsound2_.Play();
		effectsound2_.SetVolume(1.f);
	}
	else
	{
		castalpha_ = static_cast<unsigned char>(alpha_ * 100.f);
	}

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

bool TitleImage::TitleEnd()
{
	return introstop_;
}

bool TitleImage::WhiteFadeStart()
{
	alpha_ += GameEngineTime::GetInst().GetDeltaTime();

	if (2.55f <= alpha_)
	{
		alpha_ = 2.55f;
		castalpha_ = 255;
		fadewhilteEnd_ = true;
		fadeWhiteSpriteRender_->Off();
		mainSpriteRender_->On();

		// �ִϸ��̼� ��������
		titlelogoActorRender_->CurAnimationReset();

		// ������� ����
		mainsound_.Play();
		mainsound_.SetVolume(0.2f);

		// ����Ҹ� ��� ����
		effectsound2_.Stop();
	}
	else
	{
		castalpha_ = static_cast<unsigned char>(alpha_ * 100.f);
	}

	fadeWhiteSpriteRender_->SetAlpha(castalpha_);

	return fadewhilteEnd_;
}

void TitleImage::LevelChange()
{
	alpha_ += GameEngineTime::GetInst().GetDeltaTime();

	if (2.55f <= alpha_)
	{
		alpha_ = 0.0f;
		castalpha_ = 0;
		levelChangeStart_ = false;
		fadeBlackSpriteRender_->Off();

		// ���� ��ȯ
		GameEngineLevelManager::GetInst().ChangeLevel("MenuSelectLevel", true);

		// ������� off
		mainsound_.Stop();
	}
	else
	{
		castalpha_ = static_cast<unsigned char>(alpha_ * 100.f);
	}

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}
