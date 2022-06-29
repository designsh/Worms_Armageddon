#include "ExplosionSize.h"
#include "EffectCircle.h"
#include "EffectElipse.h"
#include "EffectSmklt.h"
#include "EffectSmkdrk.h"
#include "EffectFlame.h"
#include "Effectex.h"

#include "GameEngineLevel.h"
#include "Petroleum.h"

#include "eCollisionGroup.h"
#include <GameEngineCollision.h>

// Size25

ExplosionSize25::ExplosionSize25()
{
}

ExplosionSize25::~ExplosionSize25()
{
}

ExplosionSize25::ExplosionSize25(ExplosionSize25&& _other) noexcept
{
}

void ExplosionSize25::Start()
{
	Explosion::Start();
	ExplosionCollision_->SetSize({ 25.f, 25.f });

	EffectActor* Effect;
	GameEngineMath::Random random;
	float RandomFloat;
	float degree;
	float4 RandomRot = { 1.f,0.f,0.f };

	Effect = parentLevel_->CreateActor<Effect::Circle25>(pos_);	
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	Effect = parentLevel_->CreateActor<Effect::Elipse25>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	for (int i = 0; i < 9; ++i)
	{
		// �ʱ�ȭ
		RandomRot = { 1.f,0.f,0.f }; //�ʱ�ȭ

		//������
		RandomFloat = random.RandomFloat(0.f, 10.f);
		degree = i * 36.f;

		//����
		RandomRot = RandomRot.DegreeTofloat2(degree); 
		RandomRot.x *= RandomFloat; 
		RandomRot.y *= RandomFloat;

		Effect = parentLevel_->CreateActor<Effect::Smklt25>(pos_ + RandomRot);
		Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));
		Effect->SetDir(RandomRot);
	}

	// Flame �߽� pos ���� +- 15�� ���� �������� �����Բ� ���� ����
	{
		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = -30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame1* Flame1Effect = parentLevel_->CreateActor<Effect::Flame1>(pos_);
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));


		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = -15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame2* Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 0.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame1Effect = parentLevel_->CreateActor<Effect::Flame1>(pos_);
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(5.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	}
}

void ExplosionSize25::UpdateBefore()
{
}

void ExplosionSize25::Update()
{
	Explosion::Update();
}

void ExplosionSize25::UpdateAfter()
{
}

void ExplosionSize25::Render()
{
	Explosion::Render();
}

// ExplosionSize50

ExplosionSize50::ExplosionSize50()
{
}

ExplosionSize50::~ExplosionSize50()
{
}

ExplosionSize50::ExplosionSize50(ExplosionSize50&& _other) noexcept
{
}

void ExplosionSize50::Start()
{
	Explosion::Start();
	ExplosionCollision_->SetSize({ 50.f, 50.f });

	EffectActor* Effect;
	GameEngineMath::Random random;
	float RandomFloat;
	float degree;
	float4 RandomRot = { 1.f,0.f,0.f };

	Effect = parentLevel_->CreateActor<Effect::Circle50>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	Effect = parentLevel_->CreateActor<Effect::Elipse50>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	for (int i = 0; i < 9; ++i)
	{
		// �ʱ�ȭ
		RandomRot = { 1.f,0.f,0.f }; //�ʱ�ȭ

		//������
		RandomFloat = random.RandomFloat(7.f, 25.f);// 10~40 ���� ������ ��, ���� �������� �ɰ�
		degree = i * 36.f;

		//����
		RandomRot = RandomRot.DegreeTofloat2(degree); // ���� 1�� ���� ���� 0~360�� ������ ����	
		RandomRot.x *= RandomFloat; // ���� ������ ������ ���� ���ϱ�
		RandomRot.y *= RandomFloat;

		Effect = parentLevel_->CreateActor<Effect::Smklt50>(pos_ + RandomRot);
		Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));
		Effect->SetDir(RandomRot);
	}
	
	// Flame �߽� pos ���� +- 15�� ���� �������� �����Բ� ���� ����
	{
		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = -30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame1* Flame1Effect = parentLevel_->CreateActor<Effect::Flame1>(pos_);
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));


		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = -15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame2* Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 0.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame1Effect = parentLevel_->CreateActor<Effect::Flame1>(pos_);
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect)); 
	};
}

void ExplosionSize50::UpdateBefore()
{
}

void ExplosionSize50::Update()
{
	Explosion::Update();
}

void ExplosionSize50::UpdateAfter()
{
}

void ExplosionSize50::Render()
{
	Explosion::Render();
}

// ExplosionSize75

ExplosionSize75::ExplosionSize75()
{
}

