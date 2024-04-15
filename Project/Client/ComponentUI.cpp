#include "pch.h"
#include "ComponentUI.h"

ComponentUI::ComponentUI(const string& name, const  string& id, COMPONENT_TYPE type)
	: EditorUI(name, id)
	, m_Type(type)
	, m_TargetObject(nullptr)
{
}

ComponentUI::~ComponentUI()
{
}

void ComponentUI::SetTarget(CGameObject* target)
{
	m_TargetObject = target;

	// Target 이 없으면 비활성화
	if (m_TargetObject == nullptr)
	{
		SetActive(false);
	}
	else
	{
		// Target 이 자신(= UI)과 대칭되는 Component 가 없으면 비활성화
		if (m_TargetObject->GetComponent(m_Type) == nullptr)
		{
			SetActive(false);
		}
		// Target 이 자신(= UI)과 대칭되는 Component 가 있으면 활성화
		else
		{
			SetActive(true);
		}
	}
}