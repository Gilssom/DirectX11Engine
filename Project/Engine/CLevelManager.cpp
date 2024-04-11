#include "pch.h"
#include "CLevelManager.h"
#include "CAssetManager.h"

#include "CLevel.h"
#include "CLayer.h"

CLevelManager::CLevelManager()
	: m_CurLevel(nullptr)
{

}

CLevelManager::~CLevelManager()
{
	if (m_CurLevel != nullptr)
	{
		delete m_CurLevel;
	}
}

void CLevelManager::Init()
{
	
}

void CLevelManager::Tick()
{
	if (m_CurLevel != nullptr)
	{
		// Level �� Play ���°� �ƴ϶�� Tick �� ȣ�� ����
		if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
		{
			m_CurLevel->Tick();
		}

		// Level �� �����Ǵ��� Editor ������ �� �� �־�� �Ѵ�.
		// Final Tick �� Rendering �� �����ϴ� �����̱� ������ ���ܵд�.
		m_CurLevel->RegisterClear();
		m_CurLevel->FinalTick();
	}
}

void CLevelManager::ChangeLevel(CLevel* nextLevel)
{
	if (m_CurLevel != nullptr)
	{
		delete m_CurLevel;
		m_CurLevel = nullptr;
	}

	m_CurLevel = nextLevel;
}