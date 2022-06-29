#pragma once
#include "EffectActor.h"

// �з� : 
// �뵵 : 
// ���� : 
namespace Effect
{
	class ex :
		public EffectActor
	{
	private:	// member Var

	public:
		ex(); // default constructer ����Ʈ ������
		~ex(); // default destructer ����Ʈ �Ҹ���

	protected:		// delete constructer
		ex(const ex& _other) = delete; // default Copy constructer ����Ʈ ���������
		ex(ex&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

	private:		//delete operator
		ex& operator=(const ex& _other) = delete; // default Copy operator ����Ʈ ���� ������
		ex& operator=(const ex&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};
}
