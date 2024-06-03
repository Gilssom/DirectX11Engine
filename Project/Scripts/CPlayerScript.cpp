#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>

#include <Engine\\CCollider2D.h>

#include "CCameraMoveScript.h"

CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_Speed(250.f)
	, m_TargetMonster(nullptr)
	, m_MoveLeft(false)
	, m_MoveRight(false)
	, m_CanMoveLeft(true)
	, m_CanMoveRight(true)
	, m_CanMoveUp(true)
	, m_CanMoveDown(true)
{
	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Speed", &m_Speed);
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::Begin()
{
	m_ParticlePrefab = CAssetManager::GetInst()->FindAsset<CPrefab>(L"Prefab\\ParticlePrefab.pref");
	m_MissilePrefab = CAssetManager::GetInst()->FindAsset<CPrefab>(L"Prefab\\Missile.pref");
}

void CPlayerScript::Tick()
{
	if (KEY_TAP(KEY::_1))
	{
		Ptr<CMaterial> pMtrl = CAssetManager::GetInst()->FindAsset<CMaterial>(L"BackGroundMaterial");
		pMtrl->SetScalarParam(INT_1, 1);
	}

	if (KEY_TAP(KEY::_2))
	{
		Ptr<CMaterial> pMtrl = CAssetManager::GetInst()->FindAsset<CMaterial>(L"BackGroundMaterial");
		pMtrl->SetScalarParam(INT_1, 0);
	}

	if (KEY_TAP(KEY::U))
	{
		Ptr<CMaterial> pMtrl = GetRenderComponent()->GetDynamicMaterial();
		pMtrl->SetScalarParam(INT_0, 1);
	}
	else if (KEY_RELEASED(KEY::U))
	{
		GetRenderComponent()->RestoreMaterial();
	}

	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();

	// Ű �Է¿� ���� ��ġ �̵�
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		if (!m_CanMoveUp)
			return;

		vCurPos.y += DT * m_Speed * 0.5f;
	}
	if (KEY_PRESSED(KEY::S))
	{
		if (!m_CanMoveDown)
			return;

		vCurPos.y -= DT * m_Speed * 0.5f;
	}

	// GameObject �� �������� ������ ���ؼ� Relative Scale x �� ����(����), ���(����) �� ������ ��.
	if (KEY_TAP(KEY::A))
	{
		if (!Transform()->GetLeft())
		{
			vCurPos += Vec3(-90.f, 0.f, 0.f);
			GetOwner()->Transform()->SetRelativePos(vCurPos);
		}
	}
	if (KEY_PRESSED(KEY::A))
	{
		if (!m_CanMoveLeft)
			return;

		m_MoveLeft = true;
		Transform()->SetLeft(true);
		Transform()->SetRight(false);
		vCurPos.x -= DT * m_Speed;
	}
	if(KEY_RELEASED(KEY::A))
		m_MoveLeft = false;

	if (KEY_TAP(KEY::D))
	{
		if (!Transform()->GetRight())
		{
			vCurPos += Vec3(90.f, 0.f, 0.f);
			GetOwner()->Transform()->SetRelativePos(vCurPos);
		}
	}
	if (KEY_PRESSED(KEY::D))
	{
		if (!m_CanMoveRight)
			return;

		m_MoveRight = true;
		Transform()->SetRight(true);
		Transform()->SetLeft(false);
		vCurPos.x += DT * m_Speed;
	}
	if (KEY_RELEASED(KEY::D))
		m_MoveRight = false;


	//if (KEY_PRESSED(KEY::Z))
	//{
	//	Vec3 vRot = GetOwner()->Transform()->GetRelativeRotation();
	//	vRot.z += DT * XM_PI; // 1�ʿ� 90��ŭ ȸ��
	//	GetOwner()->Transform()->SetRelativeRotation(vRot);

	//	//vCurPos.z += DT * m_Speed;
	//}
	if (KEY_TAP(KEY::ALT))
	{
		// Collider Ȱ��ȭ - ��Ȱ��ȭ ���� �Ϸ�
		//if (Collider2D()->IsActive())
		//{
		//	Collider2D()->Deactivate();
		//	//m_Speed = 10.f;
		//}
		//else
		//{
		//	Collider2D()->Activate();
		//}

		Instantiate(m_MissilePrefab, 0, Transform()->GetRelativePos());
	}

	Transform()->SetRelativePos(vCurPos);
}

#pragma region Collision Contents Script
void CPlayerScript::BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"East_Wall")
		m_CanMoveRight = false;

	if (otherObject->GetName() == L"West_Wall")
		m_CanMoveLeft = false;

	if (otherObject->GetName() == L"North_Wall")
		m_CanMoveUp = false;

	if (otherObject->GetName() == L"South_Wall")
		m_CanMoveDown = false;
}

void CPlayerScript::Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}

void CPlayerScript::EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"East_Wall")
		m_CanMoveRight = true;

	if (otherObject->GetName() == L"West_Wall")
		m_CanMoveLeft = true;

	if (otherObject->GetName() == L"North_Wall")
		m_CanMoveUp = true;

	if (otherObject->GetName() == L"South_Wall")
		m_CanMoveDown = true;
}
#pragma endregion

void CPlayerScript::SaveToLevelFile(FILE* file)
{
	fwrite(&m_Speed, sizeof(float), 1, file);
	SaveAssetRef(m_ParticlePrefab, file);
	SaveAssetRef(m_MissilePrefab, file);
}

void CPlayerScript::LoadFromLevelFile(FILE* file)
{
	fread(&m_Speed, sizeof(float), 1, file);
	LoadAssetRef(m_ParticlePrefab, file);
	LoadAssetRef(m_MissilePrefab, file);
}