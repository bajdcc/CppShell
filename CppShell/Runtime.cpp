#include "stdafx.h"
#include "Runtime.h"


CRuntime::CRuntime()
{
}


CRuntime::~CRuntime()
{
}

void CRuntime::add_app(std::shared_ptr<CApp> app)
{
    apps.push_back(app);
}

void CRuntime::run()
{

}
