#include "pch.h"
#include "CPlayerScript.h"


CPlayerScript::CPlayerScript()
	: m_Speed(100.f)
{

}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::Tick()
{
	// Ű �Է¿� ���� ��ġ �̵�
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vCurPos.y += DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::S))
	{
		vCurPos.y -= DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::A))
	{
		vCurPos.x -= DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::D))
	{
		vCurPos.x += DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = GetOwner()->Transform()->GetRelativeRotation();
		vRot.z += DT * XM_PI; // 1�ʿ� 90��ŭ ȸ��
		GetOwner()->Transform()->SetRelativeRotation(vRot);

		//vCurPos.z += DT * m_Speed;
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}

#pragma region Collision Contents Script
void CPlayerScript::BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}

void CPlayerScript::Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}

void CPlayerScript::EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}
#pragma endregion