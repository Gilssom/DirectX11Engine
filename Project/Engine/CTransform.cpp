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

	// ũ�� -> ȸ�� -> �̵� �������� ����ؾ� ��

	// 4���� ��� ���
	// ȸ�� ������ ũ��, �̵��� �Ѳ����� �ϱ� ���� ����� 3�� ����� ���� �̸� �������� �ع�����.
	Matrix matScale = XMMatrixScaling(m_RelativeScale.x, m_RelativeScale.y, m_RelativeScale.z); // ��� ��� �Լ� ����
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
	// ������ GPU �� ������
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	// �ڽ��� ����ִ� Camera �� View ��� ������ �´�.
	g_Trans.matWorld = m_matWorld;

	pCB->SetData(&g_Trans);
	pCB->Binding();
}