ExplosionSize75::~ExplosionSize75()
{
}

ExplosionSize75::ExplosionSize75(ExplosionSize75&& _other) noexcept
{
}

void ExplosionSize75::Start()
{
	Explosion::Start();
	ExplosionCollision_->SetSize({ 75.f, 75.f });

	GameEngineMath::Random random;
	EffectActor* Effect;
	float4 RandomRot = { 1.f,0.f,0.f };
	float RandomFloat;
	float degree;

	Effect = parentLevel_->CreateActor<Effect::Circle75>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	Effect = parentLevel_->CreateActor<Effect::Elipse75>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	Effect = parentLevel_->CreateActor<Effect::ex>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	for (int i = 0; i < 9; ++i)
	{
		// �ʱ�ȭ
		RandomRot = { 1.f,0.f,0.f }; //�ʱ�ȭ

		//������
		RandomFloat = random.RandomFloat(7.5f, 30.f);// 10~40 ���� ������ ��, ���� �������� �ɰ�
		degree = i * 36.f;

		//����
		RandomRot = RandomRot.DegreeTofloat2(degree); // ���� 1�� ���� ���� 0~360�� ������ ����	
		RandomRot.x *= RandomFloat; // ���� ������ ������ ���� ���ϱ�
		RandomRot.y *= RandomFloat;

		Effect = parentLevel_->CreateActor<Effect::Smklt75>(pos_ + RandomRot);
		Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));
		Effect->SetDir(RandomRot);
	}

	// Flame �߽� pos ���� +- 15�� ���� �������� �����Բ� ���� ����
	{
		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = -30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame1* Flame1Effect = parentLevel_->CreateActor<Effect::Flame1>(pos_);
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));


		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = -15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame2* Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 0.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame1Effect = parentLevel_->CreateActor<Effect::Flame1>(pos_);
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));
	}
}

void ExplosionSize75::UpdateBefore()
{
}

void ExplosionSize75::Update()
{
	Explosion::Update();
}

void ExplosionSize75::UpdateAfter()
{
}

void ExplosionSize75::Render()
{
	Explosion::Render();
}

// ExplosionSize100

ExplosionSize100::ExplosionSize100()
{
}

ExplosionSize100::~ExplosionSize100()
{
}

ExplosionSize100::ExplosionSize100(ExplosionSize100&& _other) noexcept
{
}

void ExplosionSize100::Start()
{
	Explosion::Start();

	ExplosionCollision_->SetSize({ 100.f, 100.f });

	EffectActor* Effect;

	Effect = parentLevel_->CreateActor<Effect::Circle100>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	Effect = parentLevel_->CreateActor<Effect::Elipse100>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	Effect = parentLevel_->CreateActor<Effect::ex>(pos_);
	Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));

	GameEngineMath::Random random;
	float RandomFloat;
	float degree;
	float4 RandomRot = { 1.f,0.f,0.f };
	//float semidiameter = 50.f;


	//������ 10~40 ���� ���������� 36�� �������� 10�� ���� �ǵ��� ����,
	for (int i = 0; i < 9; ++i)
	{
		// �ʱ�ȭ
		RandomRot = { 1.f,0.f,0.f }; //�ʱ�ȭ

		//������
		RandomFloat = random.RandomFloat(10.f, 40.f);// 10~40 ���� ������ ��, ���� �������� �ɰ�
		degree = i * 36.f;

		//����
		RandomRot = RandomRot.DegreeTofloat2(degree); // ���� 1�� ���� ���� 0~360�� ������ ����	
		RandomRot.x *= RandomFloat; // ���� ������ ������ ���� ���ϱ�
		RandomRot.y *= RandomFloat;

		Effect = parentLevel_->CreateActor<Effect::Smklt100>(pos_ + RandomRot);
		Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));
		Effect->SetDir(RandomRot);
	}

	// Flame �߽� pos ���� +- 15�� ���� �������� �����Բ� ���� ����
	{
		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = -30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame1* Flame1Effect = parentLevel_->CreateActor<Effect::Flame1>(pos_);
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));


		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = -15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame2* Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 0.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame1Effect = parentLevel_->CreateActor<Effect::Flame1>(pos_);
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //�ʱ�ȭ

		degree = 30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = parentLevel_->CreateActor<Effect::Flame2>(pos_);
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetRenderOrder(static_cast<int>(RenderOrder::Effect));
	}

}

void ExplosionSize100::UpdateBefore()
{
}

void ExplosionSize100::Update()
{
	Explosion::Update();
}

void ExplosionSize100::UpdateAfter()
{
}

void ExplosionSize100::Render()
{
	Explosion::Render();
}
