// CppShell.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Shell.h"


int main()
{
    for(;;)
    {
        std::cout << "$ ";
        std::string line;
        std::getline(std::cin, line);
        if (line == "exit")
            break;
        CShell::exec(line);
    }

    return 0;
}

