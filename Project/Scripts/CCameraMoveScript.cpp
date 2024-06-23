#include "pch.h"
#include "CCameraMoveScript.h"

#include <Engine\\CCamera.h>
#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>

#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>
				 
#include <Engine\\CDevice.h>

#include "CPlayerScript.h"

CCameraMoveScript::CCameraMoveScript()
	: CScript(SCRIPT_TYPE::CAMERAMOVESCRIPT)
	, m_TargetObject(nullptr)
	, m_Speed(200.f)
{
	AddScriptProperty(PROPERTY_TYPE::GAMEOBJECT, "Target Object", &m_TargetObject);
	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Speed", &m_Speed);
}

CCameraMoveScript::~CCameraMoveScript()
{

}

void CCameraMoveScript::Tick()
{
	// ī�޶� ���� ��� ����
	if (KEY_TAP(KEY::P))
	{
		Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC ? Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE) : Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);

		if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
		{
			Vec3 vPos = Transform()->GetRelativePos();
			Transform()->SetRelativePos(Vec3(vPos.x, vPos.y, 0.f));
			Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		}
	}

	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();
	if(pCurLevel != nullptr)
		m_TargetObject = pCurLevel->FindObjectByName(L"Player");

	if (Camera()->GetProjType() == PROJ_TYPE::PERSPECTIVE)
		MoveByPerspective();

	else
		MoveByOrthographic();
}

void CCameraMoveScript::MoveByPerspective()
{
	// Shift �ӵ� ����
	float speed = m_Speed;
	if (KEY_PRESSED(KEY::LSHIFT))
	{
		speed *= 4.f;
	}

	// Ű �Է¿� ���� ��ġ �̵�
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

	if (KEY_PRESSED(KEY::UP))
	{
		vCurPos += vFront * speed * DT;
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

void CCameraMoveScript::MoveByOrthographic()
{
	if (m_TargetObject)
	{
		CPlayerScript* pPlayerScript = m_TargetObject->GetScript<CPlayerScript>();

		if (pPlayerScript->GetOriginPos() == nullptr)
			return;

		Vec3 vObjectPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();

		// 1. �ش� ������ ��� Object Scael �� �����´�.
		CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();
		CGameObject* pBackGround_0 = pCurLevel->FindObjectByName(L"BackGround_0");
		CGameObject* pBackGround_1 = pCurLevel->FindObjectByName(L"BackGround_1");
		float halfX = pBackGround_1->Transform()->GetRelativeScale().x / 2;
		float halfY = pBackGround_1->Transform()->GetRelativeScale().y / 2;

		// 2. ���� ī�޶� ������ �ػ�
		Vec2 vRenderResol = CDevice::GetInst()->GetRenderResolution();

		// 3. ī�޶� �̵� ���� ���
		float minX = (vRenderResol.x / 2.0f) - halfX;
		float maxX = halfX - (vRenderResol.x / 2.0f);
		float minY = (vRenderResol.y / 2.0f) - halfY;
		float maxY = halfY - (vRenderResol.y / 2.0f);

		// 4. �ּҰ��� �ִ밪���� ũ�� �ʵ��� ����
		if (minX > maxX) 
			std::swap(minX, maxX);

		if (minY > maxY) 
			std::swap(minY, maxY);

		// 5. ī�޶� ��ġ ����
		float newX = Custom_Clamp(vObjectPos.x, minX, maxX);
		float newY = Custom_Clamp(vObjectPos.y, minY, maxY);

		// 6. ī�޶��� �̵��� ���� �޹�� ��ǥ ��ȭ
		Vec3 vBackOriginPos = pBackGround_0->Transform()->GetRelativePos();

		if (pPlayerScript->GetMoveLeft() && pPlayerScript->GetMove())
		{
			Vec3 vNewBackPos = vBackOriginPos + Vec3(10.f * DT, 0.f, 0.f);
			pBackGround_0->Transform()->SetRelativePos(vNewBackPos);
		}

		if (pPlayerScript->GetMoveRight() && pPlayerScript->GetMove())
		{
			Vec3 vNewBackPos = vBackOriginPos + Vec3(-10.f * DT, 0.f, 0.f);
			pBackGround_0->Transform()->SetRelativePos(vNewBackPos);
		}
			
		// 7. �÷��̾ �ٶ󺸴� ���⿡ ���� ��ġ ����
		// Player Origin Pos �߰��� ���� ���� �ʿ� X
		/*if (pPlayerScript->Transform()->GetLeft())
		{
			if (newX + 45.f >= maxX + 45.f)
				newX += 0.f;

			if (newX - maxX > 45.f)
				newX += (newX - maxX) - 45.f;

			else if (newX - 45.f <= maxX)
				newX += 45.f;
		}
		else if (pPlayerScript->Transform()->GetRight())
		{
			if (newX - 45.f <= minX - 45.f)
				newX += 0.f;
				
			if(newX - minX < 45.f)
				newX += -(newX - minX) + 45.f;
			
			else if(newX - 45.f >= minX)
				newX += -45.f;
		}

		if (newX < minX + 45.f || newX > maxX - 45.f)
			return;*/

		// ī�޶� ��ġ ���� ����
		GetOwner()->Transform()->SetRelativePos(Vec3(newX, newY, 0.f));
	}

	UpdateShake();
}

void CCameraMoveScript::StartShake(float duration, float magnitude)
{
	m_IsShaking = true;
	m_ShakeDuration = duration;
	m_ShakeTimer = 0;
	m_ShakeMagnitude = magnitude;
}

void CCameraMoveScript::UpdateShake()
{
	Vec3 camPos = GetOwner()->Transform()->GetRelativePos();

	if (m_IsShaking)
	{
		m_ShakeTimer += DT;

		if (m_ShakeTimer > m_ShakeDuration)
		{
			m_IsShaking = false;
		}
		else
		{
			float offsetX = GetRandomFloat(-1.f, 1.f) * m_ShakeMagnitude;
			float offsetY = GetRandomFloat(-1.f, 1.f) * m_ShakeMagnitude;
			Vec3 shakePos = camPos + Vec3(offsetX, offsetY, 0);
			GetOwner()->Transform()->SetRelativePos(shakePos);
		}
	}
}