#include "MapTrain.h"
#include "GameOptionInfo.h"
#include "eCollisionGroup.h"

#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"

MapTrain::MapTrain() // default constructer 디폴트 생성자
	:firstupdate_(false),
	gradationSpriteRender_(nullptr),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr),
	boomEdgeSpriteRender_(nullptr),
	boomSpriteRender25_(nullptr),
	boomSpriteRender50_(nullptr),
	boomSpriteRender75_(nullptr),
	boomSpriteRender100_(nullptr),
	boomEdgeSpriteRender25_(nullptr),
	boomEdgeSpriteRender50_(nullptr),
	boomEdgeSpriteRender75_(nullptr),
	boomEdgeSpriteRender100_(nullptr),
	boomEdgeSpriteRender13_(nullptr),
	boomSpriteRender13_(nullptr),
	bodyCollision_(nullptr)
{
	SetRenderOrder((int)RenderOrder::Map);
}

MapTrain::~MapTrain() // default destructer 디폴트 소멸자
{

}

MapTrain::MapTrain(MapTrain&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	:firstupdate_(_other.firstupdate_),
	gradationSpriteRender_(nullptr),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr),
	boomEdgeSpriteRender_(nullptr),
	boomSpriteRender25_(nullptr),
	boomSpriteRender50_(nullptr),
	boomSpriteRender75_(nullptr),
	boomSpriteRender100_(nullptr),
	boomEdgeSpriteRender25_(nullptr),
	boomEdgeSpriteRender50_(nullptr),
	boomEdgeSpriteRender75_(nullptr),
	boomEdgeSpriteRender100_(nullptr),
	boomEdgeSpriteRender13_(nullptr),
	boomSpriteRender13_(nullptr),
	bodyCollision_(nullptr)
{

}

void MapTrain::Start()
{
	CoreCount_ = std::thread::hardware_concurrency();
	ThreadList_.resize(CoreCount_);

	//float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	//
	//gradationSpriteRender_ = CreateRenderer("Gradient");
	//float4 ImageSize = gradationSpriteRender_->GetImageSize();
	//gradationSpriteRender_->SetPivotPos(ImageSize.halffloat4());
	//gradationSpriteRender_->SetCameraEffectOff();
	//
	//gradationSpriteRender_->SetRenderSize(WindowSize);

	boomSpriteRender_ = CreateRenderer("Boom");
	boomEdgeSpriteRender_ = CreateRenderer("BoomEdge");

	boomSpriteRender4_ = CreateRenderer("Boom_4");
	boomSpriteRender6_ = CreateRenderer("Boom_6");
	boomSpriteRender13_ = CreateRenderer("Boom_13");
	boomSpriteRender25_ = CreateRenderer("Boom_25");
	boomSpriteRender50_ = CreateRenderer("Boom_50");
	boomSpriteRender75_ = CreateRenderer("Boom_75");
	boomSpriteRender100_ = CreateRenderer("Boom_100");
	boomEdgeSpriteRender4_ = CreateRenderer("BoomEdge_4");
	boomEdgeSpriteRender6_ = CreateRenderer("BoomEdge_6");
	boomEdgeSpriteRender13_ = CreateRenderer("BoomEdge_13");
	boomEdgeSpriteRender25_ = CreateRenderer("BoomEdge_25");
	boomEdgeSpriteRender50_ = CreateRenderer("BoomEdge_50");
	boomEdgeSpriteRender75_ = CreateRenderer("BoomEdge_75");
	boomEdgeSpriteRender100_ = CreateRenderer("BoomEdge_100");
}

void MapTrain::UpdateBefore()
{
	// 렌더러를 이때 생성한다
	if (false == firstupdate_)
	{
		// 맵 렌더러 생성 및 위치 지정
		mainSpriteRender_ = CreateRenderer(GameOptionInfo::CurPlayMap);
		float4 imageSize = mainSpriteRender_->GetImageSize();
		mainSpriteRender_->SetPivotPos(imageSize.halffloat4());

		// 충돌맵 렌더러 생성 및 위치 지정
		colSpriteRender_ = CreateRenderer(GameOptionInfo::CurPlayColMap);
		imageSize = colSpriteRender_->GetImageSize();
		colSpriteRender_->SetPivotPos(imageSize.halffloat4());

		bodyCollision_ = CreateCollision(eCollisionGroup::MAP, CollisionCheckType::IMAGE);
		bodyCollision_->SetImage(GameOptionInfo::CurPlayColMap);

		// 최초갱신일때만 실행되도록 설정
		firstupdate_ = true;
	}
}

