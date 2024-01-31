#pragma once
#include "Singletone.h"
class CPathManager : public CSingleton<CPathManager>
{
    SINGLE(CPathManager)

private:
    wchar_t m_szContentPath[255];


public:
    void Init();
    const wchar_t* GetComtentPath() { return m_szContentPath; }
};

