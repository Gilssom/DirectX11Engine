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
		// Level 이 Play 상태가 아니라면 Tick 은 호출 금지
		if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
		{
			m_CurLevel->Tick();
		}

		// Level 이 정지되더라도 Editor 에서도 볼 수 있어야 한다.
		// Final Tick 은 Rendering 을 진행하는 과정이기 때문에 남겨둔다.
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