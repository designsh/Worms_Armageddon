#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class LoadingImage : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* backRender_;
	GameEngineRenderer* mainSpriteRender_;
public:
	LoadingImage(); // default constructer ����Ʈ ������
	~LoadingImage(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LoadingImage(const LoadingImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	LoadingImage(LoadingImage&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LoadingImage& operator=(const LoadingImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LoadingImage& operator=(const LoadingImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

