#pragma once

// 1. Script �����͸� �˾Ƶ�, ���� Script ���� Class Name �� �˾Ƴ� �� �ִ�.

// 2. ����(����)�� ��� Script List �� �˾Ƴ� �� �־�� �Ѵ�.

// 3. Script �� Class Name �����ε� Script ��ü�� ������ų �� �־�� �Ѵ�.

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