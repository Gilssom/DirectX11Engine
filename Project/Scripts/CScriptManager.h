#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	BACKGROUNDSCRIPT,
	BOSSSCRIPT,
	CAMERAMOVESCRIPT,
	DAMAGESCRIPT,
	GATESCRIPT,
	GOBLINSCRIPT,
	LIGHTONSCRIPT,
	MISSILESCRIPT,
	NPCSCRIPT,
	OBJECTSCRIPT,
	PLAYERSCRIPT,
	PLAYERSKILLSCRIPT,
	TAUSCRIPT,
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
};
