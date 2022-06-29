#include "PetroleumManager.h"
#include "Petroleum.h"
#include "GameEngineTime.h"
#include <thread>

PetroleumManager::PetroleumManager():
	VecPetroleumCount_(0),
	CoreCount_(0)
{

}

PetroleumManager::~PetroleumManager() // default destructer 디폴트 소멸자
{

}

PetroleumManager::PetroleumManager(PetroleumManager&& _other) noexcept :
	VecPetroleumCount_(0),
	CoreCount_(0)
{

}

void PetroleumManager::Start()
{
	CoreCount_ = std::thread::hardware_concurrency();
	//if (CoreCount_ > 4)
	//{
	//	CoreCount_ = 4;
	//}

	VecPetroleum_.reserve(160);
}

void PetroleumManager::UpdateBefore()
{
	//if (VecPetroleum_.empty())
	//	return;


	//int size = VecPetroleum_.size();

	//int core = size / CoreCount_;

	////if (CoreCount_ == 4)
	////{
	//std::thread core1([&]() {PetroleumUpdate(0, core); });
	//std::thread core2([&]() {PetroleumUpdate(core, core * 2); });
	//std::thread core3([&]() {PetroleumUpdate(core * 2, core * 3); });
	//std::thread core4([&]() {PetroleumUpdate(core * 3, size); });

	//core1.join();
	//core2.join();
	//core3.join();
	//core4.join();
	////}
	////else if (CoreCount_ == 3)
	////{
	////	std::thread core1([&]() {PetroleumUpdate(0, core); });
	////	std::thread core2([&]() {PetroleumUpdate(core, core * 2); });
	////	std::thread core3([&]() {PetroleumUpdate(core * 2, size); });
	////	core1.join();
	////	core2.join();
	////	core3.join();
	////}
	////else if (CoreCount_ == 2)
	////{
	////	std::thread core1([&]() {PetroleumUpdate(0, core); });
	////	std::thread core2([&]() {PetroleumUpdate(core, size); });
	////	core1.join();
	////	core2.join();
	////}
	////else if (CoreCount_ == 1)
	////{
	////	PetroleumUpdate(0, size);
	////}
	////else
	////{
	////	GameEngineDebug::MsgBoxError("std::thread::hardware_concurrency() 계산 오류");
	////}

	//if (VecPetroleumCount_ == 0)
	//{
	//	VecPetroleum_.clear();
	//	VecPetroleum_.reserve(160);
	//}
}

void PetroleumManager::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (VecPetroleum_.empty())
		return;

	int size = VecPetroleum_.size();

	int core = size / 10;

	//if (CoreCount_ == 9)
	//{
		//PetroleumMoveUpdate(0, size, deltaTime_);
		//PetroleumGroundUpdate(0, size, deltaTime_);
		/*std::thread core1([&]() {PetroleumGroundUpdate(0, core, deltaTime_); });
		std::thread core2([&]() {PetroleumGroundUpdate(core, core * 2, deltaTime_); });
		std::thread core3([&]() {PetroleumGroundUpdate(core * 2, core * 3, deltaTime_); });
		std::thread core4([&]() {PetroleumGroundUpdate(core * 3, core * 4, deltaTime_); });
		std::thread core5([&]() {PetroleumGroundUpdate(core * 4, core * 5, deltaTime_); });
		std::thread core6([&]() {PetroleumGroundUpdate(core * 5, core * 6, deltaTime_); });
		std::thread core7([&]() {PetroleumGroundUpdate(core * 6, core * 7, deltaTime_); });
		std::thread core8([&]() {PetroleumGroundUpdate(core * 7, core * 8, deltaTime_); });
		std::thread core9([&]() {PetroleumGroundUpdate(core * 8, core * 9, deltaTime_); });
		std::thread core10([&]() {PetroleumGroundUpdate(core * 9, size, deltaTime_); });
		core1.join();
		core2.join();
		core3.join();
		core4.join();
		core5.join();
		core6.join();
		core7.join();
		core8.join();
		core9.join();
		core10.join();*/
	//}

	//else if (CoreCount_ == 4)
	//{
	//	PetroleumMoveUpdate(0, size, deltaTime_);
	//	//PetroleumGroundUpdate(0, size, deltaTime_);
	//	std::thread core1([&]() {PetroleumGroundUpdate(0, core, deltaTime_); });
	//	std::thread core2([&]() {PetroleumGroundUpdate(core, core * 2, deltaTime_); });
	//	std::thread core3([&]() {PetroleumGroundUpdate(core * 2, core * 3, deltaTime_); });
	//	std::thread core4([&]() {PetroleumGroundUpdate(core * 3, size, deltaTime_); });
	//	core1.join();
	//	core2.join();
	//	core3.join();
	//	core4.join();	
	//}
	//else if (CoreCount_ == 3)
	//{
	//	std::thread core1([&]() {PetroleumUpdate(0, core, deltaTime_); });
	//	std::thread core2([&]() {PetroleumUpdate(core, core * 2, deltaTime_); });
	//	std::thread core3([&]() {PetroleumUpdate(core * 2, size, deltaTime_); });
	//	core1.join();
	//	core2.join();
	//	core3.join();
	//}
	//else if (CoreCount_ == 2)
	//{
	//	std::thread core1([&]() {PetroleumUpdate(0, core, deltaTime_); });
	//	std::thread core2([&]() {PetroleumUpdate(core, size, deltaTime_); });
	//	core1.join();
	//	core2.join();
	//}
	//else if (CoreCount_ == 1)
	//{
	//	PetroleumUpdate(0, size, deltaTime_);
	//}
	//else
	//{
	//	GameEngineDebug::MsgBoxError("std::thread::hardware_concurrency() 계산 오류");
	//}

	if (VecPetroleumCount_ == 0)
	{
		VecPetroleum_.clear();
		//VecPetroleum_.reserve(160);
	}
}

void PetroleumManager::PetroleumUpdate(int start, int end, float _deltaTime)
{
}

void PetroleumManager::PetroleumMoveUpdate(int start, int end, float _deltaTime)
{
	for (int i = start; i < end; ++i)
	{
		if (VecPetroleum_[i] == nullptr)
			continue;
		
		VecPetroleum_[i]->PetroleumMoveUpdate(_deltaTime);
	}
}

void PetroleumManager::PetroleumGroundUpdate(int start, int end, float _deltaTime)
{
	for (int i = start; i < end; ++i)
	{
		if (VecPetroleum_[i] == nullptr)
			continue;

		if (VecPetroleum_[i]->GetisLive())
		{
			VecPetroleum_[i]->PetroleumGroundUpdate(_deltaTime);			
		}
		else
		{
			//VecPetroleum_[i]->Death();
			VecPetroleum_[i]->Death();
			VecPetroleum_[i] = nullptr;
			VecPetroleumCount_--;
		}
	}
}

void PetroleumManager::UpdateAfter()
{
}

void PetroleumManager::Render()
{
}

