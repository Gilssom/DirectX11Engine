#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

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

// ���� �ϳ��� �����ϴ� Layout ������ �ʿ���
ComPtr<ID3D11InputLayout> g_Layout;


// System Memory ���� ����
Vtx g_arrVtx[3] = {};


// HLSL ( Shader ������ C++ )

// Vertex Shader
ComPtr<ID3DBlob>		   g_VSBlob; // ������ �� ���̴� �ڵ带 ����
ComPtr<ID3D11VertexShader> g_VS;	 // Vertex Shader

// Pixel Shader
ComPtr<ID3DBlob>		   g_PSBlob;
ComPtr<ID3D11PixelShader>  g_PS;


int TempInit()
{
	// Normalized Device Codination = NDC ��ǥ��
	// �ػ󵵰� ��� ����ȭ�� ���� ��ǥ�踦 ������ �� ����

	g_arrVtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	// ���� Buffer ����
	D3D11_BUFFER_DESC VBdesc = {};

	VBdesc.ByteWidth = sizeof(Vtx) * 3;
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

	// Vertex Shader ����


	// ���� Layout ���� ����
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

	//CDevice::GetInst()->GetDevice()->CreateInputLayout(Layoutdesc, 2, );


	// Pixel Shader

	return S_OK;
}

void TempRelease()
{

}

void TempTick()
{

}

void TempRender()
{

}
