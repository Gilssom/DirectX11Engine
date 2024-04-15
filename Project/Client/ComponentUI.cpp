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

	// Target �� ������ ��Ȱ��ȭ
	if (m_TargetObject == nullptr)
	{
		SetActive(false);
	}
	else
	{
		// Target �� �ڽ�(= UI)�� ��Ī�Ǵ� Component �� ������ ��Ȱ��ȭ
		if (m_TargetObject->GetComponent(m_Type) == nullptr)
		{
			SetActive(false);
		}
		// Target �� �ڽ�(= UI)�� ��Ī�Ǵ� Component �� ������ Ȱ��ȭ
		else
		{
			SetActive(true);
		}
	}
}