#pragma once
#include "CRenderComponent.h"

struct tTileInfo
{
    UINT    ImageIndex; // ������ ��� Image �� ������ ������
    Vec3    vPadding;
};

class CStructuredBuffer;

class CTileMap : public CRenderComponent
{
private:
    UINT                m_Row;               // Tile Row Size
    UINT                m_Col;               // Tile Colum Size
    Vec2                m_TileEachSize;      // �� Ÿ�� 1���� ũ�� (�ΰ��� ���� ũ��)

    Ptr<CTexture>       m_Atlas;             // Use Atlas Texture
    UINT                m_AtlasMaxRow;       // Atlas Max Row (�ִ� �� ũ��)
    UINT                m_AtlasMaxCol;       // Atlas Max Col (�ִ� �� ũ��)
    Vec2                m_AtlasTileEachSize; // Atlas Texture �� Ÿ�� 1���� ũ��
    Vec2                m_AtlasResolution;   // Atlas Texture �ػ� ����

    vector<tTileInfo>   m_vecTileInfo;
    CStructuredBuffer*  m_TileBuffer;        // ���� ������ ��� (����ȭ ����)

public:
    void SetRowCol(UINT row, UINT col);
    void SetAtlasTexture(Ptr<CTexture> tex);
    void SetAtlasTileSize(Vec2 tileSize);
    void SetTileEachSize(Vec2 size);

public:
    virtual void Begin() override;
    virtual void FinalTick() override;
    virtual void Render() override;


public:
    CTileMap();
    CTileMap(const CTileMap& other);
    ~CTileMap();
};

