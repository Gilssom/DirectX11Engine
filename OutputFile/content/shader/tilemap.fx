#ifndef _TILEMAP
#define _TILEMAP

#include "value.fx"

struct tTileInfo
{
    uint ImageIndex;
    float3 vPadding;
};

struct VS_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

// =================================
//  Tile Map Shader
//  Parameter
    #define AtlasMaxRow         g_int_0
    #define AtlasMaxCol         g_int_1
    #define TileImageIndex      g_int_2
    #define AtlasResolution     g_vec2_0
    #define AtlasTileSize       g_vec2_1
    #define TileColRow          g_vec2_2
StructuredBuffer<tTileInfo> g_TileInfo : register(t20);
// ==================================

VS_OUT VS_TileMap(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    _in.vLocalPos.xy += float2(0.5f, -0.5f);

    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_TileMap(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    // 1. 입력된 UV (0 ~ 1 사이) 를 실제 타일 행렬 개수에 맞추어 확장한다.
    _in.vUV *= TileColRow;
    
    // 2. 확장시킨 UV 에서 해당 픽셀 Shader 의 타일 상에서의 위치값을 행렬로 알아낼 수 있다. ex) (2.8, 2.8) => 2행 2열
    int2 PixelColRowIndex = (int2)_in.vUV;
    
    // 3. 확장시킨 UV 에서 소수점만 취한다. 해당 픽셀이 해당 칸 내에서 어느 위치인지 알 수 있다.
    _in.vUV = _in.vUV - floor(_in.vUV);
    
    // 4. Atlas Texture 상에서 하나의 타일 이미지가 차지하는 크기를 UV 단위로 구한다.
    float2 TileSizeUV = AtlasTileSize / AtlasResolution;
    
    // 5. 해당 픽셀이 참조해야 하는 타일 좌상단에서 참조할 UV 좌표를 구한다.
    float2 vUV = TileSizeUV * _in.vUV;
    
    // 6. 픽셀이 위치하고 있는 타일이 누군지 알아내서, 그 타일의 Image Index 정보를 구조화버퍼에서 꺼낸다.
    int ImgIndex = g_TileInfo[PixelColRowIndex.y * TileColRow.x + PixelColRowIndex.x].ImageIndex;
    
    // 7. Atlas 상에서 내가 참조하려는 타일의 좌상단 UV 를 구한다.
    int row = ImgIndex / AtlasMaxCol;
    int col = ImgIndex % AtlasMaxCol;
    float2 LeftTop = float2(col * TileSizeUV.x, row * TileSizeUV.y);
    
    // 8. Atlas 전체 내에서 해당 이미지 좌상단 좌표 + 이미지 좌상단에서 참조할 위치 UV
    vUV = LeftTop + vUV;
    
    // 9. 최종 샘플링
    vOutColor = g_tex_0.Sample(g_sam_0, vUV);
    
    return vOutColor;
}

#endif