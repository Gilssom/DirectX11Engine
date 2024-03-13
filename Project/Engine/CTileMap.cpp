#include "pch.h"
#include "CTileMap.h"

#include "CAssetManager.h"

#include "CTransform.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_Row(1)
	, m_Col(1)
	, m_TileEachSize(Vec2(32.f, 32.f))
{
	SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"TileMapMaterial"));
}

CTileMap::~CTileMap()
{

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
	GetMaterial()->Binding();

	// Mesh Binding 및 Rendering
	GetMesh()->Render();
}

void CTileMap::SetRowCol(UINT row, UINT col)
{
	m_Row = row;
	m_Col = col;

	Transform()->SetRelativePos(Vec3(m_TileEachSize.x * m_Col, m_TileEachSize.y * m_Row, 1.f));
}

void CTileMap::SetTileEachSize(Vec2 size)
{
	m_TileEachSize = size;

	Transform()->SetRelativePos(Vec3(m_TileEachSize.x * m_Col, m_TileEachSize.y * m_Row, 1.f));
}

void CTileMap::SetAtlasTexture(Ptr<CTexture> tex)
{
	m_Atlas = tex;
}

void CTileMap::SetAtlasTileSize(Vec2 tileSize)
{
	assert(m_Atlas.Get());

	// 아틀라스 텍스처 안에서 타일 1개가 차지하는 크기
	m_AtlasTileEachSize = tileSize;

	// 아틀라스 텍스처 해상도를 타일 1개 사이즈로 나누어서 
	// 아틀라스 텍스처에 타일이 몇행 몇열에 존재하는지 확인
	m_AtlasMaxCol = m_Atlas->GetWidth() / m_AtlasTileEachSize.x;
	m_AtlasMaxRow = m_Atlas->GetHeight() / m_AtlasTileEachSize.y;
}