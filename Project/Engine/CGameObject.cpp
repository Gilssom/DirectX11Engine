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

	// 자식 오브젝트 Begin 호출
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

	// 자식 오브젝트 Tick 호출
	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Tick();
	}
}

void CGameObject::FinalTick()
{
	// Component Final Tick 호출
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (m_arrCom[i] != nullptr)
			m_arrCom[i]->FinalTick();
	}

	// 소속되어 있는 Layer에 자기 자신을 등록
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(m_LayerIdx);
	pLayer->RegisterObject(this);

	// 자식 오브젝트 Final Tick 호출
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
	// 입력으로 들어온 컴포넌트의 타입을 확인
	COMPONENT_TYPE type = component->GetComponentType();

	// 입력된 컴포넌트가 Script 종류인 경우
	if (COMPONENT_TYPE::SCRIPT == type)
	{
		m_vecScripts.push_back((CScript*)component);
	}
	else
	{
		// 컴포넌트 중복 방지
		assert(!m_arrCom[(UINT)type]);

		// 입력된 컴포넌트가 렌더링 관련 컴포넌트인지 확인 ( 다운 캐스팅으로 있는지 없는지 확인 )
		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(component);

		if (pRenderCom != nullptr)
		{
			// 이미 렌더링 관련 컴포넌트를 보유하고 있다.
			assert(!m_RenderCom);

			m_RenderCom = pRenderCom;
		}

		// 입력된 컴포넌트를 배열의 알맞은 인덱스 자리에 주소값을 기록
		m_arrCom[(UINT)type] = component;
	}

	// 컴포넌트의 소유자를 자신으로 지정
	component->m_Owner = this;
}

void CGameObject::AddChild(CGameObject* object)
{
	// 받은 오브젝트를 "자식" 으로 설정 , 자식의 부모 오브젝트를 "자신" 으로 설정
	object->m_Parent = this;
	m_vecChild.push_back(object);
}