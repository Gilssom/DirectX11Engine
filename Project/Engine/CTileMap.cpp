#include "pch.h"
#include "CTileMap.h"

#include "CAssetManager.h"
#include "components.h"

#include "CStructuredBuffer.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_Row(1)
	, m_Col(1)
	, m_AtlasMaxRow(0)
	, m_AtlasMaxCol(0)
	, m_TileEachSize(Vec2(32.f, 32.f))
{
	SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"TileMapMaterial"));

	m_TileBuffer = new CStructuredBuffer;
}

CTileMap::CTileMap(const CTileMap& other)
	: CRenderComponent(other)
	, m_Row(other.m_Row)
	, m_Col(other.m_Col)
	, m_TileEachSize(other.m_TileEachSize)
	, m_Atlas(other.m_Atlas)
	, m_AtlasMaxRow(other.m_AtlasMaxRow)
	, m_AtlasMaxCol(other.m_AtlasMaxCol)
	, m_AtlasTileEachSize(other.m_AtlasTileEachSize)
	, m_AtlasResolution(other.m_AtlasResolution)
	, m_vecTileInfo(other.m_vecTileInfo)
	, m_TileBuffer(nullptr)
{
	m_TileBuffer = new CStructuredBuffer;
	m_TileBuffer->Create(sizeof(tTileInfo), m_vecTileInfo.size(), SB_TYPE::SRV_ONLY, true, m_vecTileInfo.data());

	// 복사 생성자를 구현 함으로써 해당 생성자를 사용하여 원본 Buffer 를 복제
	// (딱히 GPU 간의 연산을 할 필요가 없기 때문에 효율성을 위해 위의 코드를 사용)
	//m_TileBuffer = new CStructuredBuffer(*other.m_TileBuffer);
}

CTileMap::~CTileMap()
{
	delete m_TileBuffer;
}

void CTileMap::Begin()
{
	SetRowCol(m_Row, m_Col);
}

void CTileMap::FinalTick()
{

}

void CTileMap::Render()
{
	// 위치 정보
	Transform()->Binding();

	// 재질 정보
	GetMaterial()->SetTexParam(TEX_0, m_Atlas);
	GetMaterial()->SetScalarParam(VEC2_0, m_AtlasResolution);
	GetMaterial()->SetScalarParam(VEC2_1, m_AtlasTileEachSize);
	GetMaterial()->SetScalarParam(VEC2_2, Vec2(m_Col, m_Row));
	GetMaterial()->SetScalarParam(INT_0, m_AtlasMaxRow);
	GetMaterial()->SetScalarParam(INT_1, m_AtlasMaxCol);
	GetMaterial()->SetScalarParam(INT_2, 0);
	GetMaterial()->Binding();

	// Tile Info Binding
	if (m_TileBuffer->GetElementCount() < m_vecTileInfo.size())
		m_TileBuffer->Create(sizeof(tTileInfo), m_vecTileInfo.size(), SB_TYPE::SRV_ONLY, true, m_vecTileInfo.data());
	else
		m_TileBuffer->SetData(m_vecTileInfo.data(), m_vecTileInfo.size());

	m_TileBuffer->Binding(20);

	// Mesh Binding 및 Rendering
	GetMesh()->Render();
}

void CTileMap::SetRowCol(UINT row, UINT col)
{
	m_Row = row;
	m_Col = col;

	Transform()->SetRelativeScale(Vec3(m_TileEachSize.x * m_Col, m_TileEachSize.y * m_Row, 1.f));

	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);

	for (int i = 0; i < m_vecTileInfo.size(); i++)
	{
		m_vecTileInfo[i].ImageIndex = i % (m_AtlasMaxRow * m_AtlasMaxCol);
		//m_vecTileInfo[i].ImageIndex = 10;
	}
}

void CTileMap::SetTileEachSize(Vec2 size)
{
	m_TileEachSize = size;

	Transform()->SetRelativeScale(Vec3(m_TileEachSize.x * m_Col, m_TileEachSize.y * m_Row, 1.f));
}

void CTileMap::SetAtlasTexture(Ptr<CTexture> tex)
{
	m_Atlas = tex;

	if(m_Atlas != nullptr)
		m_AtlasResolution = Vec2(m_Atlas->GetWidth(), m_Atlas->GetHeight());
}

void CTileMap::SetAtlasTileSize(Vec2 tileSize)
{
	assert(m_Atlas.Get());

	// 아틀라스 텍스처 안에서 타일 1개가 차지하는 크기
	m_AtlasTileEachSize = tileSize;

	// 아틀라스 텍스처 해상도를 타일 1개 사이즈로 나누어서 
	// 아틀라스 텍스처에 타일이 몇행 몇열 존재하는지 확인
	m_AtlasMaxCol = m_Atlas->GetWidth() / m_AtlasTileEachSize.x;
	m_AtlasMaxRow = m_Atlas->GetHeight() / m_AtlasTileEachSize.y;
}

void CTileMap::SaveToLevelFile(FILE* file)
{
	CRenderComponent::SaveToLevelFile(file);

	fwrite(&m_Row, sizeof(UINT), 1, file);
	fwrite(&m_Col, sizeof(UINT), 1, file);
	fwrite(&m_TileEachSize, sizeof(Vec2), 1, file);

	SaveAssetRef(m_Atlas, file);

	fwrite(&m_AtlasTileEachSize, sizeof(Vec2), 1, file);

	size_t i = m_vecTileInfo.size();
	fwrite(&i, sizeof(size_t), 1, file);

	for (size_t i = 0; i < m_vecTileInfo.size(); i++)
	{
		fwrite(&m_vecTileInfo[i], sizeof(tTileInfo), 1, file);
	}
}

void CTileMap::LoadFromLevelFile(FILE* file)
{
	CRenderComponent::LoadFromLevelFile(file);

	fread(&m_Row, sizeof(UINT), 1, file);
	fread(&m_Col, sizeof(UINT), 1, file);
	fread(&m_TileEachSize, sizeof(Vec2), 1, file);
	SetRowCol(m_Row, m_Col);

	LoadAssetRef(m_Atlas, file);
	SetAtlasTexture(m_Atlas);

	fread(&m_AtlasTileEachSize, sizeof(Vec2), 1, file);
	SetTileEachSize(m_AtlasTileEachSize);

	size_t vecSize = 0;
	fread(&vecSize, sizeof(size_t), 1, file);

	for (size_t i = 0; i < vecSize; i++)
	{
		tTileInfo info = {};
		fread(&info, sizeof(tTileInfo), 1, file);
		m_vecTileInfo.push_back(info);
	}
}