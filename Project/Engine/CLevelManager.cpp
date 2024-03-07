#include "pch.h"
#include "CLevelManager.h"
#include "CAssetManager.h"

#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "components.h"
#include "CAnim2D.h"

#include "CPlayerScript.h"
#include "CCameraMoveScript.h"

#include "CCollisionManager.h"

CLevelManager::CLevelManager()
	: m_CurLevel(nullptr)
{

}

CLevelManager::~CLevelManager()
{
	if (m_CurLevel != nullptr)
	{
		delete m_CurLevel;
	}
}

void CLevelManager::Init()
{
	m_CurLevel = new CLevel;

	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Player");
	m_CurLevel->GetLayer(2)->SetName(L"Monster");

	// 오브젝트에 컴포넌트 등록 후, 컴포넌트의 함수에 접근 후 세팅
	
	// Camera
	CGameObject* pCamObject = new CGameObject;
	pCamObject->SetName(L"Camera");
	pCamObject->AddComponent(new CTransform);
	pCamObject->AddComponent(new CCamera);
	pCamObject->AddComponent(new CCameraMoveScript);

	pCamObject->Camera()->SetCameraPriority(0); // Main Camera Setting
	pCamObject->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObject->Camera()->LayerCheckAll();

	m_CurLevel->AddObject(0, pCamObject);


	// Player
	CGameObject* pPlayer = new CGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new CTransform);
	pPlayer->AddComponent(new CMeshRender);
	pPlayer->AddComponent(new CCollider2D);
	pPlayer->AddComponent(new CAnimator2D);
	pPlayer->AddComponent(new CPlayerScript);

	pPlayer->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pPlayer->Transform()->SetRelativeScale(100.f, 100.f, 0.2f);

	pPlayer->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DMaterial"));
	pPlayer->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetManager::GetInst()->FindAsset<CTexture>(L"texture\\Character.png"));

	pPlayer->Collider2D()->SetAbsolute(false);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	Ptr<CTexture> pAtlas = CAssetManager::GetInst()->Load<CTexture>(L"texture\\link.png", L"texture\\link.png");
	//pPlayer->Animator2D()->CreateAnimation(L"MOVE_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(240.f, 260.f), 10, 16);
	//pPlayer->Animator2D()->CreateAnimation(L"IDLE_RIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(240.f, 260.f), 3, 2);
	//pPlayer->Animator2D()->FindAnimation(L"MOVE_DOWN")->Save(L"Animation\\");

	pPlayer->Animator2D()->LoadAnimation(L"Animation\\MOVE_DOWN.anim");
	pPlayer->Animator2D()->Play(L"MOVE_DOWN", true);

	m_CurLevel->AddObject(1, pPlayer, false);

	// Monster
	CGameObject* pMonster = new CGameObject;
	pMonster->SetName(L"Monster");
	pMonster->AddComponent(new CTransform);
	pMonster->AddComponent(new CMeshRender);
	pMonster->AddComponent(new CCollider2D);

	pMonster->Transform()->SetRelativePos(Vec3(200.f, 0.f, 0.f));
	pMonster->Transform()->SetRelativeScale(100.f, 100.f, 0.f);
	pMonster->Transform()->SetAbsolute(true);

	pMonster->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DMaterial"));

	pMonster->Collider2D()->SetAbsolute(false);
	pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pMonster->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	// Player 와 Monster 를 부모-자식 관계로 연결
	//pPlayer->AddChild(pMonster);
	m_CurLevel->AddObject(1, pMonster, false);

	pPlayer->GetScript<CPlayerScript>()->SetTarget(pMonster);

	// Level 의 Collision Setting
	CCollisionManager::GetInst()->LayerCheck(1, 1);
	CCollisionManager::GetInst()->LayerCheck(1, 2);
}

void CLevelManager::Tick()
{
	if (m_CurLevel != nullptr)
	{
		m_CurLevel->Tick(); 
		m_CurLevel->FinalTick();
	}
}
