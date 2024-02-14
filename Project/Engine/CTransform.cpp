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
	/*matScale._11 = m_RelativeScale.x;
	matScale._22 = m_RelativeScale.y;
	matScale._33 = m_RelativeScale.z;*/

	Matrix matRot =  XMMatrixRotationX(m_RelativeRotation.x);
		   matRot *= XMMatrixRotationY(m_RelativeRotation.y);
		   matRot *= XMMatrixRotationZ(m_RelativeRotation.z);
	//matZRot._11 = cosf(m_RelativeRotation.z);	matZRot._12 = sinf(m_RelativeRotation.z);
	//matZRot._21 = -sinf(m_RelativeRotation.z);	matZRot._22 = cosf(m_RelativeRotation.z);

	Matrix matTranslation = XMMatrixTranslation(m_RelativePos.x, m_RelativePos.y, m_RelativePos.z);
	/*matTranslation._41 = m_RelativePos.x;
	matTranslation._42 = m_RelativePos.y;
	matTranslation._43 = m_RelativePos.z;*/

	m_matWorld = matScale * matRot * matTranslation;
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
