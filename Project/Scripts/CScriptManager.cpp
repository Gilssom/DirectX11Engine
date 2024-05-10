#include "pch.h"
#include "CScriptManager.h"

#include "CBackGroundScript.h"
#include "CCameraMoveScript.h"
#include "CMissileScript.h"
#include "CPlayerScript.h"
#include "CTestScript.h"

void CScriptManager::GetScriptInfo(vector<wstring>& vec)
{
	vec.push_back(L"CBackGroundScript");
	vec.push_back(L"CCameraMoveScript");
	vec.push_back(L"CMissileScript");
	vec.push_back(L"CPlayerScript");
	vec.push_back(L"CTestScript");
}

CScript* CScriptManager::GetScript(const wstring& strScriptName)
{
	if (L"CBackGroundScript" == strScriptName)
		return new CBackGroundScript;
	if (L"CCameraMoveScript" == strScriptName)
		return new CCameraMoveScript;
	if (L"CMissileScript" == strScriptName)
		return new CMissileScript;
	if (L"CPlayerScript" == strScriptName)
		return new CPlayerScript;
	if (L"CTestScript" == strScriptName)
		return new CTestScript;
	return nullptr;
}

CScript* CScriptManager::GetScript(UINT scriptType)
{
	switch (scriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackGroundScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::TESTSCRIPT:
		return new CTestScript;
		break;
	}
	return nullptr;
}

const wchar_t* CScriptManager::GetScriptName(CScript* pScript)
{
	switch ((SCRIPT_TYPE)pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackGroundScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"CTestScript";
		break;

	}
	return nullptr;
}