void MapTrain::Update()
{
	//if (GroundUpdateList_.empty())
	//	return;

	//int updatecount = GroundUpdateList_.size() / CoreCount_;
	//for (int i = 0 ; i < CoreCount_; ++i)
	//{
	//	if (i == CoreCount_ - 1)
	//	{
	//		ThreadList_[i] = std::thread([&]() {Threading(i * updatecount, GroundUpdateList_.size()); });
	//		break;
	//	}
	//	ThreadList_[i] = std::thread([&]() {Threading(i* updatecount, (i+1) * updatecount); });
	//}

	//for (auto& Thread : ThreadList_)
	//{
	//	Thread.join();
	//}

	//GroundUpdateList_.clear();
}

void MapTrain::UpdateAfter()
{
	//TODO :: 쓰레드 구현은 해놓음
	/*if (GroundUpdateList_.empty())
		return;
	if (std::thread::hardware_concurrency() <5)
		GameEngineDebug::MsgBoxError("쓰레드를 돌리기에 cpu가 너무 좆같습니다.");

	int size = GroundUpdateList_.size();
	int core = size * 0.25f;

	std::thread core1([&]() {Threading(0, core); });
	std::thread core2([&]() {Threading(core, core * 2); });
	std::thread core3([&]() {Threading(core * 2, core * 3); });
	std::thread core4([&]() {Threading(core * 3, size); });

	core1.join();
	core2.join();
	core3.join();
	core4.join();

	if (!(core1.joinable() && core2.joinable() && core3.joinable() && core4.joinable()))
	{
		GroundUpdateList_.clear();
	}*/
}

void MapTrain::Render()
{
	// 그라데이션 
	//gradationSpriteRender_->Render();

	// 충돌맵
	colSpriteRender_->Render();

	// 진짜 맵
	mainSpriteRender_->Render();
}

//void MapTrain::Threading(int start, int end)
//{
//	for (int i = start; i < end; ++i)
//	{
//		GroundUpdate(GroundUpdateList_[i]);
//	}
//}

//쓰레드에 사용할 함수
//void MapTrain::GroundUpdate(GroundUpdateDesc Desc)
//{
//	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
//	ColImage->TransCopy(Desc.image_->GetImage(),
//		Desc.Pos_,
//		Desc.size_,
//		{ 0.f, 0.f },
//		Desc.size_,
//		RGB(0, 255, 0));
//
//	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
//	mapImage->TransCopy(Desc.edgeimage_->GetImage(),
//		Desc.Pos_,
//		Desc.size_,
//		{ 0.f, 0.f },
//		Desc.size_,
//		RGB(0, 255, 0));
//
//	mapImage->TransCopy(colSpriteRender_->GetImage(),
//		{ 0.f, 0.f },
//		colSpriteRender_->GetImageSize(),
//		{ 0.f, 0.f },
//		colSpriteRender_->GetImageSize(),
//		RGB(0, 0, 255));
//}

