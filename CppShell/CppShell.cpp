// CppShell.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Shell.h"


int main()
{
    CShell shell;
    for(;;)
    {
        std::cout << "$ ";
        std::string line;
        std::getline(std::cin, line);
        if (line == "exit")
            break;
        shell.exec(line);
    }

    return 0;
}

