#include "pch.h"
#include "CScriptManager.h"

#include "CBackGroundScript.h"
#include "CCameraMoveScript.h"
#include "CMissileScript.h"
#include "CPlayerScript.h"

void CScriptManager::GetScriptsName(vector<string>& vecNames)
{
	// ����(����)�� ��� Script List �� �˾Ƴ� �� �־�� �Ѵ�.

	vecNames.push_back("CBackGroundScript");
	vecNames.push_back("CCameraMoveScript");
	vecNames.push_back("CMissileScript");
	vecNames.push_back("CPlayerScript");
}

string CScriptManager::GetScriptName(CScript* script)
{
	// Script �����͸� �˾Ƶ�, ���� Script ���� Class Name �� �˾Ƴ� �� �ִ�.
	// Script ���� ���� ������ ���� �ʿ��ϴ�.

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
	// Script �� Class Name �����ε� Script ��ü�� ������ų �� �־�� �Ѵ�.

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
