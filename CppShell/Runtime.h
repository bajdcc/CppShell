#ifndef _CRUNTIME_H
#define _CRUNTIME_H
#include "App.h"
#include <memory>

class CRuntime
{
public:
    CRuntime();
    ~CRuntime();

    void add_app(std::shared_ptr<CApp> app);
    void run();

private:
    std::vector<std::shared_ptr<CApp>> apps;
};

#endif