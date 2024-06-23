#include "pch.h"
#include "CObjectScript.h"

CObjectScript::CObjectScript()
	: CScript(SCRIPT_TYPE::OBJECTSCRIPT)
	, m_Health(5)
{
	AddScriptProperty(PROPERTY_TYPE::INT, "Health", &m_Health);
}

CObjectScript::~CObjectScript()
{

}

void CObjectScript::Begin()
{

}

void CObjectScript::Tick()
{
	if (m_Health == 0)
	{
		GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_1, 1);
	}
}

void CObjectScript::BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (m_Health <= 0)
		return;

	if (otherObject->GetName() == L"Attack Area_0" || otherObject->GetName() == L"Attack Area_1" || otherObject->GetName() == L"Attack Area_2")
	{
		m_Health--;
		PlaySoundEffect(L"Sound\\cross_hit_04.ogg");
	}

}

void CObjectScript::Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}

void CObjectScript::EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}