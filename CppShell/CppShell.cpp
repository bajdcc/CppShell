// CppShell.cpp : �������̨Ӧ�ó������ڵ㡣
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

