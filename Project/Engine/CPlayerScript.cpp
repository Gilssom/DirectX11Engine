#include "pch.h"
#include "CPlayerScript.h"

#include "CMissileScript.h"
#include "CLevelManager.h"
#include "CLevel.h"

#include "CCollider2D.h"
#include "CStructuredBuffer.h"

CPlayerScript::CPlayerScript()
	: m_Speed(300.f)
{
	m_StructBuffer = new CStructuredBuffer;
}

CPlayerScript::~CPlayerScript()
{
	if (m_StructBuffer != nullptr)
		delete m_StructBuffer;
}

void CPlayerScript::Begin()
{
	Vec4 vData = Vec4(1.f, 2.f, 3.f, 4.f);
	m_StructBuffer->Create(sizeof(Vec4), 1, &vData);
	m_StructBuffer->Binding(20);
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
	//if (KEY_PRESSED(KEY::Z))
	//{
	//	Vec3 vRot = GetOwner()->Transform()->GetRelativeRotation();
	//	vRot.z += DT * XM_PI; // 1초에 90만큼 회전
	//	GetOwner()->Transform()->SetRelativeRotation(vRot);

	//	//vCurPos.z += DT * m_Speed;
	//}
	if (KEY_TAP(KEY::SPACE))
	{
		// Collider 활성화 - 비활성화 구현 완료
		if (Collider2D()->IsActive())
		{
			Collider2D()->Deactivate();
			m_Speed = 10.f;
		}
		else
		{
			Collider2D()->Activate();
		}

 		CGameObject* pNewObj = new CGameObject;

		pNewObj->AddComponent(new CTransform);
		pNewObj->AddComponent(new CMeshRender);
		pNewObj->AddComponent(new CMissileScript);

		Vec3 vPos = Transform()->GetRelativePos();
		vPos.y += Transform()->GetRelativeScale().y / 2.f;
		pNewObj->Transform()->SetRelativePos(vPos);
		pNewObj->Transform()->SetRelativeScale(Vec3(40.f, 40.f, 40.f));

		pNewObj->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pNewObj->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DMaterial"));

		SpawnObject(0, pNewObj);

		//CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();
		//pCurLevel->AddObject(0, pNewObj);
	}

	if (IsValid(m_TargetMonster))
	{
		Vec3 vDir = m_TargetMonster->Transform()->GetWorldPos() - Transform()->GetWorldPos();
		vDir.Normalize();

		vCurPos += vDir * m_Speed * DT;
	}

	Transform()->SetRelativePos(vCurPos);
}

#pragma region Collision Contents Script
void CPlayerScript::BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	//otherObject->Destroy();
}

void CPlayerScript::Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}

void CPlayerScript::EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	int a = 0;
}
#pragma endregion