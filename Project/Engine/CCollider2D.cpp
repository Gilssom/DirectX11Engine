#include "pch.h"
#include "CCollider2D.h"

#include "CTransform.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_Scale(Vec3(1.f, 1.f, 1.f))
	, m_Absolute(false)
{

}

CCollider2D::~CCollider2D()
{

}

void CCollider2D::FinalTick()
{
	// ���� ��ġ ���� ���
	Vec3 vObjectPos = Transform()->GetRelativePos();
	m_FinalPos = vObjectPos + m_Offset;

	if (m_Absolute == false)
	{
		Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		Matrix matRot = XMMatrixRotationZ(m_Rotation.z);
		Matrix matTrans = XMMatrixTranslation(m_Offset.x, m_Offset.y, m_Offset.z);

		// Collider ���� ������� ũ��, ȸ��, ��ġ
		m_matColWorld = matScale * matRot * matTrans;

		// ������Ʈ�� ���� ����� ���������� ���� ( ������� ���� �����ϸ鼭 ���� ������ )
		m_matColWorld *= Transform()->GetWorldMat();
	}
	else
	{

	}


}