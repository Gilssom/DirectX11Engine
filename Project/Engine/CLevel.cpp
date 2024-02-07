#include "pch.h"
#include "CLevel.h"

#include "CLayer.h"

CLevel::CLevel()
	: m_arrLayer{}
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		m_arrLayer[i] = new CLayer;
	}
}

CLevel::~CLevel()
{
	Safe_Del_Array(m_arrLayer);
}

void CLevel::AddObject(UINT layerIdx, CGameObject* object)
{
	m_arrLayer[layerIdx]->AddObject(object);
}

void CLevel::Init()
{

}

void CLevel::Tick()
{

}

void CLevel::FinalTick()
{

}

void CLevel::Render()
{

}