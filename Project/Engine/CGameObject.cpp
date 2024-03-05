#include "pch.h"
#include "CGameObject.h"

#include "CLevelManager.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CComponent.h"
#include "CRenderComponent.h"
#include "CScript.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
	Safe_Del_Vector(m_vecScripts);
	Safe_Del_Vector(m_vecChild);
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

	// �ڽ� ������Ʈ Begin ȣ��
	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Begin();
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

	// �ڽ� ������Ʈ Tick ȣ��
	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Tick();
	}
}

void CGameObject::FinalTick()
{
	// Component Final Tick ȣ��
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (m_arrCom[i] != nullptr)
			m_arrCom[i]->FinalTick();
	}

	// �ҼӵǾ� �ִ� Layer�� �ڱ� �ڽ��� ���
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(m_LayerIdx);
	pLayer->RegisterObject(this);

	// �ڽ� ������Ʈ Final Tick ȣ��
	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->FinalTick();
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

void CGameObject::AddChild(CGameObject* object)
{
	// ���� ������Ʈ�� "�ڽ�" ���� ���� , �ڽ��� �θ� ������Ʈ�� "�ڽ�" ���� ����
	object->m_Parent = this;
	m_vecChild.push_back(object);
}