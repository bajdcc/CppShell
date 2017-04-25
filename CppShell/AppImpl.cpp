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