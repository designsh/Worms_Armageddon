#pragma once
#include "EffectActor.h"

// 폭발 이펙트 namespace
namespace Effect
{
	// 생성후, 정해진 방향으로 이동, 위로 튀다가 중력의 영향을 받아 아래로 향하다 사라지게끔
	// update 에서 연기 이펙트를 소환하고, 연기 이펙트는 에니메이션 종료후 삭제

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