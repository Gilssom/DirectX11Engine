// 중복 헤더 파일 참조 방지 = #progma once
#ifndef _STD2D
#define _STD2D


// 정점 버퍼의 정보 변화는 필요 없다.
// 물체의 좌표만 가져오면 된다.

cbuffer TRANSFORM : register(b0)
{
    // 행으로 읽을 수 있게
    row_major matrix g_matWorld;
    row_major matrix g_matView;
};

SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

Texture2D g_tex : register(t0);

// 정점의 모든 정보가 필요 없다.
// 전달 받은 정점의 필요한 정보들만 가져오면 된다. = Input Layout

struct VS_IN // 입력 타입
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};


struct VS_OUT // 반환 타입
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};


VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // 행렬을 곱할때 3차원 좌표를 4차원으로 확장 (동차좌표)
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWorld);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}


float4 PS_Std2D(VS_OUT _in) : SV_Target // 반환 타입
{
    // 샘플링 ( 각 픽셀마다의 색상을 가져와야함 )
    float4 vColor = g_tex.Sample(g_sam_0, _in.vUV);
    
    // 보간 개념이 들어간 Color
    // 각 정점이 Color 값을 들고 있기 때문에
    // 가중치 보간 개념이 들어가 픽셀 마다의 색상 값을 정해준다. ( Rasterize Stage )
    return vColor;
}


#endif