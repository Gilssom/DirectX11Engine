#pragma once
#include "CRenderComponent.h"

#include "CTexture.h"

class CTileMap : public CRenderComponent
{
private:
    UINT            m_Row;          // Tile Row Size
    UINT            m_Col;          // Tile Colum Size
    Vec2            m_TileEachSize; // 각 타일 1개의 크기 (인게임 내의 크기)

    Ptr<CTexture>   m_Atlas;             // Use Atlas Texture
    UINT            m_AtlasMaxRow;       // Atlas Max Row (최대 행 크기)
    UINT            m_AtlasMaxCol;       // Atlas Max Col (최대 열 크기)
    Vec2            m_AtlasTileEachSize; // Atlas Texture 각 타일 1개의 크기

public:
    void SetRowCol(UINT row, UINT col);
    void SetAtlasTexture(Ptr<CTexture> tex);
    void SetAtlasTileSize(Vec2 tileSize);
    void SetTileEachSize(Vec2 size);

public:
    virtual void FinalTick() override;
    virtual void Render() override;


public:
    CTileMap();
    ~CTileMap();
};

