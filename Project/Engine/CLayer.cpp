#include "pch.h"
#include "CLayer.h"

#include "CGameObject.h"

CLayer::CLayer()
{

}

CLayer::~CLayer()
{
	Safe_Del_Vector(m_vecParent);
}

void CLayer::Init()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->Begin();
	}
}

void CLayer::Tick()
{
	for (size_t i = 0; i < m_vecParent.size(); i++)
	{
		m_vecParent[i]->Tick();
	}
}

void CLayer::FinalTick()
{
	for (size_t i = 0; i < m_vecParent.size(); i++)
	{
		m_vecParent[i]->FinalTick();
	}
}

void CLayer::AddObject(CGameObject* object)
{
	m_vecParent.push_back(object);
	object->m_LayerIdx = m_LayerIdx; // 들어온 Object Layer 번호 지정
}