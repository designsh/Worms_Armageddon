#pragma once
#include <GameEngineActor.h>
#include <vector>
#include <functional>
// 분류 : 
// 용도 : 
// 설명 : 

class Petroleum;
class PetroleumManager : public GameEngineActor
{
private:	// member Var

public:
	PetroleumManager(); // default constructer 디폴트 생성자
	~PetroleumManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	PetroleumManager(const PetroleumManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	PetroleumManager(PetroleumManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	PetroleumManager& operator=(const PetroleumManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	PetroleumManager& operator=(const PetroleumManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	float deltaTime_;
	std::vector<Petroleum*> VecPetroleum_;
	std::function<void()> UpdateFucn_;
	int VecPetroleumCount_; // 직접 새어보는 갯수

	int CoreCount_;

private:
	void PetroleumUpdate(int start, int end, float _deltaTime);
	void PetroleumMoveUpdate(int start, int end, float _deltaTime);
	void PetroleumGroundUpdate(int start, int end, float _deltaTime);

public:
	void AddVecPetroleum(Petroleum* _Petroleum)
	{
		VecPetroleum_.push_back(_Petroleum);
		VecPetroleumCount_++;
	}

	void ReservePetroleum(int reserve)
	{
		if (VecPetroleum_.size() < reserve)
			VecPetroleum_.reserve(reserve);
	}

	void AddReservePetroleum(int reserve)
	{
		if (VecPetroleum_.size() < reserve)
			VecPetroleum_.reserve(VecPetroleum_.size() + reserve);
	}

};

