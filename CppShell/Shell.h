#ifndef _CSHELL_H
#define _CSHELL_H

class CShell
{
public:
    CShell();
    ~CShell();

    static void exec(const std::string& cmd);

private:
    static void error(const std::string& str);
};

#endif