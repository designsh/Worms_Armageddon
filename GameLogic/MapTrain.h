#pragma once
#include <GameEngineActor.h>

#include <thread>

// �з� : 
// �뵵 : 
// ���� : 
class MapTrain : public GameEngineActor
{
private:
	bool firstupdate_;

private:	// member Var
	GameEngineRenderer* gradationSpriteRender_;
	GameEngineRenderer* mainSpriteRender_;
	GameEngineRenderer* colSpriteRender_;
	GameEngineRenderer* boomSpriteRender_;
	GameEngineRenderer* boomEdgeSpriteRender_;
	GameEngineCollision* bodyCollision_;

	GameEngineRenderer* boomSpriteRender4_;
	GameEngineRenderer* boomSpriteRender6_;
	GameEngineRenderer* boomSpriteRender13_;
	GameEngineRenderer* boomSpriteRender25_;
	GameEngineRenderer* boomSpriteRender50_;
	GameEngineRenderer* boomSpriteRender75_;
	GameEngineRenderer* boomSpriteRender100_;
	GameEngineRenderer* boomEdgeSpriteRender4_;
	GameEngineRenderer* boomEdgeSpriteRender6_;
	GameEngineRenderer* boomEdgeSpriteRender13_;
	GameEngineRenderer* boomEdgeSpriteRender25_;
	GameEngineRenderer* boomEdgeSpriteRender50_;
	GameEngineRenderer* boomEdgeSpriteRender75_;
	GameEngineRenderer* boomEdgeSpriteRender100_;

	struct GroundUpdateDesc
	{
		friend class MapTrain;
	private:
		GroundUpdateDesc(float4 _pos, float4 _size, GameEngineRenderer* _image, GameEngineRenderer* _edgeimage)
		{
			Pos_ = _pos;
			size_ = _size;
			image_ = _image;
			edgeimage_ = _edgeimage;
		}
		float4 Pos_;
		float4 size_;
		GameEngineRenderer* edgeimage_;
		GameEngineRenderer* image_;
	};

	std::vector<GroundUpdateDesc> GroundUpdateList_;
	int CoreCount_;
	std::vector<std::thread> ThreadList_;

public:
	MapTrain(); // default constructer ����Ʈ ������
	~MapTrain(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MapTrain(const MapTrain& _other) = delete; // default Copy constructer ����Ʈ ���������
	MapTrain(MapTrain&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MapTrain& operator=(const MapTrain& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MapTrain& operator=(const MapTrain&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	//�����忡 ����� �Լ�
	void Threading(int start, int end);
	void GroundUpdate(GroundUpdateDesc Desc);

public:

	void GroundUpdate(float4 pos, float4 size);
	void GroundUpdate4(float4 pos);
	void GroundUpdate6(float4 pos);
	void GroundUpdate13(float4 pos);
	void GroundUpdate25(float4 pos);
	void GroundUpdate50(float4 pos);
	void GroundUpdate75(float4 pos);
	void GroundUpdate100(float4 pos);
	void BuildGirder(float4 pos, GameEngineRenderer* _Image, GameEngineRenderer* _ColImage);
};

