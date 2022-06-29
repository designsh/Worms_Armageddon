#pragma once
#include "EffectActor.h"

// ¿øÇü Æø¹ß ÀÌÆåÆ® namespace
namespace Effect
{
	class Elipse25 : public EffectActor
	{
	public:
		Elipse25();
		~Elipse25();
	protected:		// delete constructer
		Elipse25(const Elipse25& _other) = delete;
		Elipse25(Elipse25&& _other) noexcept;
	private:		//delete operator
		Elipse25& operator=(const Elipse25& _other) = delete;
		Elipse25& operator=(const Elipse25&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Elipse50 : public EffectActor
	{
	public:
		Elipse50();
		~Elipse50();
	protected:		// delete constructer
		Elipse50(const Elipse50& _other) = delete;
		Elipse50(Elipse50&& _other) noexcept;
	private:		//delete operator
		Elipse50& operator=(const Elipse50& _other) = delete;
		Elipse50& operator=(const Elipse50&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Elipse75 : public EffectActor
	{
	public:
		Elipse75();
		~Elipse75();
	protected:
		Elipse75(const Elipse75& _other) = delete;
		Elipse75(Elipse75&& _other) noexcept;
	private:		//delete operator
		Elipse75& operator=(const Elipse75& _other) = delete;
		Elipse75& operator=(const Elipse75&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Elipse100 : public EffectActor
	{
	public:
		Elipse100();
		~Elipse100();
	protected:
		Elipse100(const Elipse100& _other) = delete;
		Elipse100(Elipse100&& _other) noexcept;
	private:		//delete operator
		Elipse100& operator=(const Elipse100& _other) = delete;
		Elipse100& operator=(const Elipse100&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};
};