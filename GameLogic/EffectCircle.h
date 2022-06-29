#pragma once
#include "EffectActor.h"

// ¿øÇü Æø¹ß ÀÌÆåÆ® namespace
namespace Effect
{
	class Circle25 : public EffectActor
	{
	public:
		Circle25();
		~Circle25();
	protected:		// delete constructer
		Circle25(const Circle25& _other) = delete;
		Circle25(Circle25&& _other) noexcept;
	private:		//delete operator
		Circle25& operator=(const Circle25& _other) = delete;
		Circle25& operator=(const Circle25&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Circle50 : public EffectActor
	{
	public:
		Circle50();
		~Circle50();
	protected:		// delete constructer
		Circle50(const Circle50& _other) = delete;
		Circle50(Circle50&& _other) noexcept;
	private:		//delete operator
		Circle50& operator=(const Circle50& _other) = delete;
		Circle50& operator=(const Circle50&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Circle75 : public EffectActor
	{
	public:
		Circle75();
		~Circle75();
	protected:
		Circle75(const Circle75& _other) = delete;
		Circle75(Circle75&& _other) noexcept;
	private:		//delete operator
		Circle75& operator=(const Circle75& _other) = delete;
		Circle75& operator=(const Circle75&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};

	class Circle100 : public EffectActor
	{
	public:
		Circle100();
		~Circle100();
	protected:
		Circle100(const Circle100& _other) = delete;
		Circle100(Circle100&& _other) noexcept;
	private:		//delete operator
		Circle100& operator=(const Circle100& _other) = delete;
		Circle100& operator=(const Circle100&& _other) = delete;
	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};
};