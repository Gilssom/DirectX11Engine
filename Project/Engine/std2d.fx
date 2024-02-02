// 중복 헤더 파일 참조 방지 = #progma once
#ifndef _STD2D
#define _STD2D


// 정점 버퍼의 정보 변화는 필요 없다.
// 물체의 좌표만 가져오면 된다.

cbuffer TRANSFORM : register(b0)
{
    float4 g_Position;
    float g_Scale;
};

// 정점의 모든 정보가 필요 없다.
// 전달 받은 정점의 필요한 정보들만 가져오면 된다. = Input Layout

struct VS_IN // 입력 타입
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};


struct VS_OUT // 반환 타입
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};


VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos + g_Position.xyz, 1.f);
    output.vColor = _in.vColor;
    
    return output;
}


float4 PS_Std2D(VS_OUT _in) : SV_Target // 반환 타입
{
    // 보간 개념이 들어간 Color
    // 각 정점이 Color 값을 들고 있기 때문에
    // 가중치 보간 개념이 들어가 픽셀 마다의 색상 값을 정해준다. ( Rasterize Stage )
    return _in.vColor;
}


#endif