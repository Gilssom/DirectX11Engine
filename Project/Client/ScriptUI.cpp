#include "pch.h"
#include "ScriptUI.h"

ScriptUI::ScriptUI()
	: ComponentUI("Script", "##ScriptUI", COMPONENT_TYPE::SCRIPT)
{
	SIZE;
}

ScriptUI::~ScriptUI()
{

}

void ScriptUI::Render_Tick()
{
	Render_Title();
}

// �����ϱ� ���� �ʿ��� ��ɵ�

// 1. Script �����͸� �˾Ƶ�, ���� Script ���� Class Name �� �˾Ƴ� �� �ִ�.

// 2. ����(����)�� ��� Script List �� �˾Ƴ� �� �־�� �Ѵ�.

// 3. Script �� Class Name �����ε� Script ��ü�� ������ų �� �־�� �Ѵ�.

// ��, Script �� �ڵ�ȭ ����� ������������ �ʿ���.