#include "stdafx.h"
#include "App.h"


CApp::CApp()
{
}


CApp::~CApp()
{
}

std::shared_ptr<CApp> CApp::create(app_t type)
{
    switch (type)
    {
    case app_none:
        break;
    case app_null:
        return std::make_shared<CAppNull>();
    case app_pipe:
        return std::make_shared<CAppPipe>();
    case app_range:
        return std::make_shared<CAppRange>();
    case app_take:
        return std::make_shared<CAppTake>();
    default:
        break;
    }
    assert(!"invalid type");
}

std::map<std::string, app_t> map_type;

struct CAppTypeInit
{
    CAppTypeInit()
    {
        map_type.insert(std::make_pair("pipe", app_pipe));
        map_type.insert(std::make_pair("range", app_range));
        map_type.insert(std::make_pair("take", app_take));
    }
};

static CAppTypeInit s_init;

app_t CApp::get_type_by_name(const std::string& name)
{
    auto f = map_type.find(name);
    if (f == map_type.end())
        return app_none;
    return f->second;
}

int CApp::set_arg(std::vector<std::string> arg)
{
    args = arg;
    return init();
}

void CApp::set_inner_app(std::shared_ptr<CApp> app)
{
    inner = app;
}

std::string CApp::get_err() const
{
    return error;
}

