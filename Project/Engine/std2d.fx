// 중복 헤더 파일 참조 방지 = #progma once
#ifndef _STD2D
#define _STD2D

// 정점의 모든 정보가 필요 없다.
// 전달 받은 정점의 필요한 정보들만 가져오면 된다. = Input Layout

struct VS_IN // 입력 타입
{
    float3 vPos : POSITION;
    //float4 vColor : COLOR;
};

struct VS_OUT // 반환 타입
{
    float4 vPosition : SV_Position;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos, 1.f);
    
    return output;
}


#endif