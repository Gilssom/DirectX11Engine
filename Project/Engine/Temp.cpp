#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"

#include "CAssetManager.h"

#include "CMesh.h"

#include "CConstBuffer.h"
#include "CGraphicShader.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"

CGameObject* pObject1 = nullptr;
CGameObject* pObject2 = nullptr;

#pragma region Graphics Pipeline
// Graphics Pipeline

// ==============================
// IA ( Input Assembler )
// ==============================
// Vertex Buffer
// Index Buffer
// Topology
// LayOut


// ==============================
// ★ Vertex Shader Stage ( 반드시, 무조건 필요한 정보 )
// ==============================
// 정점을 3차원 모델 좌표계에서 NDC 2차원 좌표로 맵핑


// 아래 4개는 있어도 그만, 없어도 그만
// Tessellation
// Hull Shader
// Domain Shader
// Geometry Shader

// ==============================
// Rasterizer Stage ( 기본 세팅이 되어 있음 )
// ==============================

// ==============================
// ★ Pixel Shader ( 있어야 화면에 그려줄 수 있음 )
// ==============================
// 픽셀 당 호출되는 함수
// 각 픽셀의 색상을 지정해서 렌더타겟에 출력


// ==============================
// Output Merge Stage ( 모두 기본 값이 세팅되어 있음 )
// ==============================
// DepthStencil State Check
// BlendState State Check


// 최종 출력
// RenderTarget Texture
// DepthStencil Texture
#pragma endregion

int TempInit()
{
	pObject2 = new CGameObject;
	pObject2->AddComponent(new CTransform);
	pObject2->AddComponent(new CMeshRender);
	//pObject2->AddComponent(new CPlayerScript);

	pObject2->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);

	pObject2->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject2->MeshRender()->SetShader(CAssetManager::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	return S_OK;
}

void TempRelease()
{
	delete pObject1;
	delete pObject2;
}

void TempTick()
{
	pObject1->Tick();
	pObject2->Tick();

	pObject1->FinalTick();
	pObject2->FinalTick();
}

void TempRender()
{
	pObject1->Render();
	pObject2->Render();
}