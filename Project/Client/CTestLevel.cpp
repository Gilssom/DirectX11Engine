#include "pch.h"

#include "CTestLevel.h"

#include <Engine\\CLevel.h>
#include <Engine\\CLayer.h>
#include <Engine\\CGameObject.h>
#include <Engine\\components.h>
#include <Engine\\CAnim2D.h>

#include <Scripts\\CPlayerScript.h>
#include <Scripts\\CCameraMoveScript.h>
#include <Scripts\\CBackGroundScript.h>
#include <Scripts\\CMissileScript.h>

#include <Engine\\CCollisionManager.h>
#include <Engine\\CSetColorCS.h>

#include <Engine\\CStructuredBuffer.h>
#include <Engine\\CPrefab.h>

#include "CLevelSaveLoad.h"

void CTestLevel::CreateTestLevel()
{
	// Prefab 제작 및 Asset Manager 에 등록
	CreatePrefab();

#pragma region Empty Level
	//CLevel* m_NewLevel = nullptr;
	//m_NewLevel = new CLevel;
	//m_NewLevel->GetLayer(0)->SetName(L"Default");
	//m_NewLevel->GetLayer(1)->SetName(L"Player");
	//m_NewLevel->GetLayer(2)->SetName(L"Monster");
	//m_NewLevel->GetLayer(3)->SetName(L"BackGround");
	//
	//ChangeLevel(m_NewLevel, LEVEL_STATE::STOP);
	//return;
#pragma endregion

#pragma region Object Add
	// Level
	wstring testPath = CPathManager::GetInst()->GetContentPath();
	testPath += L"Level\\ElvenGard_0.lv";
	CLevel* m_CurLevel = CLevelSaveLoad::LoadLevel(testPath);
	//m_CurLevel->GetLayer(4)->SetName(L"Portal");

	// Level 의 Collision Setting
	//CCollisionManager::GetInst()->LayerCheck(1, 1);
	//CCollisionManager::GetInst()->LayerCheck(1, 2);
	//CCollisionManager::GetInst()->LayerCheck(1, 4);

	// Test Bgm Play
	Ptr<CSound> pTestBgm = CAssetManager::GetInst()->FindAsset<CSound>(L"Sound\\elven_guard_old.wav");
	pTestBgm->Play(0, 0.3f, true);

	// TileMap Object
	//CGameObject* pTileMapObj = new CGameObject;
	//pTileMapObj->SetName(L"TileMap");
	//pTileMapObj->AddComponent(new CTransform);
	//pTileMapObj->AddComponent(new CTileMap);
	
	//pTileMapObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));
	
	//pTileMapObj->TileMap()->SetAtlasTexture(CAssetManager::GetInst()->Load<CTexture>(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));
	//pTileMapObj->TileMap()->SetAtlasTileSize(Vec2(64.f, 64.f));
	//pTileMapObj->TileMap()->SetTileEachSize(Vec2(64.f, 64.f));
	//pTileMapObj->TileMap()->SetRowCol(20, 20);
	//m_CurLevel->AddObject(0, pTileMapObj);

	//CGameObject* pTestObject = new CGameObject;
	//pTestObject->SetName(L"TestObject");
	//pTestObject->AddComponent(new CTransform);
	//pTestObject->AddComponent(new CMeshRender);
	//pTestObject->AddComponent(new CAnimator2D);
	
	//pTestObject->Transform()->SetRelativePos(Vec3(-427.f, 70.2f, 89.f));
	//pTestObject->Transform()->SetRelativeScale(Vec3(89.f, 175.f, 1.f));
	
	//pTestObject->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pTestObject->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DMaterial"));
	
	//pTestObject->Animator2D()->LoadAnimation(L"Animation\\Test.anim");
	//pTestObject->Animator2D()->Play(L"Test", true);
	
	//m_CurLevel->AddObject(3, pTestObject, false);

	CGameObject* pTestPlayer = new CGameObject;

	pTestPlayer->SetName(L"TestPlayer");
	pTestPlayer->AddComponent(new CTransform);
	pTestPlayer->AddComponent(new CMeshRender);
	pTestPlayer->AddComponent(new CAnimator2D);

	pTestPlayer->Transform()->SetRelativePos(Vec3(92.f, 0.f, 100.f));
	pTestPlayer->Transform()->SetRelativeScale(Vec3(800.f, 600.f, 1.f));

	pTestPlayer->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pTestPlayer->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaMaterial"));

	pTestPlayer->Animator2D()->LoadAnimation(L"Animation\\Tau_Idle.anim");
	pTestPlayer->Animator2D()->Play(L"Tau_Idle", true);

	m_CurLevel->AddObject(3, pTestPlayer, false);

	ChangeLevel(m_CurLevel, LEVEL_STATE::STOP);
	return;
#pragma endregion

	

	// 오브젝트에 컴포넌트 등록 후, 컴포넌트의 함수에 접근 후 세팅


	

	// Clone Test
	//CGameObject* pCamClone = pCamObject->Clone();
	//pCamClone->Camera()->SetCameraPriority(0);
	//m_CurLevel->AddObject(0, pCamClone);
	//delete pCamObject;


	// Light Object
	CGameObject* pLightObject = new CGameObject;
	pLightObject->SetName(L"Directional Light");
	pLightObject->AddComponent(new CTransform);
	pLightObject->AddComponent(new CLight2D);

	pLightObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));

	//pLightObject->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	//pLightObject->Light2D()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
	//pLightObject->Light2D()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));

	pLightObject->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObject->Light2D()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
	pLightObject->Light2D()->SetAmbient(Vec3(0.f, 0.f, 0.f));
	pLightObject->Light2D()->SetRange(500.f);

	m_CurLevel->AddObject(0, pLightObject);

	// Clone Test
	//pLightObject = pLightObject->Clone();
	//pLightObject->Transform()->SetRelativePos(Vec3(300.f, 0.f, 0.f));
	//m_CurLevel->AddObject(0, pLightObject);


	

	// Clone Test
	//pTileMapObj = pTileMapObj->Clone();
	//pTileMapObj->Transform()->SetRelativePos(Vec3(200.f, 100.f, 1.f));
	//m_CurLevel->AddObject(0, pTileMapObj);

	// Clone Test
	/*pPlayer = pPlayer->Clone();
	pPlayer->Transform()->SetRelativePos(Vec3(100.f, 0.f, 100.f));
	m_CurLevel->AddObject(0, pPlayer, false);*/


	// Monster
	CGameObject* pMonster = new CGameObject;
	pMonster->SetName(L"Monster");
	pMonster->AddComponent(new CTransform);
	pMonster->AddComponent(new CMeshRender);
	pMonster->AddComponent(new CCollider2D);

	pMonster->Transform()->SetRelativePos(Vec3(200.f, 100.f, 0.f));
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

	//pPlayer->GetScript<CPlayerScript>()->SetTarget(pMonster);


	// Back Ground Object
	CGameObject* pBackGround = new CGameObject;
	pBackGround->SetName(L"BackGround_0");
	pBackGround->AddComponent(new CTransform);
	pBackGround->AddComponent(new CMeshRender);
	pBackGround->AddComponent(new CBackGroundScript);

	pBackGround->Transform()->SetRelativePos(Vec3(0.f, 0.f, 1000.f));
	pBackGround->Transform()->SetRelativeScale(Vec3(2688.f * 1.37f, 560.f * 1.37f, 1.f));

	pBackGround->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pBackGround->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"ElvenGard_BackGround_0"));
	//pBackGround->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetManager::GetInst()->Load<CTexture>(L"texture\\ElvenGard\\ElvenGard_BackGround_0.png", L"texture\\ElvenGard\\ElvenGard_BackGround_0.png"));

	m_CurLevel->AddObject(3, pBackGround, false);

	CGameObject* pBackGround1 = new CGameObject;
	pBackGround1->SetName(L"BackGround_1");
	pBackGround1->AddComponent(new CTransform);
	pBackGround1->AddComponent(new CMeshRender);
	pBackGround1->AddComponent(new CBackGroundScript);

	pBackGround1->Transform()->SetRelativePos(Vec3(0.f, 0.f, 800.f));
	pBackGround1->Transform()->SetRelativeScale(Vec3(2688.f * 1.37f, 560.f * 1.37f, 1.f));

	pBackGround1->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pBackGround1->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"ElvenGard_BackGround_1"));
	//pBackGround1->MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, CAssetManager::GetInst()->Load<CTexture>(L"texture\\ElvenGard\\ElvenGard_BackGround_1.png", L"texture\\ElvenGard\\ElvenGard_BackGround_1.png"));

	m_CurLevel->AddObject(3, pBackGround1, false);

	CGameObject* pBackGround2 = new CGameObject;
	pBackGround2->SetName(L"BackGround_2");
	pBackGround2->AddComponent(new CTransform);
	pBackGround2->AddComponent(new CMeshRender);
	pBackGround2->AddComponent(new CBackGroundScript);

	pBackGround2->Transform()->SetRelativePos(Vec3(0.f, 0.f, 90.f));
	pBackGround2->Transform()->SetRelativeScale(Vec3(2688.f * 1.37f, 560.f * 1.37f, 1.f));

	pBackGround2->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pBackGround2->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"ElvenGard_BackGround_2"));
	//pBackGround2->MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, CAssetManager::GetInst()->Load<CTexture>(L"texture\\ElvenGard\\ElvenGard_BackGround_2.png", L"texture\\ElvenGard\\ElvenGard_BackGround_2.png"));

	m_CurLevel->AddObject(3, pBackGround2, false);


	// Smith Fire Object
	CGameObject* pSmithFireObject = new CGameObject;
	pSmithFireObject->SetName(L"SmithFire");
	pSmithFireObject->AddComponent(new CTransform);
	pSmithFireObject->AddComponent(new CMeshRender);
	pSmithFireObject->AddComponent(new CAnimator2D);

	pSmithFireObject->Transform()->SetRelativePos(Vec3(-427.f, 70.2f, 89.f));
	pSmithFireObject->Transform()->SetRelativeScale(Vec3(89.f, 175.f, 1.f));

	pSmithFireObject->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pSmithFireObject->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaMaterial"));

	//Ptr<CTexture> pAtlas = CAssetManager::GetInst()->Load<CTexture>(L"texture\\ElvenGard\\Smith_Fire.png", L"texture\\ElvenGard\\Smith_Fire.png");
	//pSmithFireObject->Animator2D()->CreateAnimation(L"SMITHFIRE_ANIM", pAtlas, Vec2(0.f, 0.f), Vec2(64.f, 130.f), Vec2(64.f, 130.f), 8, 12);
	//pSmithFireObject->Animator2D()->FindAnimation(L"SMITHFIRE_ANIM")->Save(L"Animation\\");

	pSmithFireObject->Animator2D()->LoadAnimation(L"Animation\\SMITHFIRE_ANIM.anim");
	pSmithFireObject->Animator2D()->Play(L"SMITHFIRE_ANIM", true);

	m_CurLevel->AddObject(3, pSmithFireObject, false);

	// Gate Portal Object
	CGameObject* pGatePortalObject = new CGameObject;
	pGatePortalObject->SetName(L"GatePortal");
	pGatePortalObject->AddComponent(new CTransform);
	pGatePortalObject->AddComponent(new CMeshRender);
	pGatePortalObject->AddComponent(new CAnimator2D);

	pGatePortalObject->Transform()->SetRelativePos(Vec3(-427.f, 70.2f, 89.f));
	pGatePortalObject->Transform()->SetRelativeScale(Vec3(800.f, 600.f, 1.f));

	pGatePortalObject->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pGatePortalObject->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaMaterial"));

	//Ptr<CTexture> pAtlas = CAssetManager::GetInst()->Load<CTexture>(L"texture\\ElvenGard\\Gate_Portal.png", L"texture\\ElvenGard\\Gate_Portal.png");
	//pGatePortalObject->Animator2D()->CreateAnimation(L"GATE_PORTAL", pAtlas, Vec2(0.f, 0.f), Vec2(400.f, 300.f), Vec2(400.f, 300.f), 29, 12);
	//pGatePortalObject->Animator2D()->FindAnimation(L"GATE_PORTAL")->Save(L"Animation\\");

	pGatePortalObject->Animator2D()->LoadAnimation(L"Animation\\GATE_PORTAL.anim");
	pGatePortalObject->Animator2D()->Play(L"GATE_PORTAL", true);

	m_CurLevel->AddObject(3, pGatePortalObject, false);

	// Linus Object
	CGameObject* pLinus = new CGameObject;
	pLinus->SetName(L"Linus");
	pLinus->AddComponent(new CTransform);
	pLinus->AddComponent(new CMeshRender);
	pLinus->AddComponent(new CAnimator2D);

	pLinus->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pLinus->Transform()->SetRelativeScale(Vec3(800.f, 600.f, 1.f));
	//pLinus->Transform()->SetTurn();

	pLinus->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pLinus->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaMaterial"));

	//Ptr<CTexture> pAtlas2 = CAssetManager::GetInst()->Load<CTexture>(L"texture\\ElvenGard\\npc_linus.png", L"texture\\ElvenGard\\npc_linus.png");
	//pLinus->Animator2D()->CreateAnimation(L"LINUS", pAtlas2, Vec2(0.f, 0.f), Vec2(800.f, 600.f), Vec2(800.f, 600.f), 12, 10);
	//pLinus->Animator2D()->FindAnimation(L"LINUS")->Save(L"Animation\\");

	pLinus->Animator2D()->LoadAnimation(L"Animation\\LINUS.anim");
	pLinus->Animator2D()->Play(L"LINUS", true);

	m_CurLevel->AddObject(3, pLinus, false);

	// Test Object
	/*CGameObject* pTestObject = new CGameObject;
	pTestObject->AddComponent(new CTransform);
	pTestObject->AddComponent(new CMeshRender);
	pTestObject->AddComponent(new CBackGroundScript);
	pTestObject->AddComponent(new CPlayerScript);

	pTestObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pTestObject->Transform()->SetRelativeScale(Vec3(711.f, 358.f, 1.f));

	pTestObject->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pTestObject->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"BackGroundMaterial"));
	pTestObject->MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, CAssetManager::GetInst()->Load<CTexture>(L"texture\\blacksmith.png", L"texture\\blacksmith.png"));
	pTestObject->MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_1, CAssetManager::GetInst()->Load<CTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg"));

	m_CurLevel->AddObject(0, pTestObject, false);*/


	// PostProcee Filter 추가
	CGameObject* pFilterObject = new CGameObject;
	pFilterObject->SetName(L"Post Process");
	pFilterObject->AddComponent(new CTransform);
	pFilterObject->AddComponent(new CMeshRender);

	pFilterObject->Transform()->SetRelativePos(200.f, 0.f, 500.f);
	pFilterObject->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

	pFilterObject->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pFilterObject->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"DistortionMaterial"));
	pFilterObject->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetManager::GetInst()->FindAsset<CTexture>(L"RenderTargetCopyTex"));
	pFilterObject->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CAssetManager::GetInst()->Load<CTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg"));

	m_CurLevel->AddObject(0, pFilterObject, false);

	// 레벨 시작
	//m_CurLevel->Init();

	// Level Change System 을 이용해서 Level 을 전달해줄 것 (Task Manager)
	ChangeLevel(m_CurLevel, LEVEL_STATE::STOP);
}

