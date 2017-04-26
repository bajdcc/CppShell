#include "stdafx.h"
#include "App.h"


int CAppNull::init()
{
    return 0;
}

bool CAppNull::available() const
{
    return false;
}

char CAppNull::next()
{
    return '\0';
}

// ----------------------------------------------

int CAppPipe::init()
{
    return 0;
}

bool CAppPipe::available() const
{
    return inner->available();
}

char CAppPipe::next()
{
    return inner->next();
}

// ----------------------------------------------

int CAppRange::init()
{
    if (args.size() == 1)
    {
        start = atoi(args[0].c_str());
        infinite = true;
    }
    else if (args.size() == 2)
    {
        start = atoi(args[0].c_str());
        end = atoi(args[1].c_str());
        infinite = false;
    }
    else if (args.size() == 0)
    {
        start = 1;
        infinite = true;
    }
    else
    {
        error = "invalid argument size";
        return -1;
    }
    return 0;
}

bool CAppRange::available() const
{
    return infinite ? true : (start <= end || !data.empty());
}

char CAppRange::next()
{
    if (data.empty())
    {
        if (!available())
            return '\0';
        char buf[50];
        _itoa_s(start, buf, 50, 10);
        for (auto c : std::string(buf))
            data.push(c);
        data.push('\n');
        start++;
    }
    auto ch = data.front();
    data.pop();
    return ch;
}

// ----------------------------------------------

int CAppTake::init()
{
    if (args.size() == 1)
    {
        start = 1;
        end = atoi(args[0].c_str());
    }
    else
    {
        error = "invalid argument size";
        return -1;
    }
    return 0;
}

bool CAppTake::available() const
{
    return start <= end || !data.empty();
}

char CAppTake::next()
{
    if (data.empty())
    {
        if (!available())
            return '\0';
        while (inner->available())
        {
            auto c = inner->next();
            data.push(c);
            if (c == '\n')
                break;
        }
        start++;
        if (data.empty())
            return '\0';
    }
    auto ch = data.front();
    data.pop();
    return ch;
}

// ----------------------------------------------

int CAppLast::init()
{
    if (args.size() == 1)
    {
        start = 1;
        end = atoi(args[0].c_str());
    }
    else
    {
        error = "invalid argument size";
        return -1;
    }
    return 0;
}

bool CAppLast::available() const
{
    return start <= end || !data.empty();
}

char CAppLast::next()
{
    if (data.empty())
    {
        if (!available())
            return '\0';
        std::queue<char> d;
        while (inner->available())
        {
            auto c = inner->next();
            d.push(c);
            if (c == '\n')
            {
                if ((int)data.size() >= end)
                    data.pop();
                data.push(d);
                std::queue<char>().swap(d);
            }
        }
        end = data.size();
        if (data.empty())
            return '\0';
    }
    auto d = data.front();
    if (d.empty())
    {
        start++;
        data.pop();
        if (data.empty())
            return  '\0';
        d = data.front();
    }
    auto c = d.front();
    data.front().pop();
    return c;
}

// ----------------------------------------------

int CAppLoad::init()
{
    if (args.size() == 1)
    {
        ifs.open(args[0]);
        if (!ifs.is_open())
        {
            error = "open file '" + args[0] + "' failed";
            return -2;
        }
    }
    else
    {
        error = "invalid argument size";
        return -1;
    }
    return 0;
}

bool CAppLoad::available() const
{
    return !ifs.eof();
}

char CAppLoad::next()
{
    if (!available())
        return '\0';
    auto c = ifs.get();
    if (c == -1)
        return '\0';
    return c;
}

// ----------------------------------------------

int CAppSave::init()
{
    if (args.size() == 1)
    {
        ofs.open(args[0]);
        if (!ofs.is_open())
        {
            error = "open file '" + args[0] + "' failed";
            return -2;
        }
    }
    else
    {
        error = "invalid argument size";
        return -1;
    }
    return 0;
}

bool CAppSave::available() const
{
    return inner->available();
}

char CAppSave::next()
{
    auto c = inner->next();
    if (c != '\0')
        ofs.put(c);
    return c;
}
