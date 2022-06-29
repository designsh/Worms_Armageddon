#pragma once
#include "EffectActor.h"

namespace Effect
{
	class kamismk : public EffectActor
	{
	private:	// member Var

	public:
		kamismk(); // default constructer ����Ʈ ������
		~kamismk(); // default destructer ����Ʈ �Ҹ���

	protected:		// delete constructer
		kamismk(const kamismk& _other) = delete; // default Copy constructer ����Ʈ ���������
		kamismk(kamismk&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

	private:		//delete operator
		kamismk& operator=(const kamismk& _other) = delete; // default Copy operator ����Ʈ ���� ������
		kamismk& operator=(const kamismk&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

	public:
		virtual void Start() override;
		virtual void UpdateBefore() override;
		virtual void Update() override;
		virtual void UpdateAfter() override;
		virtual void Render() override;
	};
}