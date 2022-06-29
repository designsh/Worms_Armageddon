#include "BottomFlag.h"
#include <GameEngineRenderer.h>

BottomFlag::BottomFlag() // default constructer ����Ʈ ������
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder((int)RenderOrder::UI);
}

BottomFlag::~BottomFlag() // default destructer ����Ʈ �Ҹ���
{

}

BottomFlag::BottomFlag(BottomFlag&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr), parentWorm_(nullptr)
{

}


void BottomFlag::Start()
{
	mainRender_ = CreateRenderer("BottomFlagRUS");
	mainRender_->SetCameraEffectOff();
}

void BottomFlag::UpdateBefore()
{

}

void BottomFlag::Update()
{
	// �� ������ ���� ���ǿ��� �ٸ� Bottom UI �� �Բ� �� �Ʒ��� �̵��� ����
}

void BottomFlag::UpdateAfter()
{

}

void BottomFlag::Render()
{
	mainRender_->Render();
}


void BottomFlag::NationInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:
		mainRender_ = CreateRenderer("BottomFlagRUS");
		break;
	case 1:
		mainRender_ = CreateRenderer("BottomFlagBRA");
		break;
	case 2:
		mainRender_ = CreateRenderer("BottomFlagKOR");
		break;
	case 3:
		mainRender_ = CreateRenderer("BottomFlagUSA");
		break;
	case 4:
		mainRender_ = CreateRenderer("BottomFlagGER");
		break;
	case 5:
		mainRender_ = CreateRenderer("BottomFlagJPN");
		break;
	case 6:
		mainRender_ = CreateRenderer("BottomFlagRUS");
		break;
	case 7:
		mainRender_ = CreateRenderer("BottomFlagRUS");
		break;
	default:
		mainRender_ = CreateRenderer("BottomFlagRUS");
		break;
	}
}
void BottomFlag::StartPosInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:
		SetPos({ 605, 610 });
		break;
	case 1:
		SetPos({ 605, 630 });
		break;
	case 2:
		SetPos({ 605, 650 });
		break;
	case 3:
		SetPos({ 605, 670 });
		break;
	case 4:
		SetPos({ 605, 690 });
		break;
	case 5:
		SetPos({ 605, 710 });
		break;


	case 6:
		SetPos({ 605, 730 });
		break;
	case 7:
		SetPos({ 605, 750 });
		break;
	default:
		SetPos({ 0, 0 });
		break;
	}
	mainRender_->SetCameraEffectOff();
}