//void MapTrain::GroundUpdate(float4 pos, float4 size)
//{
//	GroundUpdateList_.push_back(GroundUpdateDesc
//	(pos, size, boomSpriteRender_, boomEdgeSpriteRender_));
//}
//
//void MapTrain::GroundUpdate4(float4 pos)
//{
//	GroundUpdateList_.push_back(GroundUpdateDesc
//	(pos, float4(16.f, 16.f), boomSpriteRender4_, boomEdgeSpriteRender4_));
//}
//
//void MapTrain::GroundUpdate6(float4 pos)
//{
//	GroundUpdateList_.push_back(GroundUpdateDesc
//	(pos, float4(18.f, 18.f), boomSpriteRender6_, boomEdgeSpriteRender6_));
//}
//
//void MapTrain::GroundUpdate13(float4 pos)
//{
//	GroundUpdateList_.push_back(GroundUpdateDesc
//	(pos, float4(25.f, 25.f), boomSpriteRender13_, boomEdgeSpriteRender13_));
//}
//
//void MapTrain::GroundUpdate25(float4 pos)
//{
//	GroundUpdateList_.push_back(GroundUpdateDesc
//	(pos, float4(37.f, 37.f), boomSpriteRender25_, boomEdgeSpriteRender25_));
//}
//
//void MapTrain::GroundUpdate50(float4 pos)
//{
//	GroundUpdateList_.push_back(GroundUpdateDesc
//	(pos, float4(62.f, 62.f), boomSpriteRender50_, boomEdgeSpriteRender50_));
//}
//
//void MapTrain::GroundUpdate75(float4 pos)
//{
//	GroundUpdateList_.push_back(GroundUpdateDesc
//	(pos, float4(87.f, 87.f), boomSpriteRender75_, boomEdgeSpriteRender75_));
//}
//
//void MapTrain::GroundUpdate100(float4 pos)
//{
//	GroundUpdateList_.push_back(GroundUpdateDesc
//	(pos, float4(112.f,112.f), boomSpriteRender100_, boomEdgeSpriteRender100_));
//}

void MapTrain::GroundUpdate(float4 pos, float4 size)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender_->GetImage(),
		pos,
		size,
		{ 0.f, 0.f },
		{ 100.f, 100.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender_->GetImage(),
		pos,
		size,
		{ 0.f, 0.f },
		{ 100.f, 100.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}
void MapTrain::GroundUpdate4(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender4_->GetImage(),
		pos,
		{ 16.f, 16.f },
		{ 0.f, 0.f },
		{ 16.f, 16.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender4_->GetImage(),
		pos,
		{ 16.f, 16.f },
		{ 0.f, 0.f },
		{ 16.f, 16.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate6(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender6_->GetImage(),
		pos,
		{ 18.f, 18.f },
		{ 0.f, 0.f },
		{ 18.f, 18.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender6_->GetImage(),
		pos,
		{ 18.f, 18.f },
		{ 0.f, 0.f },
		{ 18.f, 18.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate13(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender13_->GetImage(),
		pos,
		{ 25.f, 25.f },
		{ 0.f, 0.f },
		{ 25.f, 25.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender13_->GetImage(),
		pos,
		{ 25.f, 25.f },
		{ 0.f, 0.f },
		{ 25.f, 25.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate25(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender25_->GetImage(),
		pos,
		{ 37.f, 37.f },
		{ 0.f, 0.f },
		{ 37.f, 37.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender25_->GetImage(),
		pos,
		{ 37.f, 37.f },
		{ 0.f, 0.f },
		{ 37.f, 37.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate50(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender50_->GetImage(),
		pos,
		{ 62.f, 62.f },
		{ 0.f, 0.f },
		{ 62.f, 62.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender50_->GetImage(),
		pos,
		{ 62.f, 62.f },
		{ 0.f, 0.f },
		{ 62.f, 62.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate75(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender75_->GetImage(),
		pos,
		{ 87.f, 87.f },
		{ 0.f, 0.f },
		{ 87.f, 87.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender75_->GetImage(),
		pos,
		{ 87.f, 87.f },
		{ 0.f, 0.f },
		{ 87.f, 87.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate100(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender100_->GetImage(),
		pos,
		{ 112.f, 112.f },
		{ 0.f, 0.f },
		{ 112.f, 112.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender100_->GetImage(),
		pos,
		{ 112.f, 112.f },
		{ 0.f, 0.f },
		{ 112.f, 112.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::BuildGirder(float4 pos, GameEngineRenderer* _Image, GameEngineRenderer* _ColImage)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(_ColImage->GetImage(),
		pos,
		_ColImage->GetImageSize(),
		{ 0.f, 0.f },
		_ColImage->GetImageSize(),
		RGB(255, 0, 255));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(_Image->GetImage(),
		pos,
		_Image->GetImageSize(),
		{ 0.f, 0.f },
		_Image->GetImageSize(),
		RGB(255, 0, 255));
}

