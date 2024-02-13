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

<<<<<<< Updated upstream
=======
<<<<<<< HEAD
void CLevel::Init()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->Init();
=======
>>>>>>> Stashed changes
void CLevel::Begin()
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		m_arrLayer[i]->Begin();
<<<<<<< Updated upstream
=======
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
	}
}

void CLevel::Tick()
{
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->Tick();
	}
=======
>>>>>>> Stashed changes
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		m_arrLayer[i]->Tick();
	}

>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
}

void CLevel::FinalTick()
{
<<<<<<< Updated upstream
	for (UINT i = 0; i < MAX_LAYER; i++)
=======
<<<<<<< HEAD
	for (UINT i = 0; i < MAX_LAYER; ++i)
=======
	for (UINT i = 0; i < MAX_LAYER; i++)
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
	{
		m_arrLayer[i]->FinalTick();
	}
}

void CLevel::Render()
{
<<<<<<< Updated upstream
	for (UINT i = 0; i < MAX_LAYER; i++)
=======
<<<<<<< HEAD
	for (UINT i = 0; i < MAX_LAYER; ++i)
=======
	for (UINT i = 0; i < MAX_LAYER; i++)
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
	{
		m_arrLayer[i]->Render();
	}
}

void CLevel::AddObject(UINT layerIdx, CGameObject* object)
{
	m_arrLayer[layerIdx]->AddObject(object);
}