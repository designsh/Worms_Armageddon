#pragma once
#include <GameEngineLevel.h>
#include "WaterLevel.h"	
// �з� : 
// �뵵 : 
// ���� : 

class LoadingImage;
class FadeObject;
class WindController;
class MouseObject;
class PlayLevel : public GameEngineLevel
{
private:	// member Var
	class MapTrain* Train_;
	class Bazooka* Bazooka_;
	class GameController* Controller_;
	bool isDebugOn_;

	MouseObject* MouseObject_;

private:
	GameEngineMath::Random randomGenerator_;
	bool isWormLanded_;
	bool isFadeIn_;
	static FadeObject* fadeObject_;
	float fadeInterTime_;
	LoadingImage* loadingImage_;

public:
	PlayLevel(); // default constructer ����Ʈ ������
	~PlayLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	PlayLevel(const PlayLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	PlayLevel(PlayLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	PlayLevel& operator=(const PlayLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	PlayLevel& operator=(const PlayLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Loading() override;
	void LevelUpdate() override;


public:
	void CreateGimmickObject();

	void CreateExplosion100(float4 Pos, int _Damage = 100, bool _DamageToDist = false); //test
	void CreateExplosion75(float4 Pos, int _Damage = 75, bool _DamageToDist = false); //test
	void CreateExplosion50(float4 Pos, int _Damage = 50, bool _DamageToDist = false); //test
	void CreateExplosion25(float4 Pos, int _Damage = 25, bool _DamageToDist = false); //test

	void CreateGrave(float4 Pos);

	void CreatePurpleStarEffect(float4 Pos);

	void GroundUpdate100(float4 _pos);
	void GroundUpdate75(float4 _pos);
	void GroundUpdate50(float4 _pos);
	void GroundUpdate25(float4 _pos);
	void GroundUpdate13(float4 _pos);
	void GroundUpdate6(float4 _pos);
	void GroundUpdate4(float4 _pos);

	void KeySetting();

	bool GetDebug()
	{
		return isDebugOn_;
	}

	MapTrain* GetMap() const
	{
		return Train_;
	}

	GameController* GetGameController()
	{
		return Controller_;
	}

	const float GetWaterLevel();

private:
	void wormLoading();
	void PJWLevelUpdate();

private:
	void RandomWormArrange(float _minX, float _maxX);
};

