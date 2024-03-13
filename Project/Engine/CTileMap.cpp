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
	// ��ġ ����
	Transform()->Binding();

	// ���� ����
	GetMaterial()->SetTexParam(TEX_0, m_Atlas);
	GetMaterial()->Binding();

	// Mesh Binding �� Rendering
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

	// ��Ʋ�� �ؽ�ó �ȿ��� Ÿ�� 1���� �����ϴ� ũ��
	m_AtlasTileEachSize = tileSize;

	// ��Ʋ�� �ؽ�ó �ػ󵵸� Ÿ�� 1�� ������� ����� 
	// ��Ʋ�� �ؽ�ó�� Ÿ���� ���� ��� �����ϴ��� Ȯ��
	m_AtlasMaxCol = m_Atlas->GetWidth() / m_AtlasTileEachSize.x;
	m_AtlasMaxRow = m_Atlas->GetHeight() / m_AtlasTileEachSize.y;
}