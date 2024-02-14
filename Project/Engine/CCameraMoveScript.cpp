#include "pch.h"
#include "CCameraMoveScript.h"

CCameraMoveScript::CCameraMoveScript()
	: m_Speed(200.f)
{

}

CCameraMoveScript::~CCameraMoveScript()
{

}

void CCameraMoveScript::Tick()
{
	// 키 입력에 따른 위치 이동
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::UP))
	{
		vCurPos.y += DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::DOWN))
	{
		vCurPos.y -= DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::LEFT))
	{
		vCurPos.x -= DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		vCurPos.x += DT * m_Speed;
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}