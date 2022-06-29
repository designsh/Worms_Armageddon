#pragma once

#include <GameEngineLevel.h>

class TestLevel : public GameEngineLevel
{
public:
	TestLevel(); 
	~TestLevel();

	TestLevel(const TestLevel& _other) = delete; 
	TestLevel(TestLevel&& _other) = delete; 

	TestLevel& operator=(const TestLevel& _other) = delete;
	TestLevel& operator=(const TestLevel&& _other) = delete;

	virtual void Loading() override;

};

