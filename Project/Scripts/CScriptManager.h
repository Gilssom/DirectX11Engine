#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	BACKGROUNDSCRIPT,
	CAMERAMOVESCRIPT,
	MISSILESCRIPT,
	PLAYERSCRIPT,
	TESTSCRIPT,
};

using namespace std;

class CScript;

class CScriptManager
{
public:
	static void GetScriptInfo(vector<wstring>& vec);
	static CScript* GetScript(const wstring& strScriptName);
	static CScript* GetScript(UINT scriptType);
	static const wchar_t* GetScriptName(CScript* pScript);

public:
	static int m_LevelCount;
};
