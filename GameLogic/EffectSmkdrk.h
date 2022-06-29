#pragma once
#include "EffectActor.h"

// Æø¹ß ÀÌÆåÆ® namespace
namespace Effect
{
	class Smkdrk20 : public EffectActor
	{
	public:
		Smkdrk20();
		~Smkdrk20();
	protected:		// delete constructer
		Smkdrk20(const Smkdrk20& _other) = delete;
		Smkdrk20(Smkdrk20&& _other) noexcept;
	private:		//delete operator
		Smkdrk20& operator=(const Smkdrk20& _other) = delete;
		Smkdrk20& operator=(const Smkdrk20&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Smkdrk30 : public EffectActor
	{
	public:
		Smkdrk30();
		~Smkdrk30();
	protected:		// delete constructer
		Smkdrk30(const Smkdrk30& _other) = delete;
		Smkdrk30(Smkdrk30&& _other) noexcept;
	private:		//delete operator
		Smkdrk30& operator=(const Smkdrk30& _other) = delete;
		Smkdrk30& operator=(const Smkdrk30&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Smkdrk40 : public EffectActor
	{
	public:
		Smkdrk40();
		~Smkdrk40();
	protected:
		Smkdrk40(const Smkdrk40& _other) = delete;
		Smkdrk40(Smkdrk40&& _other) noexcept;
	private:		//delete operator
		Smkdrk40& operator=(const Smkdrk40& _other) = delete;
		Smkdrk40& operator=(const Smkdrk40&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};
}