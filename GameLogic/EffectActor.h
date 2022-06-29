#pragma once
#include <GameEngineActor.h>
#include <GameEngineLevel.h>

// �з� : GameEngineActor
// �뵵 : ���� ����Ʈ �θ� Ŭ����
// ���� : ����Ʈ ����(����)�� ���� ���� ����Ʈ�� �θ� Ŭ����

class EffectActor : public GameEngineActor
{	
protected:	// member Var
	GameEngineRenderer* mainSpriteRender_;
	float4 Dir_; 

public:
	EffectActor();
	~EffectActor();
protected:		// delete constructer
	EffectActor(const EffectActor& _other) = delete;
	EffectActor(EffectActor&& _other) noexcept;
private:		//delete operator
	EffectActor& operator=(const EffectActor& _other) = delete;
	EffectActor& operator=(const EffectActor&& _other) = delete;
public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:

public:
	void SetDir(float4 Dir)
	{
		Dir_ = Dir;
	}

	const float4 GetDir()
	{
		return Dir_;
	}
};
