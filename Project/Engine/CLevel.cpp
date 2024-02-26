#include "pch.h"
#include "CLevel.h"

#include "CLayer.h"

CLevel::CLevel()
	: m_arrLayer{}
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		m_arrLayer[i] = new CLayer;
		m_arrLayer[i]->m_LayerIdx = i;
	}
}

CLevel::~CLevel()
{
	Safe_Del_Array(m_arrLayer);
}

void CLevel::Init()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->Init();
	}
}

void CLevel::Tick()
{
	// 이전 프레임에 등록된 Object 들을 모두 제거
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->Clear();
	}

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->Tick();
	}
}

void CLevel::FinalTick()
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		m_arrLayer[i]->FinalTick();
	}
}

void CLevel::AddObject(UINT layerIdx, CGameObject* object, bool childMove)
{
	m_arrLayer[layerIdx]->AddObject(object, childMove);
}