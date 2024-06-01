#include "pch.h"
#include "CPlayerScript.h"

#include "CMissileScript.h"
#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>

#include <Engine\\CCollider2D.h>

CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_Speed(300.f)
	, m_TargetMonster(nullptr)
	, m_MoveLeft(false)
	, m_MoveRight(false)
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

	// GameObject 를 양쪽으로 뒤집기 위해선 Relative Scale x 에 음수(좌측), 양수(우측) 값 넣으면 됨.
	if (KEY_TAP(KEY::A))
	{
		//Transform()->SetRelativePos(Transform()->GetRelativePos() + Vec3(-90.f, 0.f, 0.f));
	}
	if (KEY_PRESSED(KEY::A))
	{
		m_MoveLeft = true;
		Transform()->SetLeft(true);
		Transform()->SetRight(false);
		vCurPos.x -= DT * m_Speed;
	}
	if(KEY_RELEASED(KEY::A))
		m_MoveLeft = false;

	if (KEY_TAP(KEY::D))
	{
		//Transform()->SetRelativePos(Transform()->GetRelativePos() + Vec3(90.f, 0.f, 0.f));
	}
	if (KEY_PRESSED(KEY::D))
	{
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
	//	vRot.z += DT * XM_PI; // 1초에 90만큼 회전
	//	GetOwner()->Transform()->SetRelativeRotation(vRot);

	//	//vCurPos.z += DT * m_Speed;
	//}
	if (KEY_TAP(KEY::ALT))
	{
		// Collider 활성화 - 비활성화 구현 완료
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
	//wstring testPath = CPathManager::GetInst()->GetContentPath();
	//testPath += L"Level\\ElvenGard_0.lv";
	//CLevel* m_CurLevel = CLevelSaveLoad::LoadLevel(testPath);

	//CLevel* m_NextLevel = LoadLevel();
	//m_NextLevel = new CLevel;

	//ChangeLevel(m_NextLevel, LEVEL_STATE::PLAY);
	//otherObject->Destroy();
}

void CPlayerScript::Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}

void CPlayerScript::EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

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