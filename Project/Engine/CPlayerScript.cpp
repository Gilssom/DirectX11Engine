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
	// 키 입력에 따른 위치 이동
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
		vRot.z += DT * XM_PI; // 1초에 180만큼 회전
		GetOwner()->Transform()->SetRelativeRotation(vRot);
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}