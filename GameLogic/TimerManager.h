#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class TimerManager
{
private:	// member Var

public:
	TimerManager(); // default constructer ����Ʈ ������
	~TimerManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	TimerManager(const TimerManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	TimerManager(TimerManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TimerManager& operator=(const TimerManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TimerManager& operator=(const TimerManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

