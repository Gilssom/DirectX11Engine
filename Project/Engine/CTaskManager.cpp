#include "pch.h"
#include "CTaskManager.h"

#include "CLevelManager.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"
#include "CCollider2D.h"

CTaskManager::CTaskManager()
{

}

CTaskManager::~CTaskManager()
{

}

void CTaskManager::Tick()
{
	ClearDeadObject();

	for (size_t i = 0; i < m_vecTasks.size(); i++)
	{
		ExecuteTask(m_vecTasks[i]);
	}

	m_vecTasks.clear();
}

void CTaskManager::ClearDeadObject()
{
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}

	m_vecDead.clear();
}

void CTaskManager::ExecuteTask(tTask& task)
{
	// 다음번 프레임에 적용할 내용들
	switch (task.Type)
	{
		// Param_0 : LayerIndex
		// Param_1 : Object Adress
		case TASK_TYPE::SPAWN_OBJECT:
		{
			int LayerIdx = (int)task.dwParam_0;
			CGameObject* pSpawnObj = (CGameObject*)task.dwParam_1;
			CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(LayerIdx, pSpawnObj);

			// Play 상태의 레벨에 합류하는 오브젝트는 Begin 호출을 받는다.
			if (pCurLevel->GetState() == LEVEL_STATE::PLAY)
			{
				pSpawnObj->Begin();
			}
		}
		break;

		// Param_0 : Object Adress ( Dead )
		case TASK_TYPE::DESTROY_OBJECT:
		{
			CGameObject* pObject = (CGameObject*)task.dwParam_0;

			if (!pObject->IsDead())
			{
				pObject->m_Dead = true;
				m_vecDead.push_back(pObject);
			}
		}
		break;

		// Param_0 : Collider2D Adress ( Deactive )
		case TASK_TYPE::COLLIDER2D_SEMI_DEACTIVE:
		{
			CCollider2D* pCollider = (CCollider2D*)task.dwParam_0;
			pCollider->m_SemiDeactive = true;
		}
		break;

		// Param_0 : Collider2D Adress ( Deactive )
		case TASK_TYPE::COLLIDER2D_DEACTIVE:
		{
			CCollider2D* pCollider = (CCollider2D*)task.dwParam_0;
			pCollider->m_SemiDeactive = false;
			pCollider->m_Active = false;
		}
		break;

		// Param_0 : Level Adress
		// Param_1 : LEVEL_STATE
		case TASK_TYPE::CHANGE_LEVEL:
		{
			CLevel* pNextLevel = (CLevel*)task.dwParam_0;
			LEVEL_STATE NextLevelState = (LEVEL_STATE)task.dwParam_1;

			CLevelManager::GetInst()->ChangeLevel(pNextLevel);
			pNextLevel->ChangeState(NextLevelState);
		}
		break;
	}
}