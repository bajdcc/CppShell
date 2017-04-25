#include "stdafx.h"
#include "Shell.h"
#include "App.h"


template<typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
}

namespace std
{
    std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        ::split(s, delim, std::back_inserter(elems));
        return elems;
    }
}

CShell::CShell()
{
}


CShell::~CShell()
{
}

void CShell::exec(const std::string& cmd)
{
    auto s = std::split(cmd, '|');
    std::vector<app_t> cmder;
    std::vector<std::vector<std::string>> arg;
    for (auto& str : s)
    {
        auto part = std::split(str, ' ');
        if (part.empty())
            return error("empty argument");
        auto apt = CApp::get_type_by_name(part[0]);
        if (apt == app_none || apt == app_null)
            return error("invalid application: " + str);
        part.erase(part.begin());
        cmder.push_back(apt);
        arg.push_back(part);
    }
    auto inner = CApp::create(app_null);
    std::shared_ptr<CApp> app;
    for (uint32_t i = 0; i < cmder.size(); i++)
    {
        app = CApp::create(cmder[i]);
        if (app->set_arg(arg[i]) != 0)
            return error(app->get_err());
        app->set_inner_app(inner);
        inner = app;
    }
    while (app->available())
    {
        std::cout << app->next();
    }
}

void CShell::error(const std::string& str)
{
    std::cerr << str << std::endl;
}
