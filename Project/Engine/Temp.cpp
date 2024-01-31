#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"

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

// ���� ������ �����ϴ� Buffer
ComPtr<ID3D11Buffer> g_VB;

// Vertex Buffer ������ ����� ������ ����Ű�� �ε��� ������ �����ϴ� Buffer
ComPtr<ID3D11Buffer> g_IB;

// ��� ���� ( Constant Buffer ) ��ü�� ��ġ, ũ��, ȸ�� ������ �����ϴ� �뵵�� Buffer
ComPtr<ID3D11Buffer> g_CB;

// ���� �ϳ��� �����ϴ� Layout ������ �ʿ���
ComPtr<ID3D11InputLayout> g_Layout;


// System Memory ���� ����
Vtx g_arrVtx[4] = {};


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

	// = �簢�� �ϼ�

	// ���� Buffer ����
	D3D11_BUFFER_DESC VBdesc = {};

	VBdesc.ByteWidth = sizeof(Vtx) * 4;
	VBdesc.MiscFlags = 0;

	// Buffer �� �뵵�� ����
	VBdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// ���۰� ������ ���Ŀ� CPU ���� �����ؼ� GPU �� �ִ� �����͸�
	// ����Ⱑ �����ϰ� ����
	VBdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VBdesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA Subdesc = {};
	Subdesc.pSysMem = g_arrVtx;

	// define.h -> #define
	if (FAILED(DEVICE->CreateBuffer(&VBdesc, &Subdesc, g_VB.GetAddressOf())))
	{
		return E_FAIL;
	}


	// Index Buffer ����
	UINT arrIdx[6] = {0, 2, 3, 0, 1, 2};

	D3D11_BUFFER_DESC IBdesc = {};

	IBdesc.ByteWidth = sizeof(Vtx) * 6;
	IBdesc.MiscFlags = 0;

	// ���� �뵵 ����
	IBdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// �ѹ� ������ ���Ŀ� �б�, ���� �Ұ���
	IBdesc.CPUAccessFlags = 0;
	IBdesc.Usage = D3D11_USAGE_DEFAULT;

	Subdesc = {};
	Subdesc.pSysMem = arrIdx;

	if (FAILED(DEVICE->CreateBuffer(&IBdesc, &Subdesc, g_IB.GetAddressOf())))
	{
		return E_FAIL;
	}


	// Constant Buffer ����



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

	return S_OK;
}

void TempRelease()
{

}

void TempTick()
{
	// �ð� ����ȭ ó��
	float DT = CTimeManager::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		for (int i = 0; i < 4; i++)
		{
			g_arrVtx[i].vPos.y += DT;
		}
	}

	if (KEY_PRESSED(KEY::S))
	{
		for (int i = 0; i < 4; i++)
		{
			g_arrVtx[i].vPos.y -= DT;
		}
	}

	if (KEY_PRESSED(KEY::A))
	{
		for (int i = 0; i < 4; i++)
		{
			g_arrVtx[i].vPos.x -= DT;
		}
	}

	if (KEY_PRESSED(KEY::D))
	{
		for (int i = 0; i < 4; i++)
		{
			g_arrVtx[i].vPos.x += DT;
		}
	}

	// System Memory -> GPU
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	// ������ ����
	CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	// ������ �ֱ�
	memcpy(tSub.pData, g_arrVtx, sizeof(Vtx) * 4);

	// ������ ���� �Ϸ�
	CONTEXT->Unmap(g_VB.Get(), 0);
}

void TempRender()
{
	// ������ ������ ���� �ܰ迡 ���� ���� �� �ʿ�� ����.

	UINT stride = sizeof(Vtx); // �� ���� �� ����
	UINT offset = 0; // �������� ���� �� ���� ��ġ
	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &stride, &offset);

	// �簢���� �׸� �� �Ȱ��� ������ ������ ���� ���� �� �ۿ� ���µ�
	// �� �κ��� �޸𸮸� ��� ���� �� �ִ�.
	// �̰� �ذ��ϱ� ���ؼ� Index Buffer �� ����ϸ� �ȴ�.
	// Vertex Buffer �� �� 4���� ������ ���� �ǰ�,
	// Index Buffer �� �� 6���� Vertex Buffer �� ����Ű�� ���� ������ �ȴ�.
	CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);

	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // ������ ������ �˷��ִ� �Լ�

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	// �簢���� ������ 6�� ( �ﰢ�� �� ���� 3�� )
	//CONTEXT->Draw(6, 0);
	// Index Buffer �� ������ŭ �������� �ؾ� �Ѵ�. ( Vertex Buffer X )
	CONTEXT->DrawIndexed(6, 0, 0);
}

// ��ǥ��
/*
��� ����
�ƹ��� ������ ����, �ʸ����� �Ѿ��
���� ������ ��ȭ �ʿ� ���� ��ǥ ��ȭ���� �����ϸ� �ȴ�.
*/