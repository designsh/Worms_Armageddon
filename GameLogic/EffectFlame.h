#pragma once
#include "EffectActor.h"

// ���� ����Ʈ namespace
namespace Effect
{
	// ������, ������ �������� �̵�, ���� Ƣ�ٰ� �߷��� ������ �޾� �Ʒ��� ���ϴ� ������Բ�
	// update ���� ���� ����Ʈ�� ��ȯ�ϰ�, ���� ����Ʈ�� ���ϸ��̼� ������ ����

	class Flame1 : public EffectActor
	{
	public:
		Flame1();
		~Flame1();
	protected:		// delete constructer
		Flame1(const Flame1& _other) = delete;
		Flame1(Flame1&& _other) noexcept;

	private:
		float deltaTime_;
		float GravityAcc;
		float GravitySpeed;
		float ExplodeSpeed;
		float gentime_;
		class Smkdrk30* smkdrk30_;
	public:
		float4 Dir_;

	private:		//delete operator
		Flame1& operator=(const Flame1& _other) = delete;
		Flame1& operator=(const Flame1&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;

	public:
		void SetDir(float4 Dir)
		{
			Dir_ = Dir;
		}
	};

	class Flame2 : public EffectActor
	{
	public:
		Flame2();
		~Flame2();
	protected:		// delete constructer
		Flame2(const Flame2& _other) = delete;
		Flame2(Flame2&& _other) noexcept;

	private:
		float deltaTime_;
		float GravityAcc;
		float GravitySpeed;
		float ExplodeSpeed;
		float gentime;
		Smkdrk30* smkdrk30_;

	public:
		float4 Dir_;

	private:		//delete operator
		Flame2& operator=(const Flame2& _other) = delete;
		Flame2& operator=(const Flame2&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;

	public:
		void SetDir(float4 Dir)
		{
			Dir_ = Dir;
		}
	};
};