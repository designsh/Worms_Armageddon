#include "TestLevel.h"

#include "TestActor.h"
#include "FadeObject.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

void TestLevel::Loading()
{
	CreateActor<TestActor>("TestActor");
	CreateActor<FadeObject>("FadeObject");
}
