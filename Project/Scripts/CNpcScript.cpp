#include "pch.h"
#include "CNpcScript.h"

#include <Engine\CKeyManager.h>

CNpcScript::CNpcScript()
	: CScript(SCRIPT_TYPE::NPCSCRIPT)
{

}

CNpcScript::~CNpcScript()
{

}

void CNpcScript::Begin()
{

}

void CNpcScript::Tick()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec3 curPos = GetOwner()->Transform()->GetRelativePos();
		Vec2 mousePos = CKeyManager::GetInst()->GetMousePos();
		int a = 0;
	}
}

bool CNpcScript::IsClicked()
{
	Vec3 curPos = GetOwner()->Transform()->GetRelativePos();
	Vec2 mousePos = CKeyManager::GetInst()->GetMousePos();

	return mousePos.x >= curPos.x && mousePos.x <= curPos.x + 300.f &&
		mousePos.y >= curPos.y && mousePos.y <= curPos.y + 500.f;
}

void CNpcScript::SaveToLevelFile(FILE* file)
{

}

void CNpcScript::LoadFromLevelFile(FILE* file)
{

}