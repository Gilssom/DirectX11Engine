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

// ��ü�� ��ġ, ũ��, ȸ��
tTransform g_Trans = {};


int TempInit()
{
	// Normalized Device Codination = NDC ��ǥ��
	// �ػ󵵰� ��� ����ȭ�� ���� ��ǥ�踦 ������ �� ����
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
	Ptr<CGraphicShader> pShader = CAssetManager::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader");
	pShader->Binding();

	Ptr<CMesh> pMesh = CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh");
	pMesh->Render();
}