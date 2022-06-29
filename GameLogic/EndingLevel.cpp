#include "EndingLevel.h"

#include "EndingImage.h"
#include "EndingText.h"
#include "EndingFade.h"

#include <GameEngineWindow.h>

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Loading()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 HarfWindow = WindowSize.halffloat4();

	// 엔딩뒷배경
	EndingImage* EndingBackDrop = CreateActor<EndingImage>();

	// 크래딧
	EndingText* Credit = CreateActor<EndingText>();
	Credit->EndingTextInit("CREDIT", float4(HarfWindow.x - 70.f, 740.f));

	// 팀이름
	EndingText* TeamName = CreateActor<EndingText>();
	TeamName->EndingTextInit("TEAMNAME   WTEAM", float4(HarfWindow.x - 270.f, 810.f));

	// 제작자
	EndingText* Developer = CreateActor<EndingText>();
	Developer->EndingTextInit("DEVELOPER", float4(HarfWindow.x - 300.f, 880.f));

	// 박종원
	EndingText* PARKJONGWON = CreateActor<EndingText>();
	PARKJONGWON->EndingTextInit("PARK JONGWON", float4(HarfWindow.x + 70.f, 880.f));

	// 신종하
	EndingText* SHINJONGHA = CreateActor<EndingText>();
	SHINJONGHA->EndingTextInit("SHIN JONGHA", float4(HarfWindow.x + 70.f, 920.f));

	// 안지용
	EndingText* AHNJIYONG = CreateActor<EndingText>();
	AHNJIYONG->EndingTextInit("AHN  JIYONG", float4(HarfWindow.x + 70.f, 960.f));

	// 이현
	EndingText* LEEHYUN = CreateActor<EndingText>();
	LEEHYUN->EndingTextInit("LEE  HYUN", float4(HarfWindow.x + 70.f, 1000.f));

	// 조규현
	EndingText* JOGYUHYEON = CreateActor<EndingText>();
	JOGYUHYEON->EndingTextInit("JO   GYUHYEON", float4(HarfWindow.x + 70.f, 1040.f));

	// 감사합니다
	EndingText* ThankYou = CreateActor<EndingText>();
	ThankYou->EndingTextInit("THANK YOU", float4(HarfWindow.x - 150.f, 1140.f));

	// Fade In/Out 
	EndingFade* EndingFadeImage = CreateActor<EndingFade>();
	EndingFadeImage->PushCreditText(Credit);
	EndingFadeImage->PushCreditText(TeamName);
	EndingFadeImage->PushCreditText(Developer);
	EndingFadeImage->PushCreditText(PARKJONGWON);
	EndingFadeImage->PushCreditText(SHINJONGHA);
	EndingFadeImage->PushCreditText(AHNJIYONG);
	EndingFadeImage->PushCreditText(LEEHYUN);
	EndingFadeImage->PushCreditText(JOGYUHYEON);
	EndingFadeImage->PushCreditText(ThankYou);
}

void EndingLevel::LevelUpdate()
{
}

