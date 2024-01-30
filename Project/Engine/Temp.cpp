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


// 정점 정보를 저장하는 Buffer
ComPtr<ID3D11Buffer> g_VB;

// 정점 하나를 구성하는 Layout 정보가 필요함
ComPtr<ID3D11InputLayout> g_Layout;


// System Memory 정점 정보
Vtx g_arrVtx[3] = {};


// HLSL ( Shader 버전의 C++ )

// Vertex Shader
ComPtr<ID3DBlob>		   g_VSBlob; // 컴파일 한 쉐이더 코드를 저장
ComPtr<ID3D11VertexShader> g_VS;	 // Vertex Shader

// Pixel Shader
ComPtr<ID3DBlob>		   g_PSBlob;
ComPtr<ID3D11PixelShader>  g_PS;


int TempInit()
{
	// Normalized Device Codination = NDC 좌표계
	// 해상도가 어떻든 정규화를 통해 좌표계를 설정할 수 있음

	g_arrVtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	// 정점 Buffer 생성
	D3D11_BUFFER_DESC VBdesc = {};

	VBdesc.ByteWidth = sizeof(Vtx) * 3;
	VBdesc.MiscFlags = 0;

	// Buffer 의 용도를 지정
	VBdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// 버퍼가 생성된 이후에 CPU 에서 접근해서 GPU 에 있는 데이터를
	// 덮어쓰기가 가능하게 설정
	VBdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VBdesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA Subdesc = {};
	Subdesc.pSysMem = g_arrVtx;

	// define.h -> #define
	if (FAILED(DEVICE->CreateBuffer(&VBdesc, &Subdesc, g_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// Vertex Shader 생성


	// 정점 Layout 정보 생성
	D3D11_INPUT_ELEMENT_DESC Layoutdesc[2] = {};

	Layoutdesc[0].AlignedByteOffset = 0; // 정점 정보의 시작 위치
	Layoutdesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // 그에 맞는 픽셀 크기
	Layoutdesc[0].InputSlot = 0; // Vertex Buffer 의 위치
	Layoutdesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; // 정점 정보
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
