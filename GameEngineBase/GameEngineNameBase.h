#pragma once
#include "GameEngineObjectBase.h"
#include <string>

class GameEngineNameBase : public GameEngineObjectBase
{
private:
	std::string name_;

public:
	std::string GetName() 
	{
		return name_;
	}

	void SetName(const std::string& _name) 
	{
		name_ = _name;
	}

public:
	virtual ~GameEngineNameBase() 
	{

	}
};

