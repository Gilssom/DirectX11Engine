#include "pch.h"
#include "CScriptManager.h"

#include "CBackGroundScript.h"
#include "CBossScript.h"
#include "CCameraMoveScript.h"
#include "CDamageScript.h"
#include "CGateScript.h"
#include "CGoblinScript.h"
#include "CLightOnScript.h"
#include "CMissileScript.h"
#include "CNpcScript.h"
#include "CObjectScript.h"
#include "CPlayerScript.h"
#include "CPlayerSkillScript.h"
#include "CTauScript.h"
#include "CTestScript.h"

void CScriptManager::GetScriptInfo(vector<wstring>& vec)
{
	vec.push_back(L"CBackGroundScript");
	vec.push_back(L"CBossScript");
	vec.push_back(L"CCameraMoveScript");
	vec.push_back(L"CDamageScript");
	vec.push_back(L"CGateScript");
	vec.push_back(L"CGoblinScript");
	vec.push_back(L"CLightOnScript");
	vec.push_back(L"CMissileScript");
	vec.push_back(L"CNpcScript");
	vec.push_back(L"CObjectScript");
	vec.push_back(L"CPlayerScript");
	vec.push_back(L"CPlayerSkillScript");
	vec.push_back(L"CTauScript");
	vec.push_back(L"CTestScript");
}

CScript* CScriptManager::GetScript(const wstring& strScriptName)
{
	if (L"CBackGroundScript" == strScriptName)
		return new CBackGroundScript;
	if (L"CBossScript" == strScriptName)
		return new CBossScript;
	if (L"CCameraMoveScript" == strScriptName)
		return new CCameraMoveScript;
	if (L"CDamageScript" == strScriptName)
		return new CDamageScript;
	if (L"CGateScript" == strScriptName)
		return new CGateScript;
	if (L"CGoblinScript" == strScriptName)
		return new CGoblinScript;
	if (L"CLightOnScript" == strScriptName)
		return new CLightOnScript;
	if (L"CMissileScript" == strScriptName)
		return new CMissileScript;
	if (L"CNpcScript" == strScriptName)
		return new CNpcScript;
	if (L"CObjectScript" == strScriptName)
		return new CObjectScript;
	if (L"CPlayerScript" == strScriptName)
		return new CPlayerScript;
	if (L"CPlayerSkillScript" == strScriptName)
		return new CPlayerSkillScript;
	if (L"CTauScript" == strScriptName)
		return new CTauScript;
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
	case (UINT)SCRIPT_TYPE::BOSSSCRIPT:
		return new CBossScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::DAMAGESCRIPT:
		return new CDamageScript;
		break;
	case (UINT)SCRIPT_TYPE::GATESCRIPT:
		return new CGateScript;
		break;
	case (UINT)SCRIPT_TYPE::GOBLINSCRIPT:
		return new CGoblinScript;
		break;
	case (UINT)SCRIPT_TYPE::LIGHTONSCRIPT:
		return new CLightOnScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::NPCSCRIPT:
		return new CNpcScript;
		break;
	case (UINT)SCRIPT_TYPE::OBJECTSCRIPT:
		return new CObjectScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSKILLSCRIPT:
		return new CPlayerSkillScript;
		break;
	case (UINT)SCRIPT_TYPE::TAUSCRIPT:
		return new CTauScript;
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

	case SCRIPT_TYPE::BOSSSCRIPT:
		return L"CBossScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::DAMAGESCRIPT:
		return L"CDamageScript";
		break;

	case SCRIPT_TYPE::GATESCRIPT:
		return L"CGateScript";
		break;

	case SCRIPT_TYPE::GOBLINSCRIPT:
		return L"CGoblinScript";
		break;

	case SCRIPT_TYPE::LIGHTONSCRIPT:
		return L"CLightOnScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::NPCSCRIPT:
		return L"CNpcScript";
		break;

	case SCRIPT_TYPE::OBJECTSCRIPT:
		return L"CObjectScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::PLAYERSKILLSCRIPT:
		return L"CPlayerSkillScript";
		break;

	case SCRIPT_TYPE::TAUSCRIPT:
		return L"CTauScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"CTestScript";
		break;

	}
	return nullptr;
}