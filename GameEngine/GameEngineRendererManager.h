#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRendererManager
{
private:	// member Var

public:
	GameEngineRendererManager(); // default constructer ����Ʈ ������
	~GameEngineRendererManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRendererManager(const GameEngineRendererManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRendererManager(GameEngineRendererManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRendererManager& operator=(const GameEngineRendererManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRendererManager& operator=(const GameEngineRendererManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

