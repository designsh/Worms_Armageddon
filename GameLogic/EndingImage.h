#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class EndingImage : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* EndingImageRender_;

public:
	EndingImage(); // default constructer ����Ʈ ������
	~EndingImage(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	EndingImage(const EndingImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	EndingImage(EndingImage&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	EndingImage& operator=(const EndingImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EndingImage& operator=(const EndingImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

