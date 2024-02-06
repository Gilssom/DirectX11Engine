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

// 물체의 위치, 크기, 회전
tTransform g_Trans = {};


int TempInit()
{
	// Normalized Device Codination = NDC 좌표계
	// 해상도가 어떻든 정규화를 통해 좌표계를 설정할 수 있음
	return S_OK;
}

void TempRelease()
{
	/*if (g_RectMesh != nullptr)
		delete g_RectMesh;

	if (g_CircleMesh != nullptr)
		delete g_CircleMesh;

	if (g_Shader != nullptr)
		delete g_Shader;*/
}

void TempTick()
{
	// 시간 동기화 처리
	float DT = CTimeManager::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		g_Trans.Position.y += DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		g_Trans.Position.y -= DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		g_Trans.Position.x -= DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		g_Trans.Position.x += DT;
	}

	// System Memory -> GPU
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Trans);
	pCB->Binding();
}

void TempRender()
{
	// 세팅은 파이프 라인 단계에 따라서 맞춰 줄 필요는 없다.
	Ptr<CGraphicShader> pShader = CAssetManager::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader");
	pShader->Binding();

	Ptr<CMesh> pMesh = CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh");
	pMesh->Render();
}