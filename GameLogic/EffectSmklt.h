#pragma once
#include "EffectActor.h"

// Æø¹ß ÀÌÆåÆ® namespace
namespace Effect
{
	class Smklt25 : public EffectActor
	{
	private:
		float deltaTime_;
	public:
		Smklt25();
		~Smklt25();
	protected:		// delete constructer
		Smklt25(const Smklt25& _other) = delete;
		Smklt25(Smklt25&& _other) noexcept;
	private:		//delete operator
		Smklt25& operator=(const Smklt25& _other) = delete;
		Smklt25& operator=(const Smklt25&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Smklt50 : public EffectActor
	{
	private:
		float deltaTime_;
	public:
		Smklt50();
		~Smklt50();
	protected:		// delete constructer
		Smklt50(const Smklt50& _other) = delete;
		Smklt50(Smklt50&& _other) noexcept;
	private:		//delete operator
		Smklt50& operator=(const Smklt50& _other) = delete;
		Smklt50& operator=(const Smklt50&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Smklt75 : public EffectActor
	{
	private:
		float deltaTime_;
	public:
		Smklt75();
		~Smklt75();
	protected:
		Smklt75(const Smklt75& _other) = delete;
		Smklt75(Smklt75&& _other) noexcept;
	private:		//delete operator
		Smklt75& operator=(const Smklt75& _other) = delete;
		Smklt75& operator=(const Smklt75&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Smklt100 : public EffectActor
	{
	private:
		float deltaTime_;
	public:
		Smklt100();
		~Smklt100();
	protected:
		Smklt100(const Smklt100& _other) = delete;
		Smklt100(Smklt100&& _other) noexcept;
	private:		//delete operator
		Smklt100& operator=(const Smklt100& _other) = delete;
		Smklt100& operator=(const Smklt100&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};
};