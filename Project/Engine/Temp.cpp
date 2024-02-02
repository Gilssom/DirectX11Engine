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
// �� Vertex Shader Stage ( �ݵ��, ������ �ʿ��� ���� )
// ==============================
// ������ 3���� �� ��ǥ�迡�� NDC 2���� ��ǥ�� ����


// �Ʒ� 4���� �־ �׸�, ��� �׸�
// Tessellation
// Hull Shader
// Domain Shader
// Geometry Shader

// ==============================
// Rasterizer Stage ( �⺻ ������ �Ǿ� ���� )
// ==============================

// ==============================
// �� Pixel Shader ( �־�� ȭ�鿡 �׷��� �� ���� )
// ==============================
// �ȼ� �� ȣ��Ǵ� �Լ�
// �� �ȼ��� ������ �����ؼ� ����Ÿ�ٿ� ���


// ==============================
// Output Merge Stage ( ��� �⺻ ���� ���õǾ� ���� )
// ==============================
// DepthStencil State Check
// BlendState State Check


// ���� ���
// RenderTarget Texture
// DepthStencil Texture
#pragma endregion

// Mesh = Vertex + Index
// ������ ���� �ʱ�ȭ
Ptr<CMesh> g_RectMesh = nullptr;
Ptr<CMesh> g_CircleMesh = nullptr;

// System Memory ���� ����
Vtx g_arrVtx[4] = {};

// ��ü�� ��ġ, ũ��, ȸ��
tTransform g_Trans = {};

// HLSL ( Shader ������ C++ )
// Vertex Shader + Pixel Shader
Ptr<CGraphicShader> g_Shader = nullptr;


int TempInit()
{
	// Normalized Device Codination = NDC ��ǥ��
	// �ػ󵵰� ��� ����ȭ�� ���� ��ǥ�踦 ������ �� ����

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
	// = �簢�� �ϼ�

	// Rect Mesh ����
	g_RectMesh = new CMesh;
	g_RectMesh->Create(g_arrVtx, 4, arrIdx, 6);

	// ===============
	// Circle Mesh
	// ===============
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	// ������ vector �� �ִ´�.
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	float radius = 0.5f;
	UINT slice = 60;
	float angleStep = (2 * XM_PI) / slice; // �� ������ ����

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

	// ��� ã�� Manager ����
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
	// �ð� ����ȭ ó��
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
	// ������ ������ ���� �ܰ迡 ���� ���� �� �ʿ�� ����.
	g_Shader->Binding();

	//g_RectMesh->Render();
	g_CircleMesh->Render();
}