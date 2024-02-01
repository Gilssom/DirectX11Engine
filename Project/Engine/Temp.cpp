#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CMesh.h"

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

// Mesh = Vertex + Index
CMesh* g_RectMesh = nullptr;
CMesh* g_CircleMesh = nullptr;

// ��� ���� ( Constant Buffer ) ��ü�� ��ġ, ũ��, ȸ�� ������ �����ϴ� �뵵�� Buffer
ComPtr<ID3D11Buffer> g_CB;

// ���� �ϳ��� �����ϴ� Layout ������ �ʿ���
ComPtr<ID3D11InputLayout> g_Layout;


// System Memory ���� ����
Vtx g_arrVtx[4] = {};


// ��ü�� ��ġ��
Vec3 g_ObjectPos;


// HLSL ( Shader ������ C++ )

// Vertex Shader
ComPtr<ID3DBlob>		   g_VSBlob; // ������ �� ���̴� �ڵ带 ����
ComPtr<ID3D11VertexShader> g_VS;	 // Vertex Shader

// Pixel Shader
ComPtr<ID3DBlob>		   g_PSBlob;
ComPtr<ID3D11PixelShader>  g_PS;

// Error Blob
ComPtr<ID3DBlob>		   g_ErrBlob;

int TempInit()
{
	// Normalized Device Codination = NDC ��ǥ��
	// �ػ󵵰� ��� ����ȭ�� ���� ��ǥ�踦 ������ �� ����

	// �簢�� ����
	// ===============
	// Rect Mesh
	// ===============
	// 0 -- 1
	// |    |
	// 3 -- 2
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
	UINT slice = 10;
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


	// ��ǥ��
	/*
	��� ����
	�ƹ��� ������ ����, �ʸ����� �Ѿ��
	���� ������ ��ȭ �ʿ� ���� ��ǥ ��ȭ���� �����ϸ� �ȴ�.
	*/

	// Constant Buffer ����
	D3D11_BUFFER_DESC CBdesc = {};

	CBdesc.ByteWidth = sizeof(tTransform);
	CBdesc.MiscFlags = 0;

	// ���� �뵵 ����
	CBdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// �ѹ� ������ ���Ŀ� �б�, ���� ���� ( ��ü�� ��ġ�� ���� ���� )
	CBdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CBdesc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&CBdesc, nullptr, g_CB.GetAddressOf())))
	{
		return E_FAIL;
	}



	// Vertex Shader ����
	// ��� ã�� Manager ����
	wstring strPath = CPathManager::GetInst()->GetComtentPath();
	strPath += L"shader\\std2d.fx";

	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_Std2D", "vs_5_0", D3DCOMPILE_DEBUG, 0
		, g_VSBlob.GetAddressOf()
		, g_ErrBlob.GetAddressOf())))
	{
		if (g_ErrBlob != nullptr)
		{
			MessageBoxA(nullptr
				, (char*)g_ErrBlob->GetBufferPointer()
				, "Vertex Shader Compile ����", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"������ ã�� �� �����ϴ�."
				, L"Vertex Shader Compile ����", MB_OK);
		}

		return E_FAIL;
	}

	if (FAILED(DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer()
		, g_VSBlob->GetBufferSize()
		, nullptr, g_VS.GetAddressOf())))
	{
		return E_FAIL;
	}


	// Vertex Layout ���� ����
	D3D11_INPUT_ELEMENT_DESC Layoutdesc[2] = {};

	Layoutdesc[0].AlignedByteOffset = 0; // ���� ������ ���� ��ġ
	Layoutdesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // �׿� �´� �ȼ� ũ��
	Layoutdesc[0].InputSlot = 0; // Vertex Buffer �� ��ġ
	Layoutdesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; // ���� ����
	Layoutdesc[0].InstanceDataStepRate = 0;
	Layoutdesc[0].SemanticName = "POSITION";
	Layoutdesc[0].SemanticIndex = 0;

	Layoutdesc[1].AlignedByteOffset = 12;
	Layoutdesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Layoutdesc[1].InputSlot = 0;
	Layoutdesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Layoutdesc[1].InstanceDataStepRate = 0;
	Layoutdesc[1].SemanticName = "COLOR";
	Layoutdesc[1].SemanticIndex = 0;

	if (FAILED(DEVICE->CreateInputLayout(Layoutdesc, 2, g_VSBlob->GetBufferPointer()
		, g_VSBlob->GetBufferSize()
		, g_Layout.GetAddressOf())))
	{
		return E_FAIL;
	}


	// Pixel Shader
	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Std2D", "ps_5_0", D3DCOMPILE_DEBUG, 0
		, g_PSBlob.GetAddressOf()
		, g_ErrBlob.GetAddressOf())))
	{
		if (g_ErrBlob != nullptr)
		{
			MessageBoxA(nullptr
				, (char*)g_ErrBlob->GetBufferPointer()
				, "Pixel Shader Compile ����", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"������ ã�� �� �����ϴ�."
				, L"Pixel Shader Compile ����", MB_OK);
		}

		return E_FAIL;
	}

	if (FAILED(DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer()
		, g_PSBlob->GetBufferSize()
		, nullptr, g_PS.GetAddressOf())))
	{
		return E_FAIL;
	}


	g_ObjectPos = Vec3(0.f, 0.f, 0.f);

	return S_OK;
}

void TempRelease()
{
	if (g_RectMesh != nullptr)
		delete g_RectMesh;

	if (g_CircleMesh != nullptr)
		delete g_CircleMesh;
}

void TempTick()
{
	// �ð� ����ȭ ó��
	float DT = CTimeManager::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		g_ObjectPos.y += DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		g_ObjectPos.y -= DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		g_ObjectPos.x -= DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		g_ObjectPos.x += DT;
	}

	// System Memory -> GPU
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	// ������ ����
	CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	tTransform trans = {};
	trans.Position = g_ObjectPos;

	// ������ �ֱ�
	memcpy(tSub.pData, &trans, sizeof(tTransform));

	// ������ ���� �Ϸ�
	CONTEXT->Unmap(g_CB.Get(), 0);

	// ��� -> std2d.fx - b0 �� ������ ����
	CONTEXT->VSGetConstantBuffers(/* register ��ȣ = */ 0, 1, g_CB.GetAddressOf());
}

void TempRender()
{
	// ������ ������ ���� �ܰ迡 ���� ���� �� �ʿ�� ����.
	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // ������ ������ �˷��ִ� �Լ�

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	//g_RectMesh->Render();
	g_CircleMesh->Render();
}