void CTestLevel::CreatePrefab()
{
	// Particle Prefab
	CGameObject* pParticleObject = new CGameObject;
	pParticleObject->SetName(L"Particle");
	pParticleObject->AddComponent(new CTransform);
	pParticleObject->AddComponent(new CParticleSystem);
	pParticleObject->Transform()->SetRelativePos(Vec3(-675.f, 0.f, 500.f));
	pParticleObject->ParticleSystem()->SetParticleTexture(CAssetManager::GetInst()->Load<CTexture>(L"texture\\particle\\SmokeParticleTest.png", L"texture\\particle\\SmokeParticleTest.png"));

	Ptr<CPrefab> prefab = new CPrefab(pParticleObject);
	CAssetManager::GetInst()->AddAsset<CPrefab>(L"ParticlePrefab", prefab);

	wstring filePath = CPathManager::GetInst()->GetContentPath();
	prefab->Save(filePath + L"Prefab\\Particle.pref");

	// Missile Prefab
	CGameObject* pNewObj = new CGameObject;
	pNewObj->SetName(L"Missile");
	pNewObj->AddComponent(new CTransform);
	pNewObj->AddComponent(new CMeshRender);
	pNewObj->AddComponent(new CMissileScript);
	pNewObj->Transform()->SetRelativeScale(Vec3(40.f, 40.f, 40.f));
	pNewObj->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pNewObj->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DMaterial"));

	prefab = new CPrefab(pNewObj);
	CAssetManager::GetInst()->AddAsset<CPrefab>(L"MissilePrefab", prefab);
	prefab->Save(filePath + L"Prefab\\Missile.pref");
}
