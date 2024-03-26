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
#include "CBackGroundScript.h"

#include "CCollisionManager.h"
#include "CSetColorCS.h"

#include "CStructuredBuffer.h"

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
	//// Texture 생성하기
	//Ptr<CTexture> pTestTex = 
	//	CAssetManager::GetInst()->CreateTexture(L"TestTex"
	//										, 1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM
	//										, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
	//
	//// Compute Shader Test
	//Ptr<CSetColorShader> pCS = (CSetColorShader*)CAssetManager::GetInst()->FindAsset<CComputeShader>(L"SetColorCS").Get();
	//pCS->SetTargetTextrue(pTestTex);
	//pCS->SetClearColor(Vec3(0.f, 0.f, 1.f));
	//pCS->Execute();


	//// 구조화버퍼 데이터 이동 테스트
	//CStructuredBuffer* pTestBuffer = new CStructuredBuffer;

	//// Buffer 총 3개 생성
	//pTestBuffer->Create(sizeof(tParticle), 1, SB_TYPE::SRV_UAV, true, nullptr);

	//// 0번 particle 에 정보 기입 후 테스트용 구조화 버퍼로 데이터 이동
	//tParticle particle = {};
	//particle.Life = 10.f;
	//particle.vWorldPos = Vec3(100.f, 100.f, 100.f);
	//pTestBuffer->SetData(&particle);

	//// 테스트용 구조화 버퍼의 데이터를 1번 particle 로 데이터 복사
	//tParticle particle1 = {};
	//pTestBuffer->GetData(&particle1);

	//delete pTestBuffer;


	// Level
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


	// Light Object
	CGameObject* pLightObject = new CGameObject;
	pLightObject->SetName(L"Directinal Light");
	pLightObject->AddComponent(new CTransform);
	pLightObject->AddComponent(new CLight2D);

	pLightObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));

	pLightObject->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObject->Light2D()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
	pLightObject->Light2D()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));

	/*pLightObject->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObject->Light2D()->SetDiffuse(Vec3(0.8f, 0.2f, 0.2f));
	pLightObject->Light2D()->SetAmbient(Vec3(0.f, 0.f, 0.f));
	pLightObject->Light2D()->SetRange(400.f);*/

	m_CurLevel->AddObject(0, pLightObject);


	// TileMap Object
	/*CGameObject* pTileMapObj = new CGameObject;
	pTileMapObj->SetName(L"TileMap");
	pTileMapObj->AddComponent(new CTransform);
	pTileMapObj->AddComponent(new CTileMap);

	pTileMapObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

	pTileMapObj->TileMap()->SetAtlasTexture(CAssetManager::GetInst()->Load<CTexture>(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));
	pTileMapObj->TileMap()->SetAtlasTileSize(Vec2(64.f, 64.f));
	pTileMapObj->TileMap()->SetTileEachSize(Vec2(64.f, 64.f));
	pTileMapObj->TileMap()->SetRowCol(4, 4);

	m_CurLevel->AddObject(0, pTileMapObj);*/


	// Player
	/*CGameObject* pPlayer = new CGameObject;
	//pPlayer->SetName(L"Player");
	//pPlayer->AddComponent(new CTransform);
	//pPlayer->AddComponent(new CMeshRender);
	//pPlayer->AddComponent(new CCollider2D);
	//pPlayer->AddComponent(new CAnimator2D);
	//pPlayer->AddComponent(new CPlayerScript);

	//pPlayer->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	//pPlayer->Transform()->SetRelativeScale(100.f, 100.f, 0.2f);

	//pPlayer->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pPlayer->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DMaterial"));
	//pPlayer->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetManager::GetInst()->FindAsset<CTexture>(L"texture\\Character.png"));

	//pPlayer->Collider2D()->SetAbsolute(false);
	//pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pPlayer->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	//Ptr<CTexture> pAtlas = CAssetManager::GetInst()->Load<CTexture>(L"texture\\link.png", L"texture\\link.png");
	////pPlayer->Animator2D()->CreateAnimation(L"MOVE_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(240.f, 260.f), 10, 16);
	////pPlayer->Animator2D()->CreateAnimation(L"IDLE_RIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(240.f, 260.f), 3, 2);
	////pPlayer->Animator2D()->FindAnimation(L"MOVE_DOWN")->Save(L"Animation\\");

	//pPlayer->Animator2D()->LoadAnimation(L"Animation\\MOVE_DOWN.anim");
	//pPlayer->Animator2D()->Play(L"MOVE_DOWN", true);

	//m_CurLevel->AddObject(1, pPlayer, false);*/


	// Monster
	/*CGameObject* pMonster = new CGameObject;
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

	pMonster->GetRenderComponent()->GetMaterial()->SetTexParam(TEX_0, pTestTex);


	// Player 와 Monster 를 부모-자식 관계로 연결
	//pPlayer->AddChild(pMonster);
	m_CurLevel->AddObject(1, pMonster, false);*/

	//pPlayer->GetScript<CPlayerScript>()->SetTarget(pMonster);


	// Back Ground Object
	CGameObject* pBackGround = new CGameObject;
	pBackGround->AddComponent(new CTransform);
	pBackGround->AddComponent(new CMeshRender);
	pBackGround->AddComponent(new CBackGroundScript);

	pBackGround->Transform()->SetRelativePos(Vec3(0.f, 0.f, 1000.f));
	pBackGround->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 1.f));

	pBackGround->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pBackGround->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"BackGroundMaterial"));
	pBackGround->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetManager::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg"));
	pBackGround->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CAssetManager::GetInst()->Load<CTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg"));

	m_CurLevel->AddObject(0, pBackGround, false);


	// Particle Object
	CGameObject* pParticleObject = new CGameObject;
	pParticleObject->SetName(L"Particle");
	pParticleObject->AddComponent(new CTransform);
	pParticleObject->AddComponent(new CParticleSystem);

	pParticleObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pParticleObject->ParticleSystem()->SetParticleTexture(CAssetManager::GetInst()->Load<CTexture>(L"texture\\particle\\AlphaCircle.png", L"texture\\particle\\AlphaCircle.png"));

	m_CurLevel->AddObject(0, pParticleObject, false);


	// Level 의 Collision Setting
	CCollisionManager::GetInst()->LayerCheck(1, 1);
	CCollisionManager::GetInst()->LayerCheck(1, 2);

	// 레벨 시작
	m_CurLevel->Init();
}

void CLevelManager::Tick()
{
	if (m_CurLevel != nullptr)
	{
		m_CurLevel->Tick(); 
		m_CurLevel->FinalTick();
	}
}
