#pragma once
#include <GameEngineActor.h>
#include <vector>
#include <functional>
// �з� : 
// �뵵 : 
// ���� : 

class Petroleum;
class PetroleumManager : public GameEngineActor
{
private:	// member Var

public:
	PetroleumManager(); // default constructer ����Ʈ ������
	~PetroleumManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	PetroleumManager(const PetroleumManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	PetroleumManager(PetroleumManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	PetroleumManager& operator=(const PetroleumManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	PetroleumManager& operator=(const PetroleumManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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
	int VecPetroleumCount_; // ���� ����� ����

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

