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
