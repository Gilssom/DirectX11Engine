#include "pch.h"
#include "CGateScript.h"

CGateScript::CGateScript()
	: CScript(SCRIPT_TYPE::GATESCRIPT)
	, m_GateCollider(nullptr)
	, m_MonsterCount(0)
	, m_IsClear(false)
{
	AddScriptProperty(PROPERTY_TYPE::INT, "Monster Count", &m_MonsterCount);
}

CGateScript::~CGateScript()
{

}

void CGateScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_1, 0);
	m_GateCollider = GetOwner()->Collider2D();
	m_GateCollider->Deactivate();
}

void CGateScript::Tick()
{
	if (m_MonsterCount <= 0 && !m_IsClear)
	{
		PlaySoundEffect(L"Sound\\hk1_good.ogg", 0.7f);
		GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_1, 1);
		m_GateCollider->Activate();
		m_IsClear = true;
	}
}

void CGateScript::SaveToLevelFile(FILE* file)
{
	fwrite(&m_MonsterCount, sizeof(int), 1, file);
}

void CGateScript::LoadFromLevelFile(FILE* file)
{
	fread(&m_MonsterCount, sizeof(int), 1, file);
}