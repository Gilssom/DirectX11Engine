#include "pch.h"
#include "CAssetManager.h"

#include "CPathManager.h"

void CAssetManager::Init()
{
	CreateDefaultMesh();

	CreateDefaultTexture();

	CreateDefaultGraphicShader();

	CreateDefaultComputeShader();

	CreateDefaultMaterial();
}

void CAssetManager::CreateDefaultMesh()
{
	Ptr<CMesh> pMesh = nullptr;

	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	// ===============
	// Rect Mesh
	// ===============
	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUv = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUv = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUv = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUv = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	// = 사각형 완성

	// Rect Mesh 생성
	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"RectMesh", pMesh);
	vecIdx.clear();

	// Debug Mesh Rect
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);
	vecIdx.push_back(3);
	vecIdx.push_back(0);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"RectMesh_Debug", pMesh);
	vecVtx.clear();
	vecIdx.clear();

	// ===============
	// Circle Mesh
	// ===============
	//vector<Vtx> vecVtx;
	//vector<UINT> vecIdx;
	//Vtx v;

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

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"CircleMesh", pMesh);
	vecIdx.clear();

	// Debug Circle Mesh
	for (int i = 0; i <= slice; ++i)
	{
		vecIdx.push_back(i + 1);
	}

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"CircleMesh_Debug", pMesh);
	vecVtx.clear();
	vecIdx.clear();
}

void CAssetManager::CreateDefaultTexture()
{
	Load<CTexture>(L"texture\\Character.png", L"texture\\Character.png");
}

void CAssetManager::CreateDefaultGraphicShader()
{
	// 경로 찾기 Manager 구현
	wstring strPath = CPathManager::GetInst()->GetContentPath();

	Ptr<CGraphicShader> pShader = nullptr;

	// ================
	//	Std 2D Shader
	// ================
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(strPath + L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(strPath + L"shader\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE); // 2D 에서는 전면 후면 개념이 딱히 필요 없기 때문에 None

	AddAsset<CGraphicShader>(L"Std2DShader", pShader);

	// ====================
	//	Debug Shape Shader
	// ====================
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(strPath + L"shader\\debug_shape.fx", "VS_DebugShape");
	pShader->CreatePixelShader(strPath + L"shader\\debug_shape.fx", "PS_DebugShape");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	AddAsset<CGraphicShader>(L"DebugShapeShader", pShader);
}

void CAssetManager::CreateDefaultComputeShader()
{

}

void CAssetManager::CreateDefaultMaterial()
{
	Ptr<CMaterial> pMaterial = nullptr;

	// Std 2D Material
	pMaterial = new CMaterial;
	pMaterial->SetName(L"Std2DMaterial");
	pMaterial->SetShader(FindAsset<CGraphicShader>(L"Std2DShader"));

	AddAsset<CMaterial>(pMaterial->GetName(), pMaterial);

	// Debug Shape Material
	pMaterial = new CMaterial;
	pMaterial->SetName(L"DebugShapeMaterial");
	pMaterial->SetShader(FindAsset<CGraphicShader>(L"DebugShapeShader"));

	AddAsset<CMaterial>(pMaterial->GetName(), pMaterial);
}