#include "stdafx.h"
#include "App.h"
#include "AppPipe.h"


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
    case app_pipe:
        return std::make_shared<CAppPipe>();
    default:
        break;
    }
    return nullptr;
}

std::map<std::string, app_t> map_type;

struct CAppTypeInit
{
    CAppTypeInit()
    {
        map_type.insert(std::make_pair("pipe", app_pipe));
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

void CApp::set_input_buffer(std::shared_ptr<CBuffer> buffer)
{
    input_buf = buffer;
}

void CApp::set_output_buffer(std::shared_ptr<CBuffer> buffer)
{
    output_buf = buffer;
}
