#pragma once
#include "EffectActor.h"

// 분류 : 
// 용도 : 
// 설명 : 
namespace Effect
{
	class ex :
		public EffectActor
	{
	private:	// member Var

	public:
		ex(); // default constructer 디폴트 생성자
		~ex(); // default destructer 디폴트 소멸자

	protected:		// delete constructer
		ex(const ex& _other) = delete; // default Copy constructer 디폴트 복사생성자
		ex(ex&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

	private:		//delete operator
		ex& operator=(const ex& _other) = delete; // default Copy operator 디폴트 대입 연산자
		ex& operator=(const ex&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};
}
