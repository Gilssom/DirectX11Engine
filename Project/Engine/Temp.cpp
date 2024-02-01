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

// Mesh = Vertex + Index
CMesh* g_RectMesh = nullptr;
CMesh* g_CircleMesh = nullptr;

// 상수 버퍼 ( Constant Buffer ) 물체의 위치, 크기, 회전 정보를 전달하는 용도의 Buffer
ComPtr<ID3D11Buffer> g_CB;

// 정점 하나를 구성하는 Layout 정보가 필요함
ComPtr<ID3D11InputLayout> g_Layout;


// System Memory 정점 정보
Vtx g_arrVtx[4] = {};


// 물체의 위치값
Vec3 g_ObjectPos;


// HLSL ( Shader 버전의 C++ )

// Vertex Shader
ComPtr<ID3DBlob>		   g_VSBlob; // 컴파일 한 쉐이더 코드를 저장
ComPtr<ID3D11VertexShader> g_VS;	 // Vertex Shader

// Pixel Shader
ComPtr<ID3DBlob>		   g_PSBlob;
ComPtr<ID3D11PixelShader>  g_PS;

// Error Blob
ComPtr<ID3DBlob>		   g_ErrBlob;

int TempInit()
{
	// Normalized Device Codination = NDC 좌표계
	// 해상도가 어떻든 정규화를 통해 좌표계를 설정할 수 있음

	// 사각형 정점
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
	UINT slice = 10;
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


	// 좌표계
	/*
	상수 버퍼
	아무리 정점이 만개, 십만개가 넘어가도
	원본 정점의 변화 필요 없이 좌표 변화량만 전달하면 된다.
	*/

	// Constant Buffer 생성
	D3D11_BUFFER_DESC CBdesc = {};

	CBdesc.ByteWidth = sizeof(tTransform);
	CBdesc.MiscFlags = 0;

	// 버퍼 용도 설정
	CBdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 한번 생성한 이후에 읽기, 쓰기 가능 ( 물체의 위치값 전달 위해 )
	CBdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CBdesc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&CBdesc, nullptr, g_CB.GetAddressOf())))
	{
		return E_FAIL;
	}



	// Vertex Shader 생성
	// 경로 찾기 Manager 구현
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
				, "Vertex Shader Compile 오류", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"파일을 찾을 수 없습니다."
				, L"Vertex Shader Compile 오류", MB_OK);
		}

		return E_FAIL;
	}

	if (FAILED(DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer()
		, g_VSBlob->GetBufferSize()
		, nullptr, g_VS.GetAddressOf())))
	{
		return E_FAIL;
	}


	// Vertex Layout 정보 생성
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
				, "Pixel Shader Compile 오류", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"파일을 찾을 수 없습니다."
				, L"Pixel Shader Compile 오류", MB_OK);
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
	// 시간 동기화 처리
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
	// 데이터 수정
	CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	tTransform trans = {};
	trans.Position = g_ObjectPos;

	// 데이터 넣기
	memcpy(tSub.pData, &trans, sizeof(tTransform));

	// 데이터 수정 완료
	CONTEXT->Unmap(g_CB.Get(), 0);

	// 상수 -> std2d.fx - b0 에 데이터 복사
	CONTEXT->VSGetConstantBuffers(/* register 번호 = */ 0, 1, g_CB.GetAddressOf());
}

void TempRender()
{
	// 세팅은 파이프 라인 단계에 따라서 맞춰 줄 필요는 없다.
	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 도형의 구조를 알려주는 함수

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	//g_RectMesh->Render();
	g_CircleMesh->Render();
}