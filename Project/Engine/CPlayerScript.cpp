#include "pch.h"
#include "CPlayerScript.h"


CPlayerScript::CPlayerScript()
	: m_Speed(1.f)
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
	else if (KEY_PRESSED(KEY::S))
	{
		vCurPos.y -= DT * m_Speed;
	}
	else if (KEY_PRESSED(KEY::A))
	{
		vCurPos.x -= DT * m_Speed;
	}
	else if (KEY_PRESSED(KEY::D))
	{
		vCurPos.x += DT * m_Speed;
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}