#pragma once
#include "Singletone.h"

class CPathManager : public CSingleton<CPathManager>
{
    SINGLE(CPathManager)

private:
    wchar_t m_szContentPath[255];

public:
    void Init();
    const wchar_t* GetContentPath() { return m_szContentPath; }
    const wstring GetRelativePath(const wstring& absolutePath); // 절대경로 - 상대경로 추출
};