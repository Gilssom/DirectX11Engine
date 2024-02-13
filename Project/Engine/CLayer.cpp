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

<<<<<<< Updated upstream
void CLayer::Begin()
{
	for (size_t i = 0; i < m_vecObjects.size(); i++)
=======
<<<<<<< HEAD
void CLayer::Init()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
=======
void CLayer::Begin()
{
	for (size_t i = 0; i < m_vecObjects.size(); i++)
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
	{
		m_vecObjects[i]->Begin();
	}
}

void CLayer::Tick()
{
<<<<<<< Updated upstream
	for (size_t i = 0; i < m_vecObjects.size(); i++)
=======
<<<<<<< HEAD
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
=======
	for (size_t i = 0; i < m_vecObjects.size(); i++)
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
	{
		m_vecObjects[i]->Tick();
	}
}

void CLayer::FinalTick()
{
<<<<<<< Updated upstream
	for (size_t i = 0; i < m_vecObjects.size(); i++)
=======
<<<<<<< HEAD
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
=======
	for (size_t i = 0; i < m_vecObjects.size(); i++)
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
	{
		m_vecObjects[i]->FinalTick();
	}
}

void CLayer::Render()
{
<<<<<<< Updated upstream
	for (size_t i = 0; i < m_vecObjects.size(); i++)
=======
<<<<<<< HEAD
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
=======
	for (size_t i = 0; i < m_vecObjects.size(); i++)
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
	{
		m_vecObjects[i]->Render();
	}
}
