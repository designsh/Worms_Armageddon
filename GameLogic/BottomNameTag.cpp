#include "BottomNameTag.h"
#include <GameEngineRenderer.h>
BottomNameTag::BottomNameTag() // default constructer ����Ʈ ������
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder((int)RenderOrder::UI);
}

BottomNameTag::~BottomNameTag() // default destructer ����Ʈ �Ҹ���
{

}

BottomNameTag::BottomNameTag(BottomNameTag&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr), parentWorm_(nullptr)
{

}

void BottomNameTag::Start()
{
	mainRender_ = CreateRenderer("BottomNameTag");
	mainRender_->SetCameraEffectOff();
}

void BottomNameTag::UpdateBefore()
{

}

void BottomNameTag::Update()
{
	// �� ������ ���� ���ǿ��� �ٸ� Bottom UI �� �Բ� �� �Ʒ��� �̵��� ����
}

void BottomNameTag::UpdateAfter()
{

}

void BottomNameTag::Render()
{
	mainRender_->Render();
}

void BottomNameTag::NameInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:
		mainRender_ = CreateRenderer("BottomNameTag");
		break;
	case 1:
		mainRender_ = CreateRenderer("BottomNameTag2");
		break;
	case 2:
		mainRender_ = CreateRenderer("BottomNameTag3");
		break;
	case 3:
		mainRender_ = CreateRenderer("BottomNameTag4");
		break;
	case 4:
		mainRender_ = CreateRenderer("BottomNameTag5");
		break;
	case 5:
		mainRender_ = CreateRenderer("BottomNameTag6");
		break;
	case 6:
		mainRender_ = CreateRenderer("BottomNameTag");
		break;
	case 7:
		mainRender_ = CreateRenderer("BottomNameTag");
		break;
	default:
		mainRender_ = CreateRenderer("BottomNameTag");
		break;
	}
}
void BottomNameTag::StartPosInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:
		SetPos({ 572, 610 });
		break;
	case 1:
		SetPos({ 572, 630 });
		break;
	case 2:
		SetPos({ 572, 650 });
		break;
	case 3:
		SetPos({ 572, 670 });
		break;
	case 4:
		SetPos({ 572, 690 });
		break;
	case 5:
		SetPos({ 572, 710 });
		break;
	case 6:
		SetPos({ 572, 730 });
		break;
	case 7:
		SetPos({ 572, 750 });
		break;
	default:
		SetPos({ 0, 0 });
		break;
	}
	mainRender_->SetCameraEffectOff();
}