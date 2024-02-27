#include "pch.h"
#include "CCollider2D.h"

#include "CTransform.h"
#include "CScript.h"

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
		// Collider �� �������� ũ�� ȸ�� ��ġ�� �����ֱ�
		Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		Matrix matRot = XMMatrixRotationZ(m_Rotation.z);
		Matrix matTrans = XMMatrixTranslation(m_Offset.x, m_Offset.y, m_Offset.z);

		// Collider ���� ������� ũ��, ȸ��, ��ġ
		m_matColWorld = matScale * matRot * matTrans;

		Matrix matObjScaleInv = XMMatrixIdentity();
		Vec3 vObjScale = Transform()->GetRelativeScale();
		matObjScaleInv = XMMatrixScaling(vObjectPos.x, vObjectPos.y, vObjectPos.z);
		matObjScaleInv = XMMatrixInverse(nullptr, matObjScaleInv);

		// ������Ʈ�� ���� ����� ���������� ���� ( ������� ���� �����ϸ鼭 ���� ������ )
		m_matColWorld = m_matColWorld * matObjScaleInv * Transform()->GetWorldMat();
	}

	if (m_OverlapCount == 0)
		DrawDebugRect(m_matColWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f);
	else if (m_OverlapCount >= 1)
		DrawDebugRect(m_matColWorld, Vec4(1.f, 0.2f, 0.2f, 1.f), 0.f);
	else
		assert(nullptr);
}

void CCollider2D::BeginOverlap(CCollider2D* otherCollider)
{
	++m_OverlapCount;

	const vector<CScript*>& vecScripts = GetOwner()->GetScripts();

	for (size_t i = 0; i < vecScripts.size(); i++)
	{
		vecScripts[i]->BeginOverlap(this, otherCollider->GetOwner(), otherCollider);
	}
}

void CCollider2D::Overlap(CCollider2D* otherCollider)
{
	const vector<CScript*>& vecScripts = GetOwner()->GetScripts();

	for (size_t i = 0; i < vecScripts.size(); i++)
	{
		vecScripts[i]->Overlap(this, otherCollider->GetOwner(), otherCollider);
	}
}

void CCollider2D::EndOverlap(CCollider2D* otherCollider)
{
	--m_OverlapCount;

	const vector<CScript*>& vecScripts = GetOwner()->GetScripts();

	for (size_t i = 0; i < vecScripts.size(); i++)
	{
		vecScripts[i]->EndOverlap(this, otherCollider->GetOwner(), otherCollider);
	}
}