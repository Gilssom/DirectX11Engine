#include "pch.h"
#include "CCollisionManager.h"

#include "CLevelManager.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CCollider2D.h"

CCollisionManager::CCollisionManager()
	: m_Matrix{}
{

}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::Tick()
{
	for (UINT Row = 0; Row < MAX_LAYER; ++Row)
	{
		for (UINT Col = Row; Col < MAX_LAYER; ++Col)
		{
			// 해당 칸 비트 체크 여부 판단
			if (m_Matrix[Row] & (1 << Col))
			{
				CollisionBtwLayer(Row, Col);
			}
		}
	}
}

void CCollisionManager::LayerCheck(UINT layerLeftIndex, UINT layerRightIndex)
{
	UINT Row = layerLeftIndex;
	UINT Col = layerRightIndex;

	// 행이 작은 값, 열이 큰 값으로
	if (Col < Row)
	{
		Row = layerRightIndex;
		Col = layerLeftIndex;
	}

	// 비트 연산자
	UINT CheckBit = (1 << Col);

	// 만약 해당 비트에 값이 있다면 ( Check Box On , Off 기능 )
	if (m_Matrix[Row] & CheckBit)
	{
		// 비트 빼기
		m_Matrix[Row] &= ~CheckBit;
	}
	else
	{
		// 비트 더하기
		m_Matrix[Row] |= CheckBit;
	}
}

void CCollisionManager::CollisionBtwLayer(UINT left, UINT right)
{
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();

	CLayer* pLeftLayer = pCurLevel->GetLayer(left);
	CLayer* pRightLayer = pCurLevel->GetLayer(right);

	const vector<CGameObject*>& vecLeft = pLeftLayer->GetObjects();
	const vector<CGameObject*>& vecRight = pRightLayer->GetObjects();

	// 현재 같은 Layer 인 경우에 대한 처리가 하나도 안되어 있음 (24. 02. 26)
	// 중복 충돌 상황 발생
	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (vecLeft[i]->Collider2D() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			if (vecRight[j]->Collider2D() == nullptr)
				continue;

			CollisionBtwCollider2D(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D());
		}
	}
}

void CCollisionManager::CollisionBtwCollider2D(CCollider2D* leftCol, CCollider2D* rightCol)
{
	COL_ID id;
	id.LeftID = leftCol->GetID();
	id.RightID = rightCol->GetID();

	map<LONGLONG, bool>::iterator iter = m_ColInfo.find(id.ID);

	// 두 ID 를 가진 서로의 객체가 충돌한 적이 없다.
	if (iter == m_ColInfo.end())
	{
		m_ColInfo.insert(make_pair(id.ID, false));
	}

	// 두 객체가 겹쳐있다. 
	if (IsCollision(leftCol, rightCol))
	{
		if (iter->second)
		{
			// Overlap (Stay)
			leftCol->Overlap(rightCol);
			rightCol->Overlap(leftCol);
		}
		else
		{
			// Begin Overlap (Enter)
			leftCol->BeginOverlap(rightCol);
			rightCol->BeginOverlap(leftCol);
		}

		iter->second = true;
	}
	// 두 객체가 겹쳐있지 않다.
	else
	{	
		if (iter->second)
		{
			// 이전에는 충돌 중 이었다. End Overlap (Exit)
			leftCol->EndOverlap(rightCol);
			rightCol->EndOverlap(leftCol);
		}

		iter->second = false;
	}
}

bool CCollisionManager::IsCollision(CCollider2D* leftCol, CCollider2D* rightCol)
{
	// OBB : 사각형 물리 충돌

	return false;
}
