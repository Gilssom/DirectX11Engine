#include "pch.h"
#include "CGameObject.h"
#include "CComponent.h"
#include "CRenderComponent.h"
#include "CScript.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
}

void CGameObject::Begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if(m_arrCom[i] != nullptr)
			m_arrCom[i]->Begin();
	}

	for (size_t i = 0; i < m_vecScripts.size(); i++)
	{
		m_vecScripts[i]->Begin();
	}
}

void CGameObject::Tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (m_arrCom[i] != nullptr)
			m_arrCom[i]->Tick();
	}

	for (size_t i = 0; i < m_vecScripts.size(); i++)
	{
		m_vecScripts[i]->Tick();
	}
}

void CGameObject::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (m_arrCom[i] != nullptr)
			m_arrCom[i]->FinalTick();
	}
}

void CGameObject::Render()
{
	if (m_RenderCom)
	{
		m_RenderCom->Render();
	}
}

void CGameObject::AddComponent(CComponent* component)
{
	// �Է����� ���� ������Ʈ�� Ÿ���� Ȯ��
	COMPONENT_TYPE type = component->GetComponentType();

	// �Էµ� ������Ʈ�� Script ������ ���
	if (COMPONENT_TYPE::SCRIPT == type)
	{
		m_vecScripts.push_back((CScript*)component);
	}
	else
	{
		// ������Ʈ �ߺ� ����
		assert(!m_arrCom[(UINT)type]);

		// �Էµ� ������Ʈ�� ������ ���� ������Ʈ���� Ȯ�� ( �ٿ� ĳ�������� �ִ��� ������ Ȯ�� )
		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(component);

		if (pRenderCom != nullptr)
		{
			// �̹� ������ ���� ������Ʈ�� �����ϰ� �ִ�.
			assert(!m_RenderCom);

			m_RenderCom = pRenderCom;
		}

		// �Էµ� ������Ʈ�� �迭�� �˸��� �ε��� �ڸ��� �ּҰ��� ���
		m_arrCom[(UINT)type] = component;
	}

	// ������Ʈ�� �����ڸ� �ڽ����� ����
	component->m_Owner = this;
}
