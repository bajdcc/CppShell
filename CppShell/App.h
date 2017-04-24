#ifndef _CAPP_H
#define _CAPP_H

enum app_t
{
    app__begin,
    app_none,
    app_pipe,
    app__end
};

class CApp
{
public:
    CApp();
    ~CApp();

    static std::shared_ptr<CApp> create(app_t type);
    static app_t get_type_by_name(const std::string &name);
};

#endif