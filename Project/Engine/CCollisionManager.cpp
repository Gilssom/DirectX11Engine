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
			// �ش� ĭ ��Ʈ üũ ���� �Ǵ�
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

	// ���� ���� ��, ���� ū ������
	if (Col < Row)
	{
		Row = layerRightIndex;
		Col = layerLeftIndex;
	}

	// ��Ʈ ������
	UINT CheckBit = (1 << Col);

	// ���� �ش� ��Ʈ�� ���� �ִٸ� ( Check Box On , Off ��� )
	if (m_Matrix[Row] & CheckBit)
	{
		// ��Ʈ ����
		m_Matrix[Row] &= ~CheckBit;
	}
	else
	{
		// ��Ʈ ���ϱ�
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

	// ���� ���� Layer �� ��쿡 ���� ó���� �ϳ��� �ȵǾ� ���� (24. 02. 26)
	// �ߺ� �浹 ��Ȳ �߻�
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

	// �� ID �� ���� ������ ��ü�� �浹�� ���� ����.
	if (iter == m_ColInfo.end())
	{
		m_ColInfo.insert(make_pair(id.ID, false));
	}

	// �� ��ü�� �����ִ�. 
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
	// �� ��ü�� �������� �ʴ�.
	else
	{	
		if (iter->second)
		{
			// �������� �浹 �� �̾���. End Overlap (Exit)
			leftCol->EndOverlap(rightCol);
			rightCol->EndOverlap(leftCol);
		}

		iter->second = false;
	}
}

bool CCollisionManager::IsCollision(CCollider2D* leftCol, CCollider2D* rightCol)
{
	// OBB : �簢�� ���� �浹

	return false;
}
