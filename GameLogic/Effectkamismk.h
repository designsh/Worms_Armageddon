#pragma once
#include "EffectActor.h"

namespace Effect
{
	class kamismk : public EffectActor
	{
	private:	// member Var

	public:
		kamismk(); // default constructer 디폴트 생성자
		~kamismk(); // default destructer 디폴트 소멸자

	protected:		// delete constructer
		kamismk(const kamismk& _other) = delete; // default Copy constructer 디폴트 복사생성자
		kamismk(kamismk&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

	private:		//delete operator
		kamismk& operator=(const kamismk& _other) = delete; // default Copy operator 디폴트 대입 연산자
		kamismk& operator=(const kamismk&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};
}