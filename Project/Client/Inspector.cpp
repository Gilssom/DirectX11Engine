#include "pch.h"
#include "Inspector.h"

#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>
#include <Engine\\CGameObject.h>
#include <Engine\\CTransform.h>

#include "ComponentUI.h"
#include "TransformUI.h"
#include "MeshRenderUI.h"

Inspector::Inspector()
	: EditorUI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
	, m_arrComUI{}
{
	// Transform UI ����
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]);

	// Mesh Render UI ����
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER] = new MeshRenderUI;
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]);
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
			CGameObject* pTarget = pLevel->FindObjectByName(L"TileMap");

			if (pTarget != nullptr)
			{
				SetTargetObject(pTarget);
			}
		}

		return;
	}

	ImGui::Text("Inspector");
}

void Inspector::SetTargetObject(CGameObject* target)
{
	m_TargetObject = target;

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		// �ش� ������Ʈ�� ����� UI �� �����Ǿ����� �ʱ� ������ nullptr üũ ���־�� ��.
		if (m_arrComUI[i] == nullptr)
			continue;

		m_arrComUI[i]->SetTarget(m_TargetObject);
	}
}