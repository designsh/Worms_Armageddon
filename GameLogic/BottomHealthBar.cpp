#include "BottomHealthBar.h"
#include <GameEngineRenderer.h>
BottomHealthBar::BottomHealthBar() // default constructer ����Ʈ ������
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder((int)RenderOrder::UI);
}

BottomHealthBar::~BottomHealthBar() // default destructer ����Ʈ �Ҹ���
{

}

BottomHealthBar::BottomHealthBar(BottomHealthBar&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr), parentWorm_(nullptr)
{

}

void BottomHealthBar::Start()
{
	mainRender_ = CreateRenderer("BottomHPbarR");
	mainRender_->SetCameraEffectOff();
}

void BottomHealthBar::UpdateBefore()
{

}

void BottomHealthBar::Update()
{
	// �� ������ ���� ���ǿ��� �ٸ� Bottom UI �� �Բ� �� �Ʒ��� �̵��� ����
}

void BottomHealthBar::UpdateAfter()
{

}

void BottomHealthBar::Render()
{
	mainRender_->Render();
}

void BottomHealthBar::RenderColorInit(int _wormNumber) // ���� ��ȣ�� �޾� ü�¹��� ������ �������ݴϴ�.
{
	switch (_wormNumber)
	{
	case 0:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	case 1:
		mainRender_ = CreateRenderer("BottomHPbarB");
		break;
	case 2:
		mainRender_ = CreateRenderer("BottomHPbarG");
		break;
	case 3:
		mainRender_ = CreateRenderer("BottomHPbarY");
		break;
	case 4:
		mainRender_ = CreateRenderer("BottomHPbarP");
		break;
	case 5:
		mainRender_ = CreateRenderer("BottomHPbarS");
		break;
	case 6:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	case 7:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	default:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	}
}

void BottomHealthBar::StartPosInit(int _wormNumber) // ���� ��ȣ�� �޾� ü�¹��� ������ �������ݴϴ�.
{
	switch (_wormNumber)
	{
	case 0:
		SetPos({ 672, 610 });
		break;
	case 1:
		SetPos({ 672, 630 });
		break;
	case 2:
		SetPos({ 672, 650 });
		break;
	case 3:
		SetPos({ 672, 670 });
		break;
	case 4:
		SetPos({ 672, 690 });
		break;
	case 5:
		SetPos({ 672, 710 });
		break;
	case 6:
		SetPos({ 672, 730 });
		break;
	case 7:
		SetPos({ 672, 750 });
		break;
	default:
		SetPos({ 0, 0 });
		break;
	}
	mainRender_->SetCameraEffectOff();
}

void BottomHealthBar::DamageInit(int _damage)
{

}