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

	Matrix matRot =  XMMatrixRotationX(m_RelativeRotation.x);
		   matRot *= XMMatrixRotationY(m_RelativeRotation.y);
		   matRot *= XMMatrixRotationZ(m_RelativeRotation.z);

	Matrix matTranslation = XMMatrixTranslation(m_RelativePos.x, m_RelativePos.y, m_RelativePos.z);

	m_matWorld = matScale * matRot * matTranslation;

	// ������Ʈ�� ���� ���� ���
	m_WorldDir[(UINT)DIR_TYPE::RIGHT]	= m_RelativeDir[(UINT)DIR_TYPE::RIGHT]	= XAxis;
	m_WorldDir[(UINT)DIR_TYPE::UP]		= m_RelativeDir[(UINT)DIR_TYPE::UP]		= YAxis;
	m_WorldDir[(UINT)DIR_TYPE::FRONT]	= m_RelativeDir[(UINT)DIR_TYPE::FRONT]	= ZAxis;

	for (int i = 0; i < 3; i++)
	{
		// ȸ�� ����� 4�� ��ǥ���� ������ ���� ������ 1�� �ص� ������		( Coord )
		// ���� ����� ��� ��ǥ�� ������ �ֱ� ������ 0���� ���־�� �Ѵ�.	( Normal )
		m_RelativeDir[i] = XMVector3TransformNormal(m_RelativeDir[i], matRot);
		m_RelativeDir[i].Normalize();
	}

	// �θ� �ֱ� ������ �θ���� ������� ��ǥ�� ����� ���־����
	if (GetOwner()->GetParent())
	{
		const Matrix& matParentWorldMat = GetOwner()->GetParent()->Transform()->GetWorldMat();

		m_matWorld *= matParentWorldMat;

		for (int i = 0; i < 3; i++)
		{
			m_WorldDir[i] = XMVector3TransformNormal(m_WorldDir[i], m_matWorld);
			m_WorldDir[i].Normalize();
		}
	}
	// �θ� ������Ʈ�� ���� ���, ������ �ֻ��� �θ� ������Ʈ
	else
	{
		for (int i = 0; i < 3; i++)
		{
			m_WorldDir[i] = m_RelativeDir[i];
		}
	}
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
