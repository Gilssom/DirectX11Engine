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
	// Shift 속도 배율
	float speed = m_Speed;
	if (KEY_PRESSED(KEY::LSHIFT))
	{
		speed *= 4.f;
	}

	// 키 입력에 따른 위치 이동
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

	if (KEY_PRESSED(KEY::UP))
	{
		vCurPos +=  vFront * speed * DT;
	}
	if (KEY_PRESSED(KEY::DOWN))
	{
		vCurPos += -vFront * speed * DT;
	}
	if (KEY_PRESSED(KEY::LEFT))
	{
		vCurPos += -vRight * speed * DT;
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		vCurPos += vRight * speed * DT;
	}

	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 vDrag = CKeyManager::GetInst()->GetMouseDrag();

		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += vDrag.x * DT * XM_PI * 10.f;
		vRot.x -= vDrag.y * DT * XM_PI * 10.f;

		Transform()->SetRelativeRotation(vRot);
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}