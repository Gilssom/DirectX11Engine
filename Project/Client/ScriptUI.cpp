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

// 구현하기 위해 필요한 기능들

// 1. Script 포인터만 알아도, 무슨 Script 인지 Class Name 을 알아낼 수 있다.

// 2. 구현(제작)한 모든 Script List 를 알아낼 수 있어야 한다.

// 3. Script 의 Class Name 만으로도 Script 객체를 생성시킬 수 있어야 한다.

// 즉, Script 의 자동화 기능이 무조건적으로 필요함.