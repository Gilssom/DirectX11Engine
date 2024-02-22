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
			// 해당 칸 비트 체크 여부 판단
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