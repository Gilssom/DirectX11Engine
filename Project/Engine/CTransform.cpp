#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_RelativeScale(Vec3(1.f, 1.f, 1.f))
{

}

CTransform::~CTransform()
{

}

void CTransform::FinalTick()
{
	m_matWorld = XMMatrixIdentity();

	// 크기 -> 회전 -> 이동 서순으로 계산해야 함

	// 4차원 행렬 사용
	// 회전 각도와 크기, 이동을 한꺼번에 하기 위해 행렬을 3개 만들어 놓고 미리 곱연산을 해버린다.
	Matrix matScale = XMMatrixScaling(m_RelativeScale.x, m_RelativeScale.y, m_RelativeScale.z); // 행렬 계산 함수 지원

	Matrix matRot =  XMMatrixRotationX(m_RelativeRotation.x);
		   matRot *= XMMatrixRotationY(m_RelativeRotation.y);
		   matRot *= XMMatrixRotationZ(m_RelativeRotation.z);

	Matrix matTranslation = XMMatrixTranslation(m_RelativePos.x, m_RelativePos.y, m_RelativePos.z);

	m_matWorld = matScale * matRot * matTranslation;

	
	// 오브젝트의 방향 정보 계산
	m_RelativeDir[(UINT)DIR_TYPE::RIGHT]	= XAxis;
	m_RelativeDir[(UINT)DIR_TYPE::UP]		= YAxis;
	m_RelativeDir[(UINT)DIR_TYPE::FRONT]	= ZAxis;

	for (int i = 0; i < 3; i++)
	{
		// 회전 행렬의 4차 좌표에는 정보가 없기 때문에 1도 해도 되지만		( Coord )
		// 월드 행렬은 모든 좌표를 가지고 있기 때문에 0으로 해주어야 한다.	( Normal )
		m_RelativeDir[i] = XMVector3TransformNormal(m_RelativeDir[i], matRot);
		m_RelativeDir[i].Normalize();
	}
}

void CTransform::Binding()
{
	// 데이터 GPU 로 보내기
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	// 자신을 찍고있는 Camera 의 View 행렬 정보가 온다.
	g_Trans.matWorld = m_matWorld;

	pCB->SetData(&g_Trans);
	pCB->Binding();
}
