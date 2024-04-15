#include "pch.h"
#include "Inspector.h"

#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>
#include <Engine\\CGameObject.h>
#include <Engine\\CTransform.h>

Inspector::Inspector()
	: EditorUI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
{

}

Inspector::~Inspector()
{

}

void Inspector::Render_Tick()
{
	if (m_TargetObject == nullptr)
	{
		CLevel* pLevel = CLevelManager::GetInst()->GetCurrentLevel();

		if (pLevel != nullptr)
		{
			CGameObject* pTarget = pLevel->FindObjectByName(L"Player");

			if (pTarget != nullptr)
			{
				SetTargetObject(pTarget);
			}
		}

		return;
	}

	Vec3 vPos =  m_TargetObject->Transform()->GetRelativePos();
	Vec3 vScale = m_TargetObject->Transform()->GetRelativeScale ();
	Vec3 vRotation = m_TargetObject->Transform()->GetRelativeRotation();

	ImGui::InputFloat3("Position", vPos);
	ImGui::InputFloat3("Scale", vScale);
	ImGui::InputFloat3("Rotation", vRotation);
}

void Inspector::SetTargetObject(CGameObject* target)
{
	m_TargetObject = target;
}