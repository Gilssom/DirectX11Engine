#include "pch.h"
#include "CCollisionManager.h"

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
				int a = 0;
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