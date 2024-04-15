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
	// Transform UI 생성
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]);

	// Mesh Render UI 생성
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
		// 해당 컴포넌트를 담당할 UI 가 생성되어있지 않기 때문에 nullptr 체크 해주어야 함.
		if (m_arrComUI[i] == nullptr)
			continue;

		m_arrComUI[i]->SetTarget(m_TargetObject);
	}
}