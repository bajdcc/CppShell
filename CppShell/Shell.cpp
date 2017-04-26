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

    std::string trim(const std::string& str, char delim = ' ')
    {
        std::string::size_type pos = str.find_first_not_of(delim);
        if (pos == std::string::npos)
        {
            return str;
        }
        std::string::size_type pos2 = str.find_last_not_of(delim);
        if (pos2 != std::string::npos)
        {
            return str.substr(pos, pos2 - pos + 1);
        }
        return str.substr(pos);
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
    std::vector<std::string> names;
    std::vector<std::vector<std::string>> arg;
    for (auto& str : s)
    {
        str = std::trim(str);
        auto part = std::split(str, ' ');
        if (part.empty())
            return error("empty argument");
        names.push_back(part[0]);
        auto apt = CApp::get_type_by_name(part[0]);
        if (apt == app_none)
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
            return error(names[i] + ": " + app->get_err());
        app->set_inner_app(inner);
        inner = app;
    }
    while (app->available())
    {
        auto c = app->next();
        if (c != '\0')
            std::cout << c;
    }
}

void CShell::error(const std::string& str)
{
    std::cerr << str << std::endl;
}
