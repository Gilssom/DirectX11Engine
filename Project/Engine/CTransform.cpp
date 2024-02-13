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

	// 4차원 행렬 사용
	// 회전 각도와 크기, 이동을 한꺼번에 하기 위해 행렬을 3개 만들어 놓고 미리 곱연산을 해버린다.
	Matrix matScale = XMMatrixIdentity();
	matScale._11 = m_RelativeScale.x;
	matScale._22 = m_RelativeScale.y;
	matScale._33 = m_RelativeScale.z;

	Matrix matZRot = XMMatrixIdentity();
	matZRot._11 = cosf(m_RelativeRotation.z);	matZRot._12 = sinf(m_RelativeRotation.z);
	matZRot._21 = -sinf(m_RelativeRotation.z);	matZRot._22 = cosf(m_RelativeRotation.z);

	Matrix matTranslation = XMMatrixIdentity();
	matTranslation._41 = m_RelativePos.x;
	matTranslation._42 = m_RelativePos.y;
	matTranslation._43 = m_RelativePos.z;

	m_matWorld = matScale * matZRot * matTranslation;
}

void CTransform::Binding()
{
	// 데이터 GPU 로 보내기
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	tTransform trans = {};
	trans.matWorld = m_matWorld;

	pCB->SetData(&trans);
	pCB->Binding();
}
