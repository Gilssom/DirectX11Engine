#include "pch.h"
#include "CScriptManager.h"

#include "CBackGroundScript.h"
#include "CCameraMoveScript.h"
#include "CMissileScript.h"
#include "CPlayerScript.h"

void CScriptManager::GetScriptsName(vector<string>& vecNames)
{
	// 구현(제작)한 모든 Script List 를 알아낼 수 있어야 한다.

	vecNames.push_back("CBackGroundScript");
	vecNames.push_back("CCameraMoveScript");
	vecNames.push_back("CMissileScript");
	vecNames.push_back("CPlayerScript");
}

string CScriptManager::GetScriptName(CScript* script)
{
	// Script 포인터만 알아도, 무슨 Script 인지 Class Name 을 알아낼 수 있다.
	// Script 만의 최종 고유한 값이 필요하다.

	SCRIPT_TYPE type = (SCRIPT_TYPE)script->GetScriptType();

	switch (type)
	{
	case BACKGROUND:
		return "CBackGroundScript";
	case CAMERAMOVE:
		return "CCameraMoveScript";
	case MISSILE:
		return "CMissileScript";
	case PLAYER:
		return "CPlayerScript";
	}

	return string();
}

CScript* CScriptManager::GetScript(const string& scriptName)
{
	// Script 의 Class Name 만으로도 Script 객체를 생성시킬 수 있어야 한다.

	if (scriptName == "CBackGroundSciprt")
		return new CBackGroundScript;

	if (scriptName == "CCameraMoveScript")
		return new CCameraMoveScript;

	if (scriptName == "CMissileScript")
		return new CMissileScript;

	if (scriptName == "CPlayerScript")
		return new CPlayerScript;

	return nullptr;
}
