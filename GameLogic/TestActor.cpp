#include "TestActor.h"

#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineSoundPlayer.h>

#include "eCollisionGroup.h"

TestActor::TestActor()
	: mainRenderer_(nullptr)
	, bodyCollision_(nullptr)
	, testSoundPlayer_(nullptr)
	, state_(this)
{

}

TestActor::~TestActor()
{

}

void TestActor::Start()
{
	mainRenderer_ = CreateRenderer("test.bmp");
	mainRenderer_->CreateAnimation("Idle", "test.bmp", 0, 3, true, 0.05f);
	mainRenderer_->ChangeAnimation("Idle");

	bodyCollision_ = CreateCollision(eCollisionGroup::PLAYER, CollisionCheckType::POINT);
	bodyCollision_->SetColorCheck(RGB(0, 0, 0));

	//	testSoundPlayer_ = GameEngineSound::GetInst().CreateSoundPlayer();

	state_.CreateState("Idle", &TestActor::startIdle, &TestActor::updateIdle);
	state_.CreateState("Test", &TestActor::startTest, &TestActor::updateTest);

	state_.ChangeState("Idle");

	SetRenderOrder(0);
	SetUpdateOrder(0);
	SetPos({ 100, 100 });
}

void TestActor::UpdateBefore()
{
	mainRenderer_->AnimationUpdate();
}

void TestActor::Update()
{
	state_.Update();
}

void TestActor::UpdateAfter()
{
}

void TestActor::Render()
{
	mainRenderer_->Render();
}

StateInfo TestActor::startIdle(StateInfo _state)
{

	return "";
}

StateInfo TestActor::updateIdle(StateInfo _state)
{

	return "Test";
}

StateInfo TestActor::startTest(StateInfo _state)
{
//	testSoundPlayer_->PlayAlone("test.mp3");
	return StateInfo();
}

StateInfo TestActor::updateTest(StateInfo _state)
{
	return StateInfo();
}
