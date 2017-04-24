#include "stdafx.h"
#include "Shell.h"
#include "App.h"
#include "Buffer.h"
#include "Runtime.h"


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
    for (const std::string& str : s)
    {
        auto part = std::split(str, ' ');
        if (part.empty())
            return error("empty argument");
        auto apt = CApp::get_type_by_name(part[0]);
        if (apt == app_none)
            return error("invalid application: " + str);
        part.erase(part.begin());
        cmder.push_back(apt);
        arg.push_back(part);
    }
    std::vector<std::shared_ptr<CBuffer>> buffers(cmder.size() + 1);
    for (uint32_t i = 0; i < buffers.size(); i++)
    {
        buffers[i] = std::make_shared<CBuffer>();
    }
    CRuntime rt;
    for (uint32_t i = 0; i < cmder.size(); i++)
    {
        auto app = CApp::create(cmder[i]);
        app->set_input_buffer(buffers[i]);
        app->set_output_buffer(buffers[i + 1]);
        rt.add_app(app);
    }
    rt.run();
}

void CShell::error(const std::string& str)
{
    std::cerr << str << std::endl;
}
