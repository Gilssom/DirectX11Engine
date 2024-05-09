#pragma once

// 1. Script 포인터만 알아도, 무슨 Script 인지 Class Name 을 알아낼 수 있다.

// 2. 구현(제작)한 모든 Script List 를 알아낼 수 있어야 한다.

// 3. Script 의 Class Name 만으로도 Script 객체를 생성시킬 수 있어야 한다.

enum SCRIPT_TYPE
{
	BACKGROUND,
	CAMERAMOVE,
	MISSILE,
	PLAYER,
};

class CScript;

class CScriptManager
{
public:
	static void GetScriptsName(vector<string>& vecNames);

	static string GetScriptName(CScript* script);

	static CScript* GetScript(const string& scriptName);
};