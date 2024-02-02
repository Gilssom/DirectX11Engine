#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"

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

// Mesh = Vertex + Index
// 생성과 동시 초기화
Ptr<CMesh> g_RectMesh = nullptr;
Ptr<CMesh> g_CircleMesh = nullptr;

// System Memory 정점 정보
Vtx g_arrVtx[4] = {};

// 물체의 위치, 크기, 회전
tTransform g_Trans = {};

// HLSL ( Shader 버전의 C++ )
// Vertex Shader + Pixel Shader
Ptr<CGraphicShader> g_Shader = nullptr;


int TempInit()
{
	// Normalized Device Codination = NDC 좌표계
	// 해상도가 어떻든 정규화를 통해 좌표계를 설정할 수 있음

	// ===============
	// Rect Mesh
	// ===============
	g_arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	g_arrVtx[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	UINT arrIdx[6] = { 0, 2, 3, 0, 1, 2 };
	// = 사각형 완성

	// Rect Mesh 생성
	g_RectMesh = new CMesh;
	g_RectMesh->Create(g_arrVtx, 4, arrIdx, 6);

	// ===============
	// Circle Mesh
	// ===============
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	// 원점을 vector 에 넣는다.
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	float radius = 0.5f;
	UINT slice = 60;
	float angleStep = (2 * XM_PI) / slice; // 한 조각의 각도

	float angle = 0.f;
	for (UINT i = 0; i <= slice; ++i)
	{
		v.vPos = Vec3(cosf(angle) * radius, sinf(angle) * radius, 0.f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v);

		angle += angleStep;
	}

	for (UINT i = 0; i < slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	g_CircleMesh = new CMesh;
	g_CircleMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());

	// 경로 찾기 Manager 구현
	wstring strPath = CPathManager::GetInst()->GetComtentPath();
	strPath += L"shader\\std2d.fx";

	// Create Shader
	g_Shader = new CGraphicShader;
	g_Shader->CreateVertexShader(strPath, "VS_Std2D");
	g_Shader->CreatePixelShader	(strPath, "PS_Std2D");

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
	g_Shader->Binding();

	//g_RectMesh->Render();
	g_CircleMesh->Render();
}