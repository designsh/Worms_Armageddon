#include "GameEngineObjectBase.h"


// Static Var
// Static Func

// constructer destructer
GameEngineObjectBase::GameEngineObjectBase()
: isDeath_(false),
isUpdate_(true),
parent_(nullptr),
isDebug_(false)
{
}

GameEngineObjectBase::~GameEngineObjectBase()
{
}

//GameEngineObjectBase::GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept
//{
//}

//member Func