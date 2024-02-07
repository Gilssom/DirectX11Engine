#include "pch.h"
#include "CLayer.h"

#include "CGameObject.h"

CLayer::CLayer()
{

}

CLayer::~CLayer()
{
	Safe_Del_Vector(m_vecObjects);
}

void CLayer::Begin()
{
	for (size_t i = 0; i < m_vecObjects.size(); i++)
	{
		m_vecObjects[i]->Begin();
	}
}

void CLayer::Tick()
{
	for (size_t i = 0; i < m_vecObjects.size(); i++)
	{
		m_vecObjects[i]->Tick();
	}
}

void CLayer::FinalTick()
{
	for (size_t i = 0; i < m_vecObjects.size(); i++)
	{
		m_vecObjects[i]->FinalTick();
	}
}

void CLayer::Render()
{
	for (size_t i = 0; i < m_vecObjects.size(); i++)
	{
		m_vecObjects[i]->Render();
	}